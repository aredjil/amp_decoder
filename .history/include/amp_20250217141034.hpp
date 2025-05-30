#ifndef AMP_H
#define AMP_H
#include <iostream>  // Standard input output mechanism
#include <vector>    // To store the data
#include <random>    // Generate random numbers
#include <cmath>     // sqrt and log functions
#include <algorithm> // Operations on C++ containers
#include <cblas.h>   // cblas for linear algebra operations

/*
 *NOTE: Pass the seed as a paramter the class constructor.
 */
class AMP
{

public:
    int L; // Section size of the sparse message
    int B; // Alphabet size of the sparse message
    int N; // Size of the code_message/ Number of rows of the coding matrix F
    int M; // number of columns of the coding matrix F
    double c; // power allocation value
    double r;// communication rate 
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
        double const &rate)
    
        :L(number_of_sections) // NUmber of sections
        ,B(section_size) // Section size
        ,c(power_allocation)
        ,r(rate) // Communication rate 
        ,snr(signal_to_noise_ration)
        ,gen(dv()) // Random number generator
    {

        this->code_messgae.resize(B * L, 0); // Setting the size of the code
        this->N = this->L * this->B;         // Setting the size of the sparse code
    }
    /*
        Coding the message
     */

    void gen_sparse_code();                                 // Generate sparse superposition code
    void gen_design_matrix();             // Generate design matrix
    void gen_codeword(const double &signal_to_noise_ratio); // Generate code word y
    // Printing functions
    void print_code_message() const;
    void print_design_matrix() const; 
    void print_code_word() const;

private:
    // Generate random numbers
    std::random_device dv; // Random seed
    std::mt19937 gen;      // Pseudo-number generator
};

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
void AMP::gen_codeword(const double &snr)
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

#endif // AMP_H