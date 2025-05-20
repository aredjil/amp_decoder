#include "../include/amp.hpp"
// #include "../include/utils.hpp"

/*
    Class constructor
*/
AMP::AMP(const int &number_of_sections,
         const int &section_size,
         const data_t &power_allocation,
         data_t const &rate,
         data_t const &signal_to_noise_ration)

    : L(number_of_sections) // NUmber of sections
      ,
      B(section_size) // Section size
      ,
      c(power_allocation), r(rate) // Communication rate
      ,
      snr(signal_to_noise_ration), gen(dv()) // Random number generator
{

    this->code_messgae.resize(B * L, 0); // Setting the size of the code
    this->N = this->L * this->B;         // Setting the size of the sparse code
    this->M = (int)(this->N * std::log2(this->B)) / (r * this->B);

    this->F.resize(this->M * this->N);         // Setting the size of the coding matrix  F is N*M matrix
    std_dev = std::sqrt(1.0 / this->L); // standard deviation
}

/*
    Function to generate sparse superposition codes.
*/
void AMP::gen_sparse_code()
{
    // Generate a random index between 0 and section size
    data_t lower_bound{0.0};
    data_t upper_bound = static_cast<data_t>(this->B) - 1.0;
    std::uniform_real_distribution<data_t> dist(lower_bound, upper_bound);
    // Iterate through the sections
    for (int i = 0; i < this->L; i++)
    {

        int j = dist(gen);
        this->code_messgae[i * this->B + j] = c;
    }
}
/*
    Function to generate design matrix.
*/
void AMP::gen_design_matrix()
{

    std::normal_distribution<data_t> dist(0.0, std_dev);
    /*
        Fill the matrix with gaussian enteries
    */
    std::generate(this->F.begin(), this->F.end(), [&]()
                  { return dist(this->gen); });
};
/*
    Generate a codeword y from the code message x using the code matrix F
*/
void AMP::gen_codeword()
{

    this->codeword.resize(this->M);

    std::vector<data_t> noise(this->M, 0); // Noise buffer

    std::normal_distribution<data_t> dist(0.0, snr);

    std::generate(noise.begin(), noise.end(), [&]()
                  { return dist(gen); }); // Gaussian noise 

    // Generate the codeword

    for (int mu = 0; mu < M; mu++)
    {
        data_t sum = 0.0;
        for (int i = 0; i < N; i++)
        {
            sum += F[mu * N + i] * code_messgae[i] + noise[mu];
        }
        codeword[mu] = sum;
    }
}
// print the message
void AMP::print_code_message() const
{
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout << " " << code_messgae[i * B + j] << " ";
        }
        std::cout << std::endl;
    }
}
// print the codeword
void AMP::print_code_word() const
{
    for (int i = 0; i < M; i++)
    {
        std::cout << " " << codeword[i] << " ";
    }
    std::cout << "\n";
}

// Print design matrix
void AMP::print_design_matrix() const
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << " " << F[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
}

// Solver immplementation

/**
 * Compute V_{\mu}^{t} = \sum_{i}F_{\mu i}^2 v_{i}^{t}
 */
void AMP::compute_dgemv(std::vector<data_t> &F_2, std::vector<data_t> &v, std::vector<data_t> &V)
{
    for (int mu = 0; mu < M; mu++)
    {
        data_t sum = 0.0;
        for (int i = 0; i < N; i++)
        {
            sum += F_2[mu * N + i] * v[i];
        }
        V[mu] = sum;
    }
}
// Compute onsegar term
void AMP::compute_onsegar(std::vector<data_t> codeword, std::vector<data_t> omega_old, std::vector<data_t> V_new, std::vector<data_t> V_old, std::vector<data_t> a_old, std::vector<data_t> &omega_new)
{
    data_t snr_inv = 1.0 / this->snr;
    data_t Fa = 0.0;
    for (int mu = 0; mu < M; mu++)
    {
        for (int i = 0; i < N; i++)
        {
            Fa += F[mu * N + i] * a_old[i];
        }
        omega_new[mu] = Fa - V_new[mu] * ((codeword[mu] - omega_old[mu]) / (snr_inv + V_old[mu]));
    }
}

// Compute cavity variance
void AMP::compute_cavity_var(std::vector<data_t> F_2, std::vector<data_t> V_new, std::vector<data_t> &sigma_new)
{
    data_t snr_inv = 1.0 / this->snr;
    for (int i = 0; i < N; i++)
    {
        data_t sum = 0.0;
        for (int mu = 0; mu < M; mu++)
        {
            sum += F_2[mu * M + i] / (snr_inv + V_new[mu]);
        }
        sigma_new[i] = 1.0 / sum;
    }
}
// Compute cavity mean
void AMP::compute_cavity_mean(std::vector<data_t> a_old, std::vector<data_t> sigma_new, std::vector<data_t> V_new, std::vector<data_t> omega_new, std::vector<data_t> &cavity_mean)
{
    const data_t snr_inv = 1.0 / this->snr; // Get the signal to noise ratio

    for (int i = 0; i < N; i++)
    {
        data_t sum = 0.0;
        for (int mu = 0; mu < M; mu++)
        {
            sum += F[mu * N + i] * ((codeword[mu] - omega_new[mu]) / (snr_inv + V_new[mu]));
        }
        cavity_mean[i] = a_old[i] + sigma_new[i] * sum;
    }
}
// COmpute the estimate of the message a
void AMP::denoise_a(std::vector<data_t> sigma_new, std::vector<data_t> cavity_mean, std::vector<data_t> &a_new)
{
    const data_t power_alloc = this->c; // Get the power allocation

    std::vector<data_t> exp_term(N);

    std::transform(
        sigma_new.begin(),
        sigma_new.end(),
        cavity_mean.begin(),
        exp_term.begin(),
        [power_alloc](data_t sigma, data_t cav_m)
        {
            return std::exp(-power_alloc * (power_alloc - 2 * cav_m) / (2 * sigma));
        });

    for (int i = 0; i < N; i++)
    {

        a_new[i] = power_alloc * (std::exp(-power_alloc * (power_alloc - 2 * cavity_mean[i]) / (2 * sigma_new[i]))) / exp_term[(i % L)];
    }
}
// Get the the value of the error of the estimation v_new
void AMP::denosie_v(std::vector<data_t> a_new, std::vector<data_t> &v_new)
{
    for (int i = 0; i < N; i++)
    {
        v_new[i] = a_new[i] * (c - a_new[i]);
    }
}

// Solver
void AMP::solve()
{

    std::vector<data_t> F_2(F); // Piecewise square of design matrix F
    std::transform(
        F_2.begin(),
        F_2.end(),
        F_2.begin(),
        [](data_t x)
        { return x * x; });

    std::vector<data_t> v(N, 1.0 / (B * snr));
    std::vector<data_t> v_new(N, 1.0 / (B * snr));

    std::vector<data_t> V_new(M); // vector to hold the result of the matrix multiplication
    std::vector<data_t> V_old(M); // Old value of V

    std::vector<data_t> a_old(N, 0.0); // Store the estimation of the message
    std::vector<data_t> a_new(N, 0.0); // Store the new estimation of the message

    std::vector<data_t> omega_old(codeword); // Old value of omega
    std::vector<data_t> omega_new(M);        // New value of omega

    std::vector<data_t> sigma_new(N, 0.0);
    std::vector<data_t> cavity_mean(N, 0.0);

    int t = 0;
    int t_max = 25;
    while (t < t_max)
    {
        // Compute V_{\mu}^{t} = \sum_{i}F_{\mu i}^2 v_{i}^{t}
        compute_dgemv(F_2, v, V_new);
        // Compute F.a = \sum_{i}F_{\mu i} a_{i}^{t}
        // compute_dgemv(F, a_old, Fa);
        // Compute omege_new
        compute_onsegar(codeword, omega_old, V_new, V_old, a_old, omega_new);
        // Compute the cavity variance
        compute_cavity_var(F_2, V_new, sigma_new);
        // Compute the cavity mean
        compute_cavity_mean(a_old, sigma_new, V_new, omega_new, cavity_mean);
        // Compute the message estimate
        denoise_a(sigma_new, cavity_mean, a_new);
        denosie_v(a_new, v_new);
        t++;
    }

    std::cout << "The estimated message a: \n";
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout << " " << a_new[i * B + j] << " ";
        }
        std::cout << std::endl;
    }
}