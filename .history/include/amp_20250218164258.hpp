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
#include <chrono>
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


    void gen_sparse_code();   // Generate sparse superposition code
    void gen_design_matrix(); // Generate design matrix
    void gen_codeword();      // Generate code word y
    // Printing functions
    void print_code_message() const;
    void print_design_matrix() const;
    void print_code_word() const;

    // Compute the first line of the algorithm
    void update_V(const std::vector<data_t> &v, std::vector<data_t> &V);
    void compute_onsegar(const std::vector<data_t> & omega_old, const std::vector<data_t> & V_new, const std::vector<data_t> & V_old, const std::vector<data_t> & a_old, std::vector<data_t> &omega_new);
    // Compute cavity variance
    void compute_cavity_var(const std::vector<data_t> & V_new, std::vector<data_t> &sigma_new);
    // Compute cavity mean
    void compute_cavity_mean(const std::vector<data_t> & a_old, const std::vector<data_t> & sigma_new, const std::vector<data_t> & V_new, const std::vector<data_t> & omega_new, std::vector<data_t> &cavity_mean);
    // Compute the message estimation 
    void denoise_a(const std::vector<data_t> & sigma_new, const std::vector<data_t> &, std::vector<data_t> &a_new);
    // Get the error of the estimation value 
    void denosie_v(const std::vector<data_t> & a_new, std::vector<data_t> &v_new);
    // Compute the error 
    data_t compute_dif(const std::vector<data_t> & a_new, const std::vector<data_t> & a_old);  
    // Solver current immplementation just to check output of helper functions
    std::vector<data_t> amplify(std::vector<data_t> a);
    // Compute section error rate 
    data_t compute_ser(std::vector<data_t> a_);
    // Solver
    void solve();

private:
    // Generate random numbers
    std::random_device dv; // Random seed
    std::mt19937 gen;      // Pseudo-number generator
};



#endif // AMP_H