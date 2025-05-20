#ifndef AMP_H 
#define AMP_H
#include<iostream> // Standard input output mechanism  
#include<vector> // To store the data 
#include<random> // Generate random numbers  
#include<cmath> // sqrt and log functions 
#include<algorithm> // Operations on C++ containers
#include<cblas.h> // cblas for linear algebra operations 


// FIXME:
template<typename T>
class AMP{

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
            Code word 
        */
        std::vector<double> codeword; 
        AMP(const T &number_of_sections=8, const T & section_size=2)
        :L(number_of_sections), B(section_size), gen(dv()){
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

    private: 
    // Generate random numbers 
        std::random_device dv; // Random seed 
        std::mt19937 gen;      // Pseudo-number generator 



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
    /*
        Fill the matrix with gaussian enteries 
    */
    std::generate(this->F.begin(), this->F.end(), [&](){return dist(this->gen);});
    
};
/*
    Generate a codeword y from the code message x using the code matrix F
*/
template <typename T>
template <typename R>
void AMP<T>::gen_codeword(const R& snr){
    
    this->codeword.resize(this->M);

    std::vector<R> noise(this->M, 0); // Noise buffer 

    std::normal_distribution<double> dist(0.0, snr);

    std::generate(noise.begin(), noise.end(), [&](){return dist(this->gen);});
    
    cblas_dgemv(
        CblasRowMajor, 
        CblasNoTrans, 
        this->M, this->N, 
        1.0, 
        this->F.data(), this->N,
        this->code_messgae.data(), 1,
        0.0, 
        this->codeword.data(), 1.0         
    );

}


#endif // AMP_H