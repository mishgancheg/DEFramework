#pragma once
#include <string>
#include <vector>
#include <compare>
#include <limits>
#include <iostream>


// Struct to contain results of the experiment
struct ExperimentResult {
    std::string strategy;
    std::string function;
    double fitness;
    int dim;
    int pop_size;
    double range;
    int generations;
    double time;

    ExperimentResult()
        : strategy(""), function(""), fitness(std::numeric_limits<double>::max()),
        dim(0), pop_size(0), range(0), generations(0), time(0.0) {
    }
    friend std::ostream& operator<<(std::ostream& os, const ExperimentResult& r) {
        os << "Strategy: " << r.strategy << ", Function: " << r.function
            << ", Fitness: " << r.fitness
            << ", Dim: " << r.dim
            << ", PopSize: " << r.pop_size
            << ", Range: " << r.range
            << ", Generations: " << r.generations
            << "\n" << r.time<< "ms\n";
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const ExperimentResult& r);

    bool operator<(const ExperimentResult& other) const {
        return fitness < other.fitness;

    }
};


class Logger {
public:
    static void saveResultsToCSV(const std::vector<ExperimentResult>& results, const std::string& filename);
};



