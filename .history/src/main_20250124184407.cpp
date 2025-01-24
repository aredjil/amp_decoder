#include<iostream>
#include "../include/amp.hpp"
#include<vector>
#include<cassert>
int main(int argc, char**argv){

    if(argc < 3){
        std::cout<<"Basic usage ./main.x <number_of_sections> <section_size>"<<std::endl;
        return 1;
    }
    int L = std::atoi(argv[1]);
    int B = std::atoi(argv[2]);
    /*
    Add assertion to make sure the section size and number of sections are powers of 2 :) 
    */
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