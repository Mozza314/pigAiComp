#include <cassert>
#include <cmath>

#include "discreteDistributions.hpp"

std::vector<double> CreateRandomDiscreteDistribution(int n, std::function<double()> randFun)
{
    std::vector<double> p;
    
    double sum = 0.0;
    
    for (int i = 0; i != n - 1; ++i)
    {
        p.push_back((1 - sum) * (1 - std::pow(randFun(), 1.0 / (n - i - 1))));
        sum += p.back();
    }
    
    p.push_back(1 - sum);
    
    return p;
}

int SampleDiscreteDistribution(const std::vector<double>& dist, double rand)
{
    assert(!dist.empty());
    assert(0.0 <= rand && rand <= 1.0);
    
    double sum = dist[0];
    int i = 0;

    while (sum < rand && i < dist.size())
    {
        ++i;
        sum += dist[i];
    }

    if (i == dist.size())
    {
        assert(std::abs(sum - 1.0) < 0.000000001);
        assert(std::abs(rand - 1.0) < 0.000000001);
        return i - 1;
    }
    
    return i;
}
