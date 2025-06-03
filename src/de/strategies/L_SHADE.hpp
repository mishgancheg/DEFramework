#pragma once

#include "de/DEBase.hpp"
#include "de/strategies/JADE.hpp"

class L_SHADEStrategy : public JADEStrategy {
public:
    L_SHADEStrategy(size_t archiveSize, int NP_init, int NP_min, int Gmax);

    void evolve(Population& population) override;
    void setGeneration(int g);

private:
    void updateParameters(const std::vector<double>& SF, const std::vector<double>& SCR);
    void reducePopulation(Population& population, int newSize);

    std::vector<double> Fs;
    std::vector<double> CRs;
    int memoryIndex = 0; // current write index
    int H = 10; // size of memory lists 

    int iterations; // total iterations
    int curr_generation = 0; 
    int NP_init; // init size of population
    int NP_min; // min possible size of population
};