#include<iostream>
#include "../include/amp.hpp"
#include<vector>
int main(int argc, char**argv){
    int L = 8; 
    int B = 4; 
    AMP<int> my_amp(L, B);
    std::cout<<my_amp.code_messgae.size()<<std::endl;     
    return 0;
}