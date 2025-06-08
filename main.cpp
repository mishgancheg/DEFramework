#include "de/Population.hpp"
#include "de/DERunner.hpp"
#include "de/strategies/DE_Rand_1_Bin.hpp"
#include "de/strategies/JADE.hpp"
#include "de/strategies/L_SHADE.hpp"
#include "de/functions/Logger.hpp"
#include <iostream>
#include <numbers>
#include <memory>
#include <functional>
#include <chrono>

// FUNCTIONS:

//Sphere
double sphere(const std::vector<double>& x) {
    double sum = 0.0;
    for (double xi : x)
        sum += xi * xi;
    return sum;
}

// Rastrigin function 
double rastrigin(const std::vector<double>& x) {
	double A = 10.0;
	double sum = A * x.size();
	for (double xi : x)
		sum += xi * xi - A * cos(2 * 3.1415926535 * xi);
	return sum;
}

// Ackley function
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

    //// sphere - rand strategy
    //Population pop_1(size_of_population, dimension, sphere, -10, 10);
    //DERunner runner_1(std::make_unique<DE_Rand_1_Bin>(M, CR));
    //runner_1.run(pop_1, iterations);

    //auto& best = pop_1.best();
    //std::cout << "Best fitness for sphere func with random strategy: " << best.fitness << std::endl;

    //// rastrigin - JADE strategy
    //Population pop_2(size_of_population, dimension, rastrigin, -10, 10);
    //DERunner runner_2(std::make_unique<JADEStrategy>(150));
    //runner_2.run(pop_2, iterations);

    //auto& best_2 = pop_2.best();
    //std::cout << "Best fitness for rastrigin func with JADE strategy: " << best_2.fitness << std::endl;

    //// Ackley - L-SHADE strategy
    //int dims = 20;
    //int NP_init = 100;
    //int NP_min = 80;
    //int archive_size = 100;
    //Population pop_3(NP_init, dims, ackley, -30, 30);
    //DERunner runner_3(std::make_unique<L_SHADEStrategy>(archive_size, NP_init, NP_min, iterations), 1);

    //runner_3.run(pop_3, iterations);

    //auto& best_3 = pop_3.best();
    //std::cout << "Best fitness for Ackley func with L-SHADE strategy: " << best_3.fitness << std::endl;


	// EXPERIMENTING WITH DIFFERENT STRATEGIES
    // диапазон
    std::vector<double> xys = { 30 };
    // количество измерений
    std::vector<int> dims = {10, 20, 30};
	// размер популяции
    std::vector<int> p_sizes = { 100, 200, 300 };
    // Функции
    std::vector<std::pair<std::string, std::function<double(const std::vector<double>&)>>> objectives = {
    {"Sphere", sphere},
    {"Rastrigin", rastrigin},
    {"Ackley", ackley}
    };

    //std::vector<ExperimentResult> results;
    //// rANDOM
    //for (auto& [name, obj] : objectives)
    //{
    //ExperimentResult result;
    //for (double xy : xys) {
    //    for (int dim : dims) {
    //        for (int p_size : p_sizes) {
    //            Population pop(dim, p_size, obj, -xy, xy);
    //            DERunner runner(std::make_unique<DE_Rand_1_Bin>(0.5, 0.9));
    //            auto start = std::chrono::steady_clock::now(); // timer

    //            runner.run(pop, iterations);

    //            auto end = std::chrono::steady_clock::now();
    //            double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();


    //            if (pop.best().fitness < result.fitness) {
    //                result.strategy = "DE_Rand_1_Bin";
    //                result.function = name;
    //                result.fitness = pop.best().fitness;
    //                result.dim = dim;
    //                result.pop_size = p_size;
    //                result.range = xy;
    //                result.generations = iterations;
    //                result.time = elapsed_ms;
    //                std::cout << "\nNew best:\n" << result;
    //                }
    //            }
    //        }
	   // }
    //    results.push_back(result);
    //}

    //// JADE
    //for (auto& [name, obj] : objectives)
    //{
    //    ExperimentResult result;
    //    for (double xy : xys) {
    //        for (int dim : dims) {
    //            for (int p_size : p_sizes) {
    //                Population pop(dim, p_size, obj, -xy, xy);
    //                DERunner runner(std::make_unique<JADEStrategy>(150));
    //                auto start = std::chrono::steady_clock::now(); // timer

    //                runner.run(pop, iterations);

    //                auto end = std::chrono::steady_clock::now();
    //                double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();


    //                if (pop.best().fitness < result.fitness) {
    //                    result.strategy = "JADE";
    //                    result.function = name;
    //                    result.fitness = pop.best().fitness;
    //                    result.dim = dim;
    //                    result.pop_size = p_size;
    //                    result.range = xy;
    //                    result.generations = iterations;
    //                    result.time = elapsed_ms;
    //                    std::cout << "\nNew best:\n" << result;
    //                }
    //            }
    //        }
    //    }
    //    results.push_back(result);
    //}

    ////L-SHADE
    //for (auto& [name, obj] : objectives)
    //{
    //    ExperimentResult result;
    //    for (double xy : xys) {
    //        for (int dim : dims) {
    //            for (int p_size : p_sizes) {
    //                Population pop(dim, p_size, obj, -xy, xy);
    //                DERunner runner(std::make_unique<L_SHADEStrategy>(100,100,80, iterations));
    //                auto start = std::chrono::steady_clock::now(); // timer

    //                runner.run(pop, iterations);

    //                auto end = std::chrono::steady_clock::now();
    //                double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();


    //                if (pop.best().fitness < result.fitness) {
    //                    result.strategy = "L-SHADE";
    //                    result.function = name;
    //                    result.fitness = pop.best().fitness;
    //                    result.dim = dim;
    //                    result.pop_size = p_size;
    //                    result.range = xy;
    //                    result.generations = iterations;
    //                    result.time = elapsed_ms;
    //                    std::cout << "\nNew best:\n" << result;
    //                }
    //            }
    //        }
    //    }
    //    results.push_back(result);
    //}

    //Logger::saveResultsToCSV(results, "C:\\M\\DE_Framework_cpp\\Exps\\BestHyps.csv");

    Population pop(30, 100, rastrigin, -30, 30);
    DERunner runner(std::make_unique<L_SHADEStrategy>(100, 100, 80, iterations));

    runner.run(pop, iterations);
    runner.getValues();

}
