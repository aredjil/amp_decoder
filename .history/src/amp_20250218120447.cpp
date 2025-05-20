#include "../include/amp.hpp"
// #include "../include/utils.hpp"

/*
    Class constructor
*/
AMP::AMP(const int &number_of_sections,
         const int &section_size,
         const double &power_allocation,
         double const &rate,
         double const &signal_to_noise_ration)

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
}

/*
    Function to generate sparse superposition codes.
*/
void AMP::gen_sparse_code()
{
    // Generate a random index between 0 and section size
    double lower_bound{0.0};
    double upper_bound = static_cast<double>(this->B) - 1.0;
    std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
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

    this->M = (int)(this->N * std::log2(this->B)) / (r * this->B);

    this->F.resize(this->M * this->N);         // Setting the size of the coding matrix  F is N*M matrix
    double std_dev = std::sqrt(1.0 / this->L); // standard deviation

    std::normal_distribution<double> dist(0.0, std_dev);
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

    std::vector<double> noise(this->M, 0); // Noise buffer

    std::normal_distribution<double> dist(0.0, snr);

    std::generate(noise.begin(), noise.end(), [&]()
                  { return dist(this->gen); });

    // Generate the codeword
    cblas_dgemv(
        CblasRowMajor,
        CblasNoTrans,
        this->M, this->N,
        1.0,
        this->F.data(), this->N,
        this->code_messgae.data(), 1,
        0.0,
        this->codeword.data(), 1.0);
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
void AMP::compute_dgemv(std::vector<double> &F_2, std::vector<double> &v, std::vector<double> &V)
{
    cblas_dgemv(
        CblasRowMajor,
        CblasNoTrans,
        this->M, this->N,
        1.0,
        F_2.data(), this->N,
        v.data(), 1,
        0.0,
        V.data(), 1.0);
}
// Compute onsegar term
void AMP::compute_onsegar(std::vector<double> codeword, std::vector<double> omega_old, std::vector<double> V_new, std::vector<double> V_old, std::vector<double> a_old, std::vector<double> &omega_new)
{
    double snr_inv = 1.0 / this->snr;
    double Fa =0.0;
    for(int mu=0;mu<M;mu++)
    {
        for(int i=0;i<N;i++)
        {
            Fa += F[mu*N+i] * a_old[i];
        }
        omega_new[mu] = Fa - (codeword[mu] - omega_old[mu]) * (V_new[mu] / ())
    }
    // std::vector<double> sub(M, 0.0);  // Variable to hold the result of y-omega
    // std::vector<double> frac(M, 0.0); // Variable to hold the result of V_new /(1\snr + V_old)
    // std::vector<double> onsegar_term(M, 0.0);
    // // Compute y - omega
    // std::transform(
    //     codeword.begin(),
    //     codeword.end(),
    //     omega_old.begin(),
    //     sub.begin(),
    //     std::minus<int>());
    // // Compute V_{\mu}^{t+1} / (1\snr + V_{\mu}^{t})
    // std::transform(
    //     V_old.begin(),
    //     V_old.end(),
    //     V_new.begin(),
    //     frac.begin(),
    //     [snr_inv](int v_old, int v_new)
    //     { return v_new / (v_old + snr_inv); });
    // // Compute onsegar term
    // std::transform(
    //     sub.begin(),
    //     sub.end(),
    //     frac.begin(),
    //     onsegar_term.begin(),
    //     [](int a, int b)
    //     { return a * b; });
    // // Compute omega_new
    // std::transform(
    //     Fa.begin(),
    //     Fa.end(),
    //     onsegar_term.begin(),
    //     omega_new.begin(),
    //     [](int a, int b)
    //     { return a - b; });
}

// Compute cavity variance
void AMP::compute_cavity_var(std::vector<double> F_2, std::vector<double> V_new, std::vector<double> &sigma_new)
{
    double snr_inv = 1.0 / this->snr;
    for (int i = 0; i < N; i++)
    {
        double sum = 0.0;
        for (int mu = 0; mu < M; mu++)
        {
            sum += F_2[mu * M + i] / (snr_inv + V_new[mu]);
        }
        sigma_new[i] = 1.0 / sum;
    }
}
// Compute cavity mean
/**
 * I am assuming the unreasonable values I am getting from the estimate of the mesage could be traced here
 */
void AMP::compute_cavity_mean(std::vector<double> a_old, std::vector<double> sigma_new, std::vector<double> V_new, std::vector<double> omega_new, std::vector<double> &cavity_mean)
{
    const double snr_inv = 1.0 / this->snr; // Get the signal to noise ratio

    for (int i = 0; i < N; i++)
    {
        double sum = 0.0;
        for (int mu = 0; mu < M; mu++)
        {
            sum += F[mu * N + i] * ((codeword[mu] - omega_new[mu]) / (snr_inv + V_new[mu]));
        }
        cavity_mean[i] = a_old[i] + sigma_new[i] * sum;
    }

}
// COmpute the estimate of the message a
void AMP::denoise_a(std::vector<double> sigma_new, std::vector<double> cavity_mean, std::vector<double> &a_new)
{
    const double power_alloc = this->c; // Get the power allocation
    // 1. compute the sum
    std::vector<double> exp_term(N);

    std::transform(
        sigma_new.begin(),
        sigma_new.end(),
        cavity_mean.begin(),
        exp_term.begin(),
        [power_alloc](double sigma, double cav_m)
        {
            return std::exp(-power_alloc * (power_alloc - 2 * cav_m) / (2 * sigma));
        });

    // std::cout<<"Exponential term\n\n";
    // for(auto term : exp_term)
    //     std::cout<<" "<<term<<" ";
    // std::cout<<"\n\n";
    // 2. loop N times and access the sum using %
    for (int i = 0; i < N; i++)
    {

        a_new[i] = power_alloc * (std::exp(-power_alloc * (power_alloc - 2 * cavity_mean[i]) / (2 * sigma_new[i]))) / exp_term[(i % L)];
    }
}
// Get the the value of the error of the estimation v_new
void AMP::denosie_v(std::vector<double> a_new, std::vector<double> &v_new)
{
    for (int i = 0; i < N; i++)
    {
        v_new[i] = a_new[i] * (c - a_new[i]);
    }
}

// Solver
void AMP::solve()
{

    std::vector<double> F_2(F); // Piecewise square of design matrix F

    std::vector<double> v(N, 1.0 / (B * snr));
    std::vector<double> v_new(N);

    std::vector<double> V_new(M); // vector to hold the result of the matrix multiplication
    std::vector<double> V_old(M);

    std::vector<double> Fa(M, 0.0); // Store the result of matrix vector multiplication

    std::vector<double> a_old(N, 0.0); // Store the estimation of the message
    std::vector<double> a_new(N, 0.0); // Store the new estimation of the message

    std::vector<double> omega_old(codeword); // Old value of omega
    std::vector<double> omega_new(M);        // New value of omega

    std::vector<double> sigma_new(N, 0.0);
    std::vector<double> cavity_mean(N, 0.0);
    // Compute F_{ij}**2
    int t=0;
    int t_max = 5;
    while(t<t_max)
    {
        std::transform(
            F_2.begin(),
            F_2.end(),
            F_2.begin(),
            [](double x)
            { return x * x; });
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

    std::cout << "The estimated message\n";
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout << " " << a_new[i * B + j] << " ";
        }
        std::cout << std::endl;
    }
}