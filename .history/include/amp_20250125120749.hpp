#ifndef AMP_H 
#define AMP_H
#include<iostream> // Standard input output mechanism  
#include<vector> // To store the data 
#include<random> // Generate random numbers  
#include<cmath> // sqrt and log functions 
#include<algorithm> // Operations on C++ containers
#include<cblas.h> // cblas for linear algebra operations 


/*
*NOTE: Pass the seed as a paramter the class constructor. 
*/
class AMP{

    public: 
        int L; // Section size of the sparse message 
        int B; // Alphabet size of the sparse message 
        int N; // Size of the code_message/ Number of rows of the coding matrix F 
        int M; // number of columns of the coding matrix F
        /*
        The code is divided into L sections of length B
        B is the size of the message alphabet 
        L is the length of the message 
        message ---- > code message (sparse super position code)
        */ 
        std::vector<double> code_messgae; // Sparse code for the message code_message is 1 dimensional vector with N elements.
        /*
            Coding matrix 
        */
        std::vector<double> F; // normal random matrix with 0 mean and 1/sqrt(L) std
        /*
            Code word 
        */
        std::vector<double> codeword;

        AMP(const int &number_of_sections=8, const int & section_size=2)
        :L(number_of_sections), B(section_size), gen(dv()){
            
            this->code_messgae.resize(B * L, 0); // Setting the size of the code
            this->N = this->L * this->B; // Setting the size of the sparse code
        }
        /*
            Coding the message 
         */

        void gen_sparse_code(const double& power_allocation=1.0); // Generate sparse superposition code
        void gen_design_matrix(const double& rate);// Generate design matrix  
        void gen_codeword(const double& signal_to_noise_ratio);// Generate code word y
        /*
            Decoding the codeword 
        */
        void get_decoded_message(const double &snr, const double &rate, const int&t_max, const double&error_th, const double&power_allocation);

    private: 
    // Generate random numbers 
        std::random_device dv; // Random seed 
        std::mt19937 gen;      // Pseudo-number generator 



};

/*
    Function to generate sparse superposition codes.
*/
void AMP::gen_sparse_code(const double &power_allocation){
    // Iterate through the sections 
    for(int i=0;i < this->L; i++){
        // Generate a random index between 0 and section size
        std::uniform_int_distribution<int> dist(0, this->B-1); 
        int j = dist(gen); 
        this->code_messgae[i * this->B + j] = power_allocation; 
    }  
}
/*
    Function to generate design matrix.
*/
void AMP::gen_design_matrix(const double& rate){
   
    this->M = (int)(this->N * std::log2(this->B)) / (rate * this->B);
    
    this->F.resize(this->M * this->N); // Setting the size of the coding matrix  F is N*M matrix 
    double std_dev = std::sqrt(1.0 / this->L); // standard deviation 
    
    std::normal_distribution<double> dist(0.0, std_dev);
    /*
        Fill the matrix with gaussian enteries 
    */
    std::generate(this->F.begin(), this->F.end(), [&](){return dist(this->gen);});
    
};
/*
    Generate a codeword y from the code message x using the code matrix F
*/
void AMP::gen_codeword(const double& snr){
    
    this->codeword.resize(this->M);

    std::vector<double> noise(this->M, 0); // Noise buffer 

    std::normal_distribution<double> dist(0.0, snr);

    std::generate(noise.begin(), noise.end(), [&](){return dist(this->gen);});
    
    // Generate the codeword
    cblas_dgemv(
        CblasRowMajor, 
        CblasNoTrans, 
        this->M, this->N, 
        1.0, 
        this->F.data(), this->N,
        this->code_messgae.data(), 1,
        0.0, 
        this->codeword.data(), 1.0         
    );

}


/*
 Decode the codeword 
*/
void AMP::get_decoded_message(const double &snr, const double &rate, const int&t_max, const double&error_threshold, const double&power_allocation){

    double delta = 1 + error_threshold; 
    int t =0; 
    

    std::vector<double> FF(this->F); // copy the design matrix 
    // compute F**2 
    std::transform(
        FF.begin(), 
        FF.end(), 
        FF.begin(), 
        [](auto element){
            return element * element;
        }
    );
    
    std::vector<double> estimation(this->N);
    std::vector<double> v(this->N, 1.0/(snr*this->B));
    std::vector<double> V(this->M, 0.0); 

    std::vector<double> z(this->codeword); 
    
    std::vector<double> ser(t_max, 1.0); 

    while(t < t_max && delta > error_threshold){
        std::vector<double> V_old(V); 
        std::vector<double> z_old(z); 
        std::vector<double> estimation_old(estimation);

        // Compute F**2.


    }

}

#endif // AMP_H