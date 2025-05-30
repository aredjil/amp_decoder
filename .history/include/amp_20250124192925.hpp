#ifndef AMP_H 
#define AMP_H
#include<iostream>
#include<vector> 
#include<random>
#include<cmath>

template<typename T>
class AMP{
    private: 
    // Generate random numbers 
    std::random_device dv;
    std::mt19937 gen(dv());

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
    std::vector<T> code_messgae; // Sparse code for the message 
    /*
    Coding matrix 
    */
    std::vector<double> F; // normal random matrix with 0 mean and 1/sqrt(L) std
    AMP(const T &number_of_sections=8, const T & section_size=2):L(number_of_sections), B(section_size){
        this->code_messgae.resize(B * L, 0); // Setting the size of the code
        this->N = this->L * this->B; // Setting the size of the sparse code
    }
    // Generate sparse superposition code
    template <typename R>
    void gen_sparse_code(const R& power_allocation=1); 
    // Generate design matrix 
    template<typename R> 
    void gen_design_matrix(const R& rate);

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
    this->F.resize(this->N * this->M); // Setting the size of the coding matrix
    double std_dev = std::sqrt(1.0 / this->L); // standard deviation 
    
    std::normal_distribution<double> dist(0.0, std_dev);
    
    for (int i = 0; i < this->N; ++i)
    {
        for (int j = 0; j < this->M; ++j)
        {
            this->F[i*this->M+j] = dist(gen);
        }
        
    }
    
};


#endif // AMP_H