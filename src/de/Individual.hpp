#pragma once
#include <vector>

// Contains dim size and fitness value of the individual
struct Individual {
    std::vector<double> genome;
    double fitness;
	Individual() : fitness(0.0) {}; // Default constructor
    Individual(int dim) : genome(dim, 0.0), fitness(0.0) {}
    
};