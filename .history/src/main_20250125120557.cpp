#include<iostream>
#include<vector>
#include<cassert>

#include "../include/amp.hpp"
#include "../include/utils.hpp"
int main(int argc, char**argv){

    if(argc < 3){
        std::cout<<"Basic usage ./main.x <number_of_sections> <section_size>"<<std::endl;
        return 1;
    }
    int L = std::atoi(argv[1]);
    int B = std::atoi(argv[2]);
    assert(is_power_of_two(L) && is_power_of_two(B) && "L and B must be powers of 2");
    /*
    Add assertion to make sure the section size and number of sections are powers of 2 :) 
    */
    int power_allocation = 2;
    double rate{1.3};
    double snr{15};


    AMP my_amp(L, B);

    my_amp.gen_sparse_code(power_allocation);

    my_amp.gen_design_matrix(1.3);
    my_amp.gen_design_matrix(rate);
    // Test print for the coding matrix F 
    #ifdef PRINT_F
    for (int i = 0; i < my_amp.M; i++)
    {   
        for (int j = 0; j < my_amp.N; j++)
        {
            std::cout << " "<< my_amp.F[i* my_amp.N+j]<<" ";
        }
        std::cout<<std::endl;
    }
    #endif    

    #ifdef PRINT_C    
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B; j++)
        {
            std::cout<<" "<<my_amp.code_messgae[i*B+j]<<" ";
        }
        std::cout<<std::endl;
        
    }
    #endif 
    my_amp.gen_codeword(snr);
    my_amp.get_decoded_message(const double &snr, const double &rate, 1.0,  1.0, 1.0)
    return 0;   
}