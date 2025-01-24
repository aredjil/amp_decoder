#ifndef AMP_H 
#define AMP_H
#include<iostream>
#include<vector> 
#include<random>
// Generate random numbers 
std::random_device dv;
std::mt19937 gen(dv());

template<typename T>
class AMP{
    public: 
    T L; // Section size of the sparse message 
    T B; // Alphabet size of the sparse message 
    T N; 
    std::vector<T> code_messgae; // Sparse code for the message 
    /*
    The code is divided into L sections of length B
    B is the size of the message alphabet 
    L is the length of the message 
    message ---- > code message (sparse super position code)
    */ 
    AMP(const T &number_of_sections=8, const T & section_size=2):L(number_of_sections), B(section_size){
        this->code_messgae.resize(B * L, 0); // Setting the size of the code
        this->N = this->L * this->B; // Setting the size of the sparse code
    }
    // Generate sparse superposition code
    template <typename R>
    void gen_sparse_code(const R& power_allocation=1); 
    // Generate design matrix 
    template<typename R> 
    gen_design_matrix(const R& rate);

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
void AMP<T>::gen_design_matrix(const R& rate);


#endif // AMP_H