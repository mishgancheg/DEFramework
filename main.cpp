#include "de/Population.hpp"
#include "de/DERunner.hpp"
#include "de/strategies/DE_Rand_1_Bin.hpp"
#include "de/strategies/JADE.hpp"
#include "de/strategies/L_SHADE.hpp"
#include <iostream>
#include <numbers>

// FUNCTIONS:

// Rastrigin function 
double rastrigin(const std::vector<double>& x) {
	double A = 10.0;
	double sum = A * x.size();
	for (double xi : x)
		sum += xi * xi - A * cos(2 * 3.1415926535 * xi);
	return sum;
}
//Sphere
double sphere(const std::vector<double>& x) {
    double sum = 0.0;
    for (double xi : x)
        sum += xi * xi;
    return sum;
}

double ackley(const std::vector<double>& x) {
    double a = 20.0, b = 0.2, c = 2.0 * 3.1415926535;
    int d = x.size();

    double sum1 = 0.0, sum2 = 0.0;
    for (double xi : x) {
        sum1 += xi * xi;
        sum2 += std::cos(c * xi);
    }

    return -a * std::exp(-b * std::sqrt(sum1 / d)) - std::exp(sum2 / d) + a + std::exp(1.0);
}
int main() {
	// HYPERPARAMETERS:
    int dimension = 3;
	int size_of_population = 5*dimension;
    int iterations = 1000;
	double M = 0.5; // Mutation factor
	double CR = 0.9; // Crossover probabilityx

    // sphere - rand strategy
    Population pop_1(size_of_population, dimension, sphere, -10, 10);
    DERunner runner_1(std::make_unique<DE_Rand_1_Bin>(M, CR));
    runner_1.run(pop_1, iterations);

    auto& best = pop_1.best();
    std::cout << "Best fitness for sphere func with random strategy: " << best.fitness << std::endl;

    // rastrigin - JADE strategy
    Population pop_2(size_of_population, dimension, rastrigin, -10, 10);
    DERunner runner_2(std::make_unique<JADEStrategy>(150));
    runner_2.run(pop_2, iterations);

    auto& best_2 = pop_2.best();
    std::cout << "Best fitness for rastrigin func with JADE strategy: " << best_2.fitness << std::endl;

    // Ackley - L-SHADE strategy
    int dims = 20;
    int NP_init = 100;
    int NP_min = 80;
    int archive_size = 100;
    Population pop_3(NP_init, dims, ackley, -30, 30);
    DERunner runner_3(std::make_unique<L_SHADEStrategy>(archive_size, NP_init, NP_min, iterations), 1);

    runner_3.run(pop_3, iterations);

    auto& best_3 = pop_3.best();
    std::cout << "Best fitness for Ackley func with L-SHADE strategy: " << best_3.fitness << std::endl;

}
