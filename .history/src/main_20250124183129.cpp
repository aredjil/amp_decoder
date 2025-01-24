#include<iostream>
#include "../include/amp.hpp"
#include<vector>
int main(int argc, char**argv){
    int L = 8; 
    int B = 4; 
    AMP<int> my_amp(L, B);
    for(int i; i < L;++i){
        for (int j = 0; j < L; ++j)
        {
            std::cout<<my_amp.code_messgae[i*B+j]<<" "
        }
        
    }      
    return 0;
}