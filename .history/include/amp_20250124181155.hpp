#ifndef AMP_H 
#define AMP_H
#include<iostream>
#include<vector> 

template<typename T>
class AMP{
    public: 
    T L; // Section size of the sparse message 
    T B; // Alphabet size of the sparse message 
    std::vector<T> code_messgae; // Sparse code for the message 
    /*
    The code is divided into L sections of length B
    B is the size of the message alphabet 
    L is the length of the message 
    message ---- > code message (sparse super position code)
    */ 
   
    AMP(const T number_of_sections=8, int section_size=2):L(number_of_sections), B(section_size){
        this.code_messgae.resize(B * L) // Setting the size of the code
    }    


    

}


#endif // AMP_H