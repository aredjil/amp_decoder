
#include "../include/amp.hpp"

/**
 * To do list 
 * TODO: Make the power allocation private. 
 * TODO: Implement spatially coupled coding matrix 
 */
/**
 *  Function to check if a number is a power of 2 
 */ 
bool is_power_of_two(int n){
    return n > 0 && (n & (n - 1)) == 0; 
}

int main(int argc, char **argv)
{
    std::cout<<std::fixed<<std::setprecision(4); // Set the precision of the output 
    // Deafult values of the paramters that will be passed to the AMP class 
    int num_sections{1024};      // Number of sections per message
    int section_size{4};      // Size of a single section
    const data_t power_allocation{1.0}; // Power allocation value
    data_t comm_rate{1.3};
    data_t snr{15.0};
    data_t ep{10E-8};
    int t_max{25};
    // Get the paramters from the user 
    for (int i = 1; i < argc; i++)
    {
        // Get the number sections 
        if ((std::string(argv[i]) == "-l" || std::string(argv[i]) == "--section-length")&& i + 1 < argc)
        {
            num_sections = std::atoi(argv[++i]);
        }
        // Get the section size
        if ((std::string(argv[i]) == "-b"|| std::string(argv[i]) == "--section-size") && i + 1 < argc)
        {
            section_size = std::atoi(argv[++i]);
        }
        // Get the communication rate 
        if ((std::string(argv[i]) == "-r" || std::string(argv[i]) == "--coomunication-rate") && i + 1 < argc)
        {
            comm_rate = std::atof(argv[++i]);
        }
        // Get the signal to noise ratio 
        if ((std::string(argv[i]) == "-snr" || std::string(argv[i]) == "--signal-to-noise") && i + 1 < argc)
        {
            snr = std::atof(argv[++i]);
        }
        // Print the help message 
        if((std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help"))
        {
            std::cout<<"Usage: \n\n";
            std::cout<<"./<excutable> [OPTIONS] \n";

            std::cout<<"OPTIONS:\n\n";
            std::cout<<"-l, --section-length  \n";
            std::cout<<"Number of sections used in the randomly generated sparse superposition code\n";
            std::cout<<"must be a power of 2: 2, 4, 8, ...\n";

            std::cout<<"-b,--section-size\n";
            std::cout<<"Section size used in the randomly generated sparse superposition code\n";
            std::cout<<"must be a power of 2: 2, 4, 8, ...\n";

            std::cout<<"-r, --communication-rate\n";
            std::cout<<"Communication rate of the transmission\n";

            std::cout<<"-snr, --signal-to-noise\n";
            std::cout<<"Signal to noise ratio\n";

            std::cout<<"-h, --help\n";
            std::cout<<"Print the help message\n";
            std::exit(0);
        }
        if ((std::string(argv[i]) == "-t" || std::string(argv[i]) == "--t_max")&& i + 1 < argc)
        {
            t_max = std::atoi(argv[++i]);
        }
        if ((std::string(argv[i]) == "-e" || std::string(argv[i]) == "--threshold")&& i + 1 < argc)
        {
            ep = std::atof(argv[++i]);
        }

    }
    // Assert that the number of section and the section length are powers of 2
    assert(is_power_of_two(num_sections) && is_power_of_two(section_size) && "L and B must be powers of 2");
    // Intilize the amp class 
    AMP<data_t> my_amp(num_sections, section_size, power_allocation, comm_rate, snr); // data_t is defined in the header amp.hpp 

    // Generate sparse code 
    my_amp.gen_sparse_code();

    // Generate a design matrix 
    my_amp.gen_design_matrix();

    // Generate the corresponding codeword 
    my_amp.gen_codeword();

    auto start = std::chrono::high_resolution_clock::now();
    my_amp.solve(t_max, ep);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout<<"#The decoder took: "<<duration.count()<<" s\n\n";
    return 0;
}