
#include "../include/amp.hpp"
// #include "../include/utils.hpp"
/**
 * NOTE: add a help option later (not urgent)
 * NOTE: Immplement the algorithms
 * NOTE: Use templates to make things easier
 */

 bool is_power_of_two(int n){
    return n > 0 && (n & (n - 1)) == 0; 
}

int main(int argc, char **argv)
{
    std::cout<<std::fixed<<std::setprecision(6);
    int num_sections{2048};      // Number of sections per message
    int section_size{4};      // Size of a single section
    data_t power_allocation{1.0}; // Power allocation value
    data_t comm_rate{1.3};
    data_t snr{15.0};
    data_t ep=10E
    int t_max{25};


    for (int i = 1; i < argc; i++)
    {
        if ((std::string(argv[i]) == "-l" || std::string(argv[i]) == "--section-length")&& i + 1 < argc)
        {
            num_sections = std::atoi(argv[++i]);
        }
        if ((std::string(argv[i]) == "-b"|| std::string(argv[i]) == "--section-size") && i + 1 < argc)
        {
            section_size = std::atoi(argv[++i]);
        }
        if ((std::string(argv[i]) == "-c" || std::string(argv[i]) == "--power-allocation")&& i + 1 < argc)
        {
            power_allocation = std::atof(argv[++i]);
        }
        if ((std::string(argv[i]) == "-r" || std::string(argv[i]) == "--rate") && i + 1 < argc)
        {
            comm_rate = std::atof(argv[++i]);
        }
        if ((std::string(argv[i]) == "-snr" || std::string(argv[i]) == "--signal-to-noise") && i + 1 < argc)
        {
            snr = std::atof(argv[++i]);
        }
        if((std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"))
        {
            std::cout<<"Help message not immplemented yet :) \n";
            std::exit(0);
        }
    }
    // Assert that the number of section and the section length are powers of 2
    assert(is_power_of_two(num_sections) && is_power_of_two(section_size) && "L and B must be powers of 2");
    
    // Print out the parameters used 
    // std::cout<<"Number of sections: "<<num_sections<<"\n";
    // std::cout<<"Section size: "<<section_size<<"\n";
    // std::cout<<"Power allocation: "<<power_allocation<<"\n";
    // std::cout<<"Communication rate: "<<comm_rate<<"\n";
    // std::cout<<"Signal to noise ratio: "<<snr<<"\n\n";

    // Intilize the amp class 
    AMP my_amp(num_sections, section_size, power_allocation, comm_rate, snr);

    // Generate sparse code 
    my_amp.gen_sparse_code();

    // Generate a design matrix 
    my_amp.gen_design_matrix();

    // Generate the corresponding codeword 
    my_amp.gen_codeword();

    // std::cout<<"Testing the first function\n\n";
    // auto start = std::chrono::high_resolution_clock::now();
    my_amp.solve();
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    // std::cout<<"The solver took: "<<duration.count()<<" s\n\n";
    return 0;
}