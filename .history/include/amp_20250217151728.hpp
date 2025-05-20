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

// precison of the output
#define pre 4

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
    void compute_onsegar(std::vector<double> codeword, std::vector<double> omega_old, std::vector<double> V_new, std::vector<double> V_old, std::vector<double>omega_new); 
    // Solver current immplementation just to check output of helper functions
    void solve();

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
                  { return dist(this->gen); }
                );
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
                  { return dist(this->gen); }
                );

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
    std::cout << std::fixed << std::setprecision(pre);
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
    std::cout << std::fixed << std::setprecision(pre);
    for (int i = 0; i < M; i++)
    {
        std::cout << " " << codeword[i] << " ";
    }
    std::cout << "\n";
}

// Print design matrix
void AMP::print_design_matrix() const
{
    std::cout << std::fixed << std::setprecision(pre);
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
void AMP::compute_onsegar(std::vector<double> codeword, std::vector<double> omega_old, std::vector<double> V_new, std::vector<double> V_old, std::vector<double>omega_new)
{   double snr_inv = 1.0 / this->snr;
    std::vector<double> sub(M, 0.0); // Variable to hold the result of y-omega 
    std::vector<double> frac(M, 0.0); // Variable to hold the result of V_new /(1\snr + V_old)
    std::vector<double> onsegar_
    std::transform(
        codeword.begin(), 
        codeword.end(), 
        omega_old.begin(), 
        sub.begin(), 
        std::minus<int>()
    );
    // Compute V_{\mu}^{t+1} / (1\snr + V_{\mu}^{t})
    std::transform(
        V_old.begin(), 
        V_old.end(), 
        V_new.begin(), 
        frac.begin(), 
        [snr_inv](int v_old, int v_new){ return v_new /(v_old + snr_inv);}
    );


}



// Solver 
void AMP::solve(){

    std::vector<double> F_2(F); // Piecewise square of design matrix F 
    std::vector<double> v(N, 1.0/(B*snr));
    std::vector<double> V(M); // vector to hold the result of the matrix multiplication  
    std::vector<double> Fa(M, 0.0); // Store the result of matrix vector multiplication
    std::vector<double> a(N, 0.0); // Store the estimation of the message 
    
    
    // Compute F_{ij}**2
    std::transform( 
        F_2.begin(),
        F_2.end(), 
        F_2.begin(), 
        [](double x){ return x * x; }
    ); 
    //Compute V_{\mu}^{t} = \sum_{i}F_{\mu i}^2 v_{i}^{t}
    compute_dgemv(F_2, v, V); 
    //Compute F.a = \sum_{i}F_{\mu i} a_{i}^{t}
    compute_dgemv(F, a, Fa); 




}

#endif // AMP_H