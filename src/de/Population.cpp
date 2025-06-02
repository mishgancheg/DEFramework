#include "de/Population.hpp"
#include <algorithm>

Population::Population(int size, int dim,
    std::function<double(const std::vector<double>&)> objective,
    double min, double max) :
    objective(objective),
    rng(std::random_device{}()),
    dist(min, max),
    min_bound(min), max_bound(max),
    dimension(dim)
{   
    individuals.reserve(size);
    for (int i = 0; i < size; ++i) {
        Individual ind(dim);
        for (auto& gene : ind.genome) {
			gene = dist(rng); // adding inbound random values
        }
        individuals.push_back(ind);
    }
    evaluate();
}

void Population::evaluate() {
    for (auto& ind : individuals) {
        ind.fitness = objective(ind.genome);
    }
}

Individual& Population::best() {
    return *std::min_element(individuals.begin(), individuals.end(),
        [](const Individual& a, const Individual& b) {
            return a.fitness < b.fitness;
        });
}

int Population::size() const {
    return static_cast<int>(individuals.size());
}

double Population::evaluate(const std::vector<double>& genome) const {
    return objective(genome);
}


// --- Getters ---
std::vector<Individual>& Population::getIndividuals() {
    return individuals;
}

const std::vector<Individual>& Population::getIndividuals() const {
    return individuals;
}

std::mt19937& Population::getRNG() {
    return rng;
}

std::uniform_real_distribution<double>& Population::getDistribution() {
    return dist;
}

double Population::getMinBound() const {
    return min_bound;
}

double Population::getMaxBound() const {
    return max_bound;
}

int Population::getDimension() const {
    return dimension;
}

const std::function<double(const std::vector<double>&)>& Population::getObjective() const {
    return objective;
}


