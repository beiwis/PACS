#include <iomanip>
#include <iostream>
#include <limits>
#include <chrono>

// Allow to change the floating point type
using my_float = long double;

my_float pi_taylor(size_t steps) {
    (void)steps; // ensure no warnings with unused variable
    my_float sum_pi = 0.0f;
    int sign = 1;
    for (size_t i = 0; i < steps; ++i){
        sum_pi +=  sign / (2*i + 1);
        sign = -sign;
    }
    return 4.0f * sum_pi;
}

int main(int argc, const char *argv[]) {

   

    // read the number of steps from the command line
    if (argc != 2) {
        std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
        exit(1);

    }

    size_t steps = std::stoll(argv[1]); // Parses the input argument to long long
    // Start the clock
        auto start = std::chrono::high_resolution_clock::now();   
        auto pi = pi_taylor(steps);

    // Stop the clock
        auto end = std::chrono::high_resolution_clock::now();

    // Calculate the time in miliseconds
        std::chrono::duration<double, std::milli> duration = end - start;


    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<my_float>::digits10 + 1)
        << pi << std::endl;
    std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;
    
}