#ifndef UTILS_H 
#define UTILS_H
#include<iostream>
/*
Check if a number n is a power of 2.
*/
bool is_power_of_two(int n){
    return n > 0 && (n & (n - 1)) == 0; 
}
// Compute matrix vector multiplication 
void compute_mat_vec_mul(const std::vector<double>& mat, const std::vector<double> &vec, std::vector<double>&result){
    cblas_dgemv(
        CblasRowMajor,
        CblasNoTrans,
        this->M, this->N,
        1.0,
        F_square.data(), this->N,
        v.data(), 1,
        0.0,
        V.data(), 1.0);
}
#endif //UTILS_H