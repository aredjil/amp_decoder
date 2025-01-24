#include<iostream>
#include "../include/amp.hpp"
#include<vector>
int main(int argc, char**argv){
    if(argc < 3){
        std:::cout<<" Usage main.x <number of section> <section size>"<<std::endl;
    }
    int L = 
    // int B = 4; 
    AMP<int> my_amp(L, B);
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout<<" "<<my_amp.code_messgae[i*B+j]<<" ";
        }
        std::cout<<std::endl;
        
    }
    
    return 0;
}