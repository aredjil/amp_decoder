#ifndef AMP_H 
#define AMP_H
#include<iostream>
#include<vector> 

template<typename T>
class AMP{
    public: 
    int L; // Section size of the sparse message 
    int B; // Alphabet size of the sparse message 
    std::vector<int> code_messgae; // Sparse code for the message 
    /*
    The code is devided into L section, L is the size of the alphabet, 

    */ 
    /*
    Class constructor for AMP decoder 
    L: The section size 
    B: Number of sections
    */
    AMP(int L=8, int B=2){
        
    }    


    

}


#endif // AMP_H