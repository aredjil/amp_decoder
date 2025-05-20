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

    code_messgae.resize(B * L, 0); // Setting the size of the code
    N = L * B;                     // Setting the size of the sparse code
    M = static_cast<int>((N * std::log2(B)) / (r * B));

    F.resize(M * N);              // Setting the size of the coding matrix  F is M*N matrix
    std_dev = 1.0 / std::sqrt(L); // standard deviation of the design matrix
    codeword.resize(M);           // Settign the size of the codeword y
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
    for (int i = 0; i < L; i++)
    {

        int j = dist(gen);
        this->code_messgae[i * B + j] = c;
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
    std::generate(F.begin(), F.end(), [&]()
                  { return dist(gen); });
};
/*
    Generate a codeword y from the code message x using the code matrix F
*/
void AMP::gen_codeword()
{

    std::vector<data_t> noise(M, 0.0); // Noise buffer

    data_t standard_deviation = 1.0 / std::sqrt(snr);

    std::normal_distribution<data_t> dist(0.0, standard_deviation);

    std::generate(noise.begin(), noise.end(), [&]()
                  { return dist(gen); }); // Gaussian noise

    // Generate the codeword
    for (int mu = 0; mu < M; mu++)
    {
        data_t sum = 0.0;
        for (int i = 0; i < N; i++)
        {
            sum += F[mu * N + i] * code_messgae[i];
        }
        codeword[mu] = sum + noise[mu];
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
        std::cout << "\n";
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

    for (int mu = 0; mu < M; mu++)
    {
        for (int i = 0; i < N; i++)
        {
            std::cout << " " << F[mu * N + i] << " ";
        }
    }
    std::cout << std::endl;
}

// Solver immplementation
void AMP::update_V(const std::vector<data_t> &v, std::vector<data_t> &V)
{
    for (int mu = 0; mu < M; mu++)
    {
        data_t sum = 0.0;
        for (int i = 0; i < N; i++)
        {
            sum += F[mu * N + i] * F[mu * N + i] * v[i];
        }
        V[mu] = sum;
    }
}
// Compute onsegar term
void AMP::compute_onsegar(const std::vector<data_t> &omega_old, const std::vector<data_t> &V_new, const std::vector<data_t> &V_old, const std::vector<data_t> &a_old, std::vector<data_t> &omega_new)
{
    data_t snr_inv = 1.0 / snr;
    for (int mu = 0; mu < M; mu++)
    {
        data_t sum = 0.0;
        for (int i = 0; i < N; i++)
        {
            sum += F[mu * N + i] * a_old[i];
        }
        omega_new[mu] = sum - V_new[mu] * ((codeword[mu] - omega_old[mu]) / (snr_inv + V_old[mu]));
    }
}

// Compute cavity variance
void AMP::compute_cavity_var(const std::vector<data_t> &V_new, std::vector<data_t> &sigma_new)
{
    data_t snr_inv = 1.0 / snr;

    for (int i = 0; i < N; i++)
    {
        data_t sum = 0.0;
        for (int mu = 0; mu < M; mu++)
        {
            sum += (F[mu * N + i] * F[mu * N + i]) / (snr_inv + V_new[mu]);
        }
        sigma_new[i] = 1.0 / sum;
    }
}
// Compute cavity mean
void AMP::compute_cavity_mean(const std::vector<data_t> &a_old, const std::vector<data_t> &sigma_new, const std::vector<data_t> &V_new, const std::vector<data_t> &omega_new, std::vector<data_t> &cavity_mean)
{
    const data_t snr_inv = 1.0 / snr; // Get the signal to noise ratio

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
void AMP::denoise_a(const std::vector<data_t> &sigma_new, const std::vector<data_t> &cavity_mean, std::vector<data_t> &a_new)
{

    std::vector<data_t> exp_term(L);

    for (int i = 0; i < L; i++)
    {
        data_t sum = 0.0;
        for (int j = 0; j < B; j++)
        {
            sum += std::exp(-c * (c - 2 * cavity_mean[i * B + j]) / (2 * sigma_new[i * B + j]));
        }
        exp_term[i] = sum;
    }

    for (int i = 0; i < N; i++)
    {

        a_new[i] = c * (std::exp(-c * (c - 2 * cavity_mean[i]) / (2 * sigma_new[i]))) / exp_term[i / B];
    }
}
// Get the the value of the error of the estimation v_new
void AMP::denosie_v(const std::vector<data_t> &a_new, std::vector<data_t> &v_new)
{
    for (int i = 0; i < N; i++)
    {
        v_new[i] = a_new[i] * (c - a_new[i]);
    }
}
// Compute the difference in estimations 
data_t AMP::compute_diif(std::vector<data_t> a_new, std::vector<data_t> a_old)
{
    data_t diff = 0.0; 
    for(int i=0;i<N;i++)
    {
       diff += (a_new[]) 
    }
}

// Solver
void AMP::solve()
{

    std::vector<data_t> v_old(N, 1.0 / (B * snr));
    std::vector<data_t> v_new(N, 1.0 / (B * snr));

    std::vector<data_t> V_new(M); // vector to hold the result of the matrix multiplication
    std::vector<data_t> V_old(M); // Old value of V

    std::vector<data_t> a_old(N, 0.0); // Store the estimation of the message
    std::vector<data_t> a_new(N, 0.0); // Store the new estimation of the message

    std::vector<data_t> omega_old(codeword); // Old value of omega
    std::vector<data_t> omega_new(codeword); // New value of omega

    std::vector<data_t> sigma_new(N);
    std::vector<data_t> cavity_mean(N);

    data_t ep = 10E-6; // Error threshold 
    data_t delta = ep + 1; 

    int t = 0;
    int t_max = 5;

    while (t < t_max && delta < ep)
    {
        // Compute V_{\mu}^{t} = \sum_{i}F_{\mu i}^2 v_{i}^{t}
        update_V(v_old, V_new); // Update V
        // Compute omege_new
        compute_onsegar(omega_old, V_new, V_old, a_old, omega_new);
        // Compute the cavity variance
        compute_cavity_var(V_new, sigma_new);
        // Compute the cavity mean
        compute_cavity_mean(a_old, sigma_new, V_new, omega_new, cavity_mean);
        // Compute the message estimate
        denoise_a(sigma_new, cavity_mean, a_new);
        // Compute the error in the message estimate
        denosie_v(a_new, v_new);
        delta = (1.0/N) * compute_diif(a_new, a_old);
        // swap a_old, v_old and a_new, and v_new
        v_old = v_new;

        V_old = V_new;

        a_old = a_new;

        omega_old = omega_new;
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
    std::cout << "\n\n";
    std::cout << "The estimated message v: \n";
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout << " " << v_new[i * B + j] << " ";
        }
        std::cout << std::endl;
    }
}