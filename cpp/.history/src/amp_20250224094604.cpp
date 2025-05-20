#include "../include/amp.hpp"

template <typename T>
AMP<T>::AMP(const int    &number_of_sections,
         const int    &section_size,
         const T &power_allocation,
         const T &rate,
         const T &signal_to_noise_ration)

    : L(number_of_sections) // Number of sections
      ,B(section_size) // Section size
      ,c(power_allocation), r(rate) // Communication rate
      ,snr(signal_to_noise_ration) // Signal to noise ratio 
      ,gen(dv()) // Random number generator
{

    N = L * B;                     // Setting the size of the sparse code
    code_messgae.resize(B * L, 0.0); // Setting the size of the code
    M = static_cast<int>((N * std::log2(B)) / (r * B)); // Computing the number of columns of the coding matrix 
    
    F.resize(M * N);              // Setting the size of the coding matrix  F is M*N matrix
    std_dev = 1.0 / std::sqrt(L); // Standard deviation of the design matrix
    
    codeword.resize(M);           // Settign the size of the codeword y
    ch_capacity = 0.5 * std::log2(1 + snr); // Capacity of the coding channel 

    snr_inv = 1.0 / snr; // Setting the value of the inverse of the snr 

}
/**
 * Method to generate standard sparse superposition code with fixed power allocation c 
 */
template <typename T>
void AMP<T>::gen_sparse_code()
{
    // Generate a random index between 0 and section size
    T lower_bound{0.0}; // Lower bound for the random number generator 
    T upper_bound = static_cast<T>(B) - 1.0; // Upper bound 

    std::uniform_real_distribution<T> dist(lower_bound, upper_bound); // Distrubution of section indecies 
    // Iterate through the sections
    for (int i = 0; i < L; i++)
    {

        int j = dist(gen); // Select a random element index for the section i   
        code_messgae[i * B + j] = c; // Set the value of the selected elemenet to the value of the power allocation 
    }
}

/**
 * Method to generate a design matrix/coding matrix
 * With random gaussian enteries with mean 0.0 and standard deviation 1 / sqrt(L)
 * 
 */
template <typename T>
void AMP<T>::gen_design_matrix()
{

    std::normal_distribution<T> dist(0.0, std_dev); // Normal distrubution 
    /*
        Fill the matrix with gaussian enteries
    */
    std::generate(F.begin(), F.end(), [&]()
                  { return dist(gen); }); // Fill the coding matrix with the normal enteries 
};
/**
 * Method to construct a corrupted codeword 
 * y = F.x + noise. The noise is a AWGN with mean 0.0 and variance inversly proptional to snr 
 */
template <typename T>
void AMP<T>::gen_codeword()
{

    T standard_deviation = 1.0 / std::sqrt(snr); // standard deviation of the AWGNC 

    std::normal_distribution<T> dist(0.0, standard_deviation); // Gaussian distrubution 
for (int mu = 0; mu < M; mu++) // Iterate the rows 
{
    T sum = 0.0;
    for (int i = 0; i < N; i++) // Iterates the columns 
    {
        sum += F[mu * N + i] * code_messgae[i]; // Generate a codeword
    }    
    codeword[mu] = sum + dist(gen); // Add noise to the codeword generating a corrupted codeword 
}
}
/**
 * Method to print the code message 
 */
template <typename T>
void AMP<T>::print_code_message() const
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
/**
 * Method to print the corrupted codeword 
 */
template <typename T>
void AMP<T>::print_code_word() const
{
    for (int i = 0; i < M; i++)
    {
        std::cout << " " << codeword[i] << " ";
    }
    std::cout << "\n";
}
/**
 * Method to print the coding matrix 
 */
template <typename T>
void AMP<T>::print_design_matrix() const
{

    for (int mu = 0; mu < M; mu++) // Iterate over the rows 
    {
        for (int i = 0; i < N; i++) // iterate over the columns 
        {
            std::cout << " " << F[mu * N + i] << " ";
        }
    }
    std::cout << std::endl;
}

/**
 * Method to to update the value of V
 * Equivelent to a matrix vector multiplication F**2.v 
 */
template <typename T>
void AMP<T>::update_V(const std::vector<T> &v, std::vector<T> &V)
{
for (int mu = 0; mu < M; mu++) // Iterate over the rows 
{
    T sum = 0.0;
    for (int i = 0; i < N; i++) // Iterate over columns 
    {
        sum += F[mu * N + i] * F[mu * N + i] * v[i]; // Perform the matrix vector multiplication 
    }
    V[mu] = sum;
}

}
/**
 * Method to compute the Onsegar term of the algorithm
 */
template <typename T>
void AMP<T>::compute_onsegar(const std::vector<T> &omega_old, const std::vector<T> &V_new, const std::vector<T> &V_old, const std::vector<T> &a_old, std::vector<T> &omega_new)
{
    for (int mu = 0; mu < M; mu++) // Iterate over the rows 
    {
        T sum = 0.0;
        for (int i = 0; i < N; i++) // Iterate over the columns 
        {
            sum += F[mu * N + i] * a_old[i];
        }
        omega_new[mu] = sum - V_new[mu] * ((codeword[mu] - omega_old[mu]) / (snr_inv + V_old[mu]));
    }
}
/**
 * Method to compute the cavity variance 
 */
template <typename T>
void AMP<T>::compute_cavity_var(const std::vector<T> &V_new, std::vector<T> &sigma_new)
{

    for (int i = 0; i < N; i++) // Iterate over the rows 
    {
        T sum = 0.0;
        for (int mu = 0; mu < M; mu++) // Iterate over the columns 
        {
            sum += (F[mu * N + i] * F[mu * N + i]) / (snr_inv + V_new[mu]);
        }
        sigma_new[i] = 1.0 / sum;
    }
}
/**
 * Method to compute the cavity mean 
 */
template <typename T>
void AMP<T>::compute_cavity_mean(const std::vector<T> &a_old, const std::vector<T> &sigma_new, const std::vector<T> &V_new, const std::vector<T> &omega_new, std::vector<T> &cavity_mean)
{

    for (int i = 0; i < N; i++) // Iterate over the columns 
    {
        T sum = 0.0;
        for (int mu = 0; mu < M; mu++) // Iterate over the rows 
        {
            sum += F[mu * N + i] * ((codeword[mu] - omega_new[mu]) / (snr_inv + V_new[mu]));
        }
        cavity_mean[i] = a_old[i] + sigma_new[i] * sum;
    }
}
/**
 * Method to denoise the estimate of the code message 
 */
template <typename T>
void AMP<T>::denoise_a(const std::vector<T> &sigma_new, const std::vector<T> &cavity_mean, std::vector<T> &a_new)
{

    std::vector<T> exp_term(L);

    for (int i = 0; i < L; i++) // Iterate over the sections 
    {
        T sum = 0.0;
        for (int j = 0; j < B; j++) // Iterate over the elements of the section 
        {
            sum += std::exp(-c * (c - 2 * cavity_mean[i * B + j]) / (2 * sigma_new[i * B + j]));
        }
        exp_term[i] = sum;
    }

    for (int i = 0; i < N; i++) // Update the new value of the estimate of the message 
    {

        a_new[i] = c * (std::exp(-c * (c - 2 * cavity_mean[i]) / (2 * sigma_new[i]))) / exp_term[i / B];
    }
}
/**
 * Method to denoise the variance of the estimate of the message 
 */
template <typename T>
void AMP<T>::denosie_v(const std::vector<T> &a_new, std::vector<T> &v_new)
{
    for (int i = 0; i < N; i++) // Iterate over the elements of the estimated message 
    {
        v_new[i] = a_new[i] * (c - a_new[i]);
    }
}
/**
 * Method to compute the difference between two estimation
 * Checks for convergence 
 */
template <typename T>
T AMP<T>::compute_dif(const std::vector<T> &a_new, const std::vector<T> &a_old)
{
    T sum = 0.0;
    for (int i = 0; i < N; i++) // Iterate the code message size  
    {
        sum += (a_new[i] - a_old[i]) * (a_new[i] - a_old[i]);
    }
    return  sum / N; // Return the normlized difference 
}
/**
 * Method to amplify the estimated message 
 */
template <typename T>
void AMP<T>::amplify(std::vector<T> a_new, std::vector<T> &a_temp)
{
    for (int i = 0; i < L; i++)
    {
        T *row_begin = a_new.data() + i * B;
        T *row_end = row_begin + B;
        T *max_element = std::max_element(row_begin, row_end);

        int max_idx = std::distance(row_begin, max_element);

        a_temp[i * B + max_idx] = 1.0;
    }
}
/**
 * Method to compute the mean square error between the estimated message and the code message 
 */
template <typename T>
T AMP<T>::compute_mse(const std::vector<T> &a_new)
{
    T err = 0.0;
    for (int i = 0; i < N; i++) // Iterate the size of the code message 
    {
        err += (a_new[i] - code_messgae[i]) * (a_new[i] - code_messgae[i]);
    }
    return (1.0 / N) * err;
}
/**
 * Method to compute the section error rate
 * The section error rate corresponds to the ratio of sections which are wrongly reconstructed 
 */
template <typename T>
T AMP<T>::compute_ser(const std::vector<T> &a_temp)
{
    T ser_err; // Variable to hold the value of the section error rate

    int count = L; // Intially it is assumed that all secions are wrongly reconstructed 
    for (int i = 0; i < L; i++) // Loop over the number of sections 
    {
        int id_count = 0; // Variable to track the count of elements that are correctly predicted 
        for (int j = 0; j < B; j++)
        {
            if (std::abs(a_temp[i * B + j] - code_messgae[i * B + j]) < 10E-1)  // abs here because the message and the estimate is double precision
            {
                id_count++; // Increse the count by one if the estimated element and the real element are identitical 
            }
        }
        if (id_count == B) // If all the element of the section are correctly reconstructed 
        {
            count--; // decrease the count of wrongly reconstructed sections by one 
        }
    }
    ser_err = static_cast<T>(count);  // cast the type of the count to the T type 
    return ser_err; // Return the section error rate 
}
/**
 * Method that performs AMP decoding 
 */
template <typename T>
void AMP<T>::solve(const int &t_max, const T &ep)
{

    std::vector<T> v_old(N, 1.0 / (B * snr));
    std::vector<T> v_new(N, 1.0 / (B * snr));

    std::vector<T> V_new(M); // vector to hold the result of the matrix multiplication
    std::vector<T> V_old(M); // Old value of V

    std::vector<T> a_old(N, 0.0); // Store the estimation of the message
    std::vector<T> a_new(N, 0.0); // Store the new estimation of the message

    std::vector<T> a_temp(N, 0.0); // Vector to store the amplified estimate of the message
                                        // Must be set to 0

    std::vector<T> omega_old(codeword); // Old value of omega
    std::vector<T> omega_new(codeword); // New value of omega

    std::vector<T> sigma_new(N);
    std::vector<T> cavity_mean(N);

    // Error threshold
    T delta = ep + 1;

    int t = 0;

    T mse_err = 1.0;
#ifdef MSE
    std::cout << "Iter," << "MSE\n";
    std::cout << t << ", " << mse_err << "\n";
#else
    T ser_err = 1.0;
    std::cout << "Iter," << "SER\n";
    std::cout << t << ", " << ser_err << "\n";
#endif
    t++;
    while (t < t_max && delta > ep)
    {
        // Intilize the amplified vector from previous iteration to 0
        std::fill(a_temp.begin(), a_temp.end(), 0); // To avoid collisions with values from previous
                                                    // Iterations :D
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

#ifdef MSE
        // Compute the mean square error
        mse_err = compute_mse(a_new);
        std::cout << t << ", " << mse_err << "\n";
#else
        // amplify(a_new, a_temp);
        // ser_err = compute_ser(a_temp) / L; // compute the section error rate
        // std::cout << t << ", " << ser_err << "\n";
#endif
        // Check covnergence
        delta = compute_dif(a_new, a_old);
        // Swap new values and old ones for the next iteration
        v_old = v_new;

        V_old = V_new;

        a_old = a_new;

        omega_old = omega_new;
        // increment the counter
        t++;
    }
    amplify(a_new, a_temp);
    ser_err = compute_ser(a_temp) / L; // compute the section error rate
    std::cout << t << ", " << ser_err << "\n";
}