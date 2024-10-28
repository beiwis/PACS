#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;

void
pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step) {

    my_float sum_pi = 0.0f;
    int sign = start_step & 0x1 ? -1 : 1;
    
    for (size_t i = start_step; i < stop_step; ++i){
        sum_pi +=  sign / static_cast<my_float>(2*i + 1);
        sign = -sign;
    }
    output[thread_id] = sum_pi;

}

std::pair<size_t, size_t>
usage(int argc, const char *argv[]) {
    // read the number of steps from the command line
    if (argc != 3) {
        std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
        exit(1);
    }

    size_t steps = std::stoll(argv[1]);
    size_t threads = std::stoll(argv[2]);

    if (steps < threads ){
        std::cerr << "The number of steps should be larger than the number of threads" << std::endl;
        exit(1);

    }
    return std::make_pair(steps, threads);
}

typedef struct {
    size_t large_chunk;
    size_t small_chunk;
    size_t split_item;
} chunk_info;

// For a given number of iterations N and threads
// the iterations are divided:
// N % threads receive N / threads + 1 iterations
// the rest receive N / threads
constexpr chunk_info
split_evenly(size_t N, size_t threads)
{
    return {N / threads + 1, N / threads, N % threads};
}

std::pair<size_t, size_t>
get_chunk_begin_end(const chunk_info& ci, size_t index)
{
    size_t begin = 0, end = 0;
    if (index < ci.split_item ) {
        begin = index*ci.large_chunk;
        end = begin + ci.large_chunk; // (index + 1) * ci.large_chunk
    } else {
        begin = ci.split_item*ci.large_chunk + (index - ci.split_item) * ci.small_chunk;
        end = begin + ci.small_chunk;
    }
    return std::make_pair(begin, end);
}

int main(int argc, const char *argv[]) {

    // Start the clock
        auto start = std::chrono::high_resolution_clock::now(); 

    auto ret_pair = usage(argc, argv);
    auto steps = ret_pair.first;
    auto threads = ret_pair.second;

    my_float pi;

    // please complete missing parts

    std::vector<my_float> sums(threads, 0.0);
    std::vector<std::thread> thread_vector;

    auto chunks = split_evenly(steps, threads);
    for(size_t i = 0; i < threads; ++i) {
        auto begin_end = get_chunk_begin_end(chunks, i);
        thread_vector.push_back(std::thread(pi_taylor_chunk, std::ref(sums), i, begin_end.first, begin_end.second));
        std::cout << i << ", " << begin_end.first << ", " << begin_end.second << std::endl;
        }
    for( size_t i = 0; i < threads; ++i)
        thread_vector[i].join();

    // calculate pi's final value
    pi = std::accumulate(sums.begin(), sums.end(), 0.0L) * 4.0;

    // Stop the clock
        auto end = std::chrono::high_resolution_clock::now();

    // Calculate the time in miliseconds
        std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;
    std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;
    
}