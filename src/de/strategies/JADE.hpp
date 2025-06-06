#pragma once

#include "de/Individual.hpp"
#include "de/Population.hpp"
#include "de/Archive.hpp"
#include "de/DEBase.hpp"


class JADEStrategy : public DEBase {
private:
    double mu_F = 0.5;
    double mu_CR = 0.5;
protected:
    Archive archive;
	double p = 0.1; // best individuals factor (%)

public:
    JADEStrategy(size_t archiveSize);

    void evolve(Population& population) override;

protected:
    Individual mutate(const Individual& Xi, const Population& population, double Fi);
    Individual crossover(const Individual& Xi, const Individual& Vi, double CR);
    void updateParameters(std::vector<double>& SF, std::vector<double>& SCR);

    // generating random numbers from this distributions
    double sampleCauchy(double location, double scale, std::mt19937& rng);
    double sampleNormal(double mean, double stddev, std::mt19937& rng);
};