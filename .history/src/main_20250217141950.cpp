#include <iostream>
#include <vector>
#include <cassert>

#include "../include/amp.hpp"
#include "../include/utils.hpp"
/**
 * NOTE: Take section length and alphabet size as a command line input
 * NOTE: add a help option later (not urgent)
 * NOTE: Immplement the algorithms
 * NOTE: Use templates to make things easier
 */

int main(int argc, char **argv)
{

    int L = 2;      // Number of sections per message
    int B = 4;      // Size of a single section
    double c{1.0; // Power allocation value
    double rate{1.3};
    double snr{15.0};

    for (int i = 1; i < argc; i++)
    {
        if ((std::string(argv[i]) == "-l" || std::string(argv[i]) == "--section-length")&& i + 1 < argc)
        {
            L = std::atoi(argv[++i]);
        }
        if ((std::string(argv[i]) == "-b"|| std::string(argv[i]) == "--section-size") && i + 1 < argc)
        {
            B = std::atoi(argv[++i]);
        }
        if ((std::string(argv[i]) == "-c" || std::string(argv[i]) == "--power-allocation")&& i + 1 < argc)
        {
            c = std::atof(argv[++i]);
        }
        if ((std::string(argv[i]) == "-r" || std::string(argv[i]) == "--rate") && i + 1 < argc)
        {
            rate = std::atof(argv[++i]);
        }
        if ((std::string(argv[i]) == "-snr" || std::string(argv[i]) == "--signal-to-noise") && i + 1 < argc)
        {
            snr = std::atof(argv[++i]);
        }
        if((std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"))
        {
            std::cout<<"Help message not immplemented yet \n";
            std::exit(0);
        }
    }
    // Assert that the number of section and the section length are powers of 2
    assert(is_power_of_two(L) && is_power_of_two(B) && "L and B must be powers of 2");
    
    // Print out the parameters used 
    std::cout<<"Number of sections: "<<L<<"\n";
    std::cout<<"Section size: "<<B<<"\n";
    std::cout<<"Power allocation: "<<c<<"\n";
    std::cout<<"Communication rate: "<<rate<<"\n";
    std::cout<<"Signal to noise ratio: "<<snr<<"\n\n";

    // Intilize the amp class 
    AMP my_amp(L, B, c, rate, snr);

    // Generate sparse code 
    my_amp.gen_sparse_code();

    // Generate a design matrix 
    my_amp.gen_design_matrix();

    // Generate the corresponding codeword 
    my_amp.gen_codeword();

    std::cout << "Message: \n\n";
    my_amp.print_code_message();
    std::cout << "\n\n";

    std::cout << "Design matrix: \n\n";
    my_amp.print_design_matrix();
    std::cout << "\n\n";

    std::cout << "Codeword: \n\n";
    my_amp.print_code_word();
    std::cout << "\n\n";

    
    return 0;
}