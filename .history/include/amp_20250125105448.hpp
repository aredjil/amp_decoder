#ifndef AMP_H 
#define AMP_H
#include<iostream> // Standard input output mechanism  
#include<vector> // To store the data 
#include<random> // Generate random numbers  
#include<cmath> // sqrt and log functions 
#include<cblas.h> // cblas for linear algebra operations 

template<typename T>
class AMP{
    private: 
    // Generate random numbers 
    std::random_device dv; // Random seed 
    std::mt19937 gen;      // Pseudo-number generator 

    public: 
    T L; // Section size of the sparse message 
    T B; // Alphabet size of the sparse message 
    T N; 
    T M;
    /*
    The code is divided into L sections of length B
    B is the size of the message alphabet 
    L is the length of the message 
    message ---- > code message (sparse super position code)
    */ 
    std::vector<T> code_messgae; // Sparse code for the message code_message is 1 dimensional vector with N elements.
    /*
    Coding matrix 
    */
    std::vector<double> F; // normal random matrix with 0 mean and 1/sqrt(L) std
    /*
        Signal to noise ratio that will be used to generate the codeword y
    */
    template <typename R>
    R snr; 
    AMP(const T &number_of_sections=8, const T & section_size=2):L(number_of_sections), B(section_size), gen(dv()){
        this->code_messgae.resize(B * L, 0); // Setting the size of the code
        this->N = this->L * this->B; // Setting the size of the sparse code
    }
    // Generate sparse superposition code
    template <typename R>
    void gen_sparse_code(const R& power_allocation=1); 
    // Generate design matrix 
    template<typename R> 
    void gen_design_matrix(const R& rate);
    // Generate code word y
    template <typename R>
    void gen_codeword(const R& signal_to_noise_ratio);

};

/*
    Function to generate sparse superposition codes.
*/
template <typename T>
template <typename R>
void AMP<T>::gen_sparse_code(const R& power_allocation){
    // Iterate through the sections 
    for(int i=0;i < this->L; i++){
        // Generate a random index between 0 and section size
        std::uniform_int_distribution<int> dist(0, this->B-1); 
        int j = dist(gen); 
        this->code_messgae[i * this->B + j] = power_allocation; 
    }  
}
/*
    Function to generate design matrix.
*/
template <typename T>
template <typename R>
void AMP<T>::gen_design_matrix(const R& rate){
   
    this->M = (T) (this->N * std::log(this->B)) / (rate * this->B);
    this->F.resize(this->M * this->N); // Setting the size of the coding matrix  F is N*M matrix 
    double std_dev = std::sqrt(1.0 / this->L); // standard deviation 
    
    std::normal_distribution<double> dist(0.0, std_dev);
    
    for (int i = 0; i < this->M; ++i)
    {
        for (int j = 0; j < this->N; ++j)
        {
            this->F[i*this->N+j] = dist(gen);
        }
        
    }
    
};
/*
    Generate a codeword y from the code message x using the code matrix F
*/
template <typename T>
template <typename R>
void AMP<T>::gen_codeword(const R& signal_to_noise_ratio){
    this->snr = signal_to_noise_ratio;
    
}


#endif // AMP_H