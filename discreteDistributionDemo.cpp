#include <cstdlib>
#include <ctime>
#include <iostream>

#include "discreteDistributions.hpp"

int main()
{
    std::srand(std::time(0));
    std::vector<double> dist = CreateRandomDiscreteDistribution(6, [](){ return 1.0 * std::rand() / RAND_MAX; });
    
    for (int i = 0; i != 6; ++i)
    {
        std::cout << i + 1 << ": " << dist[i] << std::endl;
    }
    
    for (int i = 0; i != 1000000; ++i)
    {
        std::cout << 1 + SampleDiscreteDistribution(dist, 1.0 * std::rand() / RAND_MAX) << std::endl;
    }
    
    return 0;
}
