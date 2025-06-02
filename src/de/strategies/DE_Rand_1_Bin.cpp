#include "de/strategies/DE_Rand_1_Bin.hpp"
#include <random>
#include <algorithm>

DE_Rand_1_Bin::DE_Rand_1_Bin(double F, double CR) : F(F), CR(CR) {}

void DE_Rand_1_Bin::evolve(Population& pop) {
    int dim = pop.getDimension();
    std::uniform_int_distribution<> idx_dist(0, pop.size() - 1);
    std::uniform_real_distribution<> cr_dist(0.0, 1.0);

    for (int i = 0; i < pop.size(); ++i) {
		// Getting unique indices for a, b, c (using for mutation)
        int a, b, c;
        do { a = idx_dist(pop.getRNG()); } while (a == i);
        do { b = idx_dist(pop.getRNG()); } while (b == i || b == a);
        do { c = idx_dist(pop.getRNG()); } while (c == i || c == a || c == b);

		// Making mutant by formula x_a + F * (x_b - x_c)
        std::vector<double> mutant(dim);
        for (int j = 0; j < dim; ++j)
            mutant[j] = pop.getIndividuals()[a].genome[j] + F * (pop.getIndividuals()[b].genome[j] - pop.getIndividuals()[c].genome[j]);

        std::vector<double> trial(dim);
        int R = idx_dist(pop.getRNG()) % dim;
        for (int j = 0; j < dim; ++j) {
            if (cr_dist(pop.getRNG()) < CR || j == R)
                trial[j] = std::clamp(mutant[j], pop.getMinBound(), pop.getMaxBound());
            else
                trial[j] = pop.getIndividuals()[i].genome[j];
        }

        double trial_fit = pop.evaluate(trial);
        if (trial_fit < pop.getIndividuals()[i].fitness) {
            pop.getIndividuals()[i].genome = trial;
            pop.getIndividuals()[i].fitness = trial_fit;
        }
    }
}