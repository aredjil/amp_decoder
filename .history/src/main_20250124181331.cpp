#include<iostream>
#include "../include/amp.hpp"
#include<vector>
int main(int argc, char**argv){
    int L =2; 
    int B = 4; 
    AMP<int> my_amp(L, B);
    for(auto val: my_amp.code_messgae){
        std::cout<<" "<<val<<" "
    }      
    return 0;
}