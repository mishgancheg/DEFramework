#pragma once
#include "Individual.hpp"
#include <vector>
#include <functional>
#include <random>

// Represents a population of individuals
class Population {
private:
    std::vector<Individual> individuals;
    std::function<double(const std::vector<double>&)> objective;

    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

    double min_bound, max_bound;
    int dimension;

public:
    Population(int size, int dim,
        std::function<double(const std::vector<double>&)> objective,
        double min, double max);

    void evaluate();
    Individual& best();
    int size() const;

    // === Getters ===
    std::vector<Individual>& getIndividuals();                // modification
    const std::vector<Individual>& getIndividuals() const;    // reading

    std::mt19937& getRNG();                                   
    std::uniform_real_distribution<double>& getDistribution();
    double getMinBound() const;
    double getMaxBound() const;
    int getDimension() const;

    const std::function<double(const std::vector<double>&)>& getObjective() const;


    // Вычисление fit вручную
    double evaluate(const std::vector<double>& genome) const;
};
