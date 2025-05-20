#ifndef UTILS_H 
#define UTILS_H
/*
Check if a number n is a power of 2.
*/
bool is_power_of_two(int n){
    return n > 0 && (n & (n - 1)) == 0; 
}
#endif //UTILS_H