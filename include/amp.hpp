#ifndef AMP_H
#define AMP_H

#include <iostream>  // Standard input output mechanism
#include <vector>    // To store the data
#include <random>    // Generate random numbers
#include <cmath>     // sqrt and log functions
#include <algorithm> // Operations on C++ containers
#include <cblas.h>   // cblas for linear algebra operations
#include <iomanip>
#include <numeric>
#include <cassert>

#define data_t long double // Data type to be used 


class AMP
{

public:
    int L;      // Section size of the sparse message
    int B;      // Alphabet size of the sparse message
    int N;      // Size of the code_message/ Number of rows of the coding matrix F
    int M;      // number of columns of the coding matrix F
    data_t c;   // power allocation value
    data_t r;   // communication rate
    data_t snr; // signla to noise ratio
    data_t std_dev; // standard deviation of the Gaussian Channel 
    /*
    The code is divided into L sections of length B
    B is the size of the message alphabet
    L is the length of the message
    message ---- > code message (sparse super position code)
    */
    std::vector<data_t> code_messgae; // Sparse code for the message code_message is 1 dimensional vector with N elements.
    /*
        Coding matrix
    */
    std::vector<data_t> F; // normal random matrix with 0 mean and 1/sqrt(L) std
    /*
        Code word
    */
    std::vector<data_t> codeword;

    AMP(const int &number_of_sections,
        const int &section_size,
        const data_t &power_allocation,
        data_t const &rate,
        data_t const &signal_to_noise_ration);

    //     : L(number_of_sections) // NUmber of sections
    //       ,
    //       B(section_size) // Section size
    //       ,
    //       c(power_allocation), r(rate) // Communication rate
    //       ,
    //       snr(signal_to_noise_ration), gen(dv()) // Random number generator
    // {

    //     this->code_messgae.resize(B * L, 0); // Setting the size of the code
    //     this->N = this->L * this->B;         // Setting the size of the sparse code
    // }
    /*
        Coding the message
     */

    void gen_sparse_code();   // Generate sparse superposition code
    void gen_design_matrix(); // Generate design matrix
    void gen_codeword();      // Generate code word y
    // Printing functions
    void print_code_message() const;
    void print_design_matrix() const;
    void print_code_word() const;

    // Compute the first line of the algorithm
    void compute_dgemv(std::vector<data_t> &F_2, std::vector<data_t> &v, std::vector<data_t> &V);
    void compute_onsegar(std::vector<data_t> codeword, std::vector<data_t> omega_old, std::vector<data_t> V_new, std::vector<data_t> V_old, std::vector<data_t> a_old, std::vector<data_t> &omega_new);
    // Compute cavity variance
    void compute_cavity_var(std::vector<data_t> F_2, std::vector<data_t> V_new, std::vector<data_t> &sigma_new);
    // Compute cavity mean
    void compute_cavity_mean(std::vector<data_t> a_old, std::vector<data_t> sigma_new, std::vector<data_t> V_new, std::vector<data_t> omega_new, std::vector<data_t> &cavity_mean);

    // Compute the message estimation 
    void denoise_a(std::vector<data_t> sigma_new, std::vector<data_t> cavity_mean, std::vector<data_t> &a_new);
    // Get the error of the estimation value 
    void denosie_v(std::vector<data_t> a_new, std::vector<data_t> &v_new);
    // Solver current immplementation just to check output of helper functions
    void solve();

private:
    // Generate random numbers
    std::random_device dv; // Random seed
    std::mt19937 gen;      // Pseudo-number generator
};



#endif // AMP_H