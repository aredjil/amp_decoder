#include "../include/amp.hpp"

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