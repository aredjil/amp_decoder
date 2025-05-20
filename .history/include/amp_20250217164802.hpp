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
#include"utils.hpp"
// precison of the output
#define pre 4
/**
 * TODO: immplement the denoising function denoise_a();
 * TODO:immplement the denoising function denoise_v();
 * TODO: immplement a function to compute the section error rate 
 */

class AMP
{

public:
    int L;      // Section size of the sparse message
    int B;      // Alphabet size of the sparse message
    int N;      // Size of the code_message/ Number of rows of the coding matrix F
    int M;      // number of columns of the coding matrix F
    double c;   // power allocation value
    double r;   // communication rate
    double snr; // signla to noise ratio
    /*
    The code is divided into L sections of length B
    B is the size of the message alphabet
    L is the length of the message
    message ---- > code message (sparse super position code)
    */
    std::vector<double> code_messgae; // Sparse code for the message code_message is 1 dimensional vector with N elements.
    /*
        Coding matrix
    */
    std::vector<double> F; // normal random matrix with 0 mean and 1/sqrt(L) std
    /*
        Code word
    */
    std::vector<double> codeword;

    AMP(const int &number_of_sections,
        const int &section_size,
        const double &power_allocation,
        double const &rate,
        double const &signal_to_noise_ration);

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
    void compute_dgemv(std::vector<double> &F_2, std::vector<double> &v, std::vector<double> &V);
    void compute_onsegar(std::vector<double> codeword, std::vector<double> omega_old, std::vector<double> V_new, std::vector<double> V_old, std::vector<double> Fa, std::vector<double> &omega_new);
    // Compute cavity variance
    void compute_cavity_var(std::vector<double> F_2, std::vector<double> V_new, std::vector<double> &sigma_new);
    // Compute cavity mean
    void compute_cavity_mean(std::vector<double> a_old, std::vector<double> sigma_new, std::vector<double> V_new, std::vector<double> omega_new, std::vector<double> &cavity_mean);

    // Compute the message estimation 
    void denoise_a(std::vector<double> sigma_new, std::vector<double> cavity_mean, std::vector<double> &a_new);
    // Solver current immplementation just to check output of helper functions
    void solve();

private:
    // Generate random numbers
    std::random_device dv; // Random seed
    std::mt19937 gen;      // Pseudo-number generator
};



#endif // AMP_H