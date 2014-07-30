#pragma once

#include <functional>
#include <vector>

std::vector<double> CreateRandomDiscreteDistribution(int n, std::function<double()> randFun);
int SampleDiscreteDistribution(const std::vector<double>& dist, double rand);
