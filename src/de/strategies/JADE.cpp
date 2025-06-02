#include "JADE.hpp"
#include <algorithm>
#include <random>
#include <cmath>


JADEStrategy::JADEStrategy(size_t archiveSize) : archive(archiveSize) {}

void JADEStrategy::evolve(Population& population) {
    std::vector<double> SF, SCR;
    std::vector<Individual> newGeneration;

    auto& individuals = population.getIndividuals();
    size_t D = individuals[0].genome.size(); //  size of individual

    for (size_t i = 0; i < individuals.size(); ++i) {
        double Fi = std::min(1.0, std::max(0.0, mu_F + 0.1 * tan(PI * (rand() / (double)RAND_MAX - 0.5)))); // making new F value. Koshi destr
        double CRi = std::min(1.0, std::max(0.0, mu_CR + 0.1 * (rand() / (double)RAND_MAX))); // making new CR value. Normal distr

        Individual Vi = mutate(individuals[i], population, Fi); // new indiv 
        Individual Ui = crossover(individuals[i], Vi, CRi); // 

        Ui.fitness = population.evaluate(Ui.genome); // calculating fitness for new indiv.

        if (Ui.fitness < individuals[i].fitness) {
            archive.add(individuals[i]);
            newGeneration.push_back(Ui);
            SF.push_back(Fi);
            SCR.push_back(CRi);
        }
        else {
            newGeneration.push_back(individuals[i]);
        }
    }

    individuals = std::move(newGeneration);
    updateParameters(SF, SCR);
}

Individual JADEStrategy::mutate(const Individual& Xi, const Population& population, double Fi) {
    const auto& pop = population.getIndividuals();
    size_t NP = pop.size();
    size_t D = Xi.genome.size();

    // sort by fitness value
    std::vector<Individual> sorted = pop;
    std::sort(sorted.begin(), sorted.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;
        });

    int pbestIndex = rand() % std::max(1, int(p * NP)); // random index from best indexes
    const Individual& Xpbest = sorted[pbestIndex]; // on of best individuals

    // Xr1 - indiv. from pop which is not equal Xi or Xpbest
    // Xr2 - indiv. from pop + archive which is not equal Xi, Xpbest or Xr1
    Individual Xr1, Xr2;
    do {
        Xr1 = pop[rand() % NP];
    } while (Xr1.genome == Xi.genome || Xr1.genome == Xpbest.genome);

    // unionPool = archive and pop together
    std::vector<Individual> unionPool = pop; 
    const auto& arc = archive.getAll();
    unionPool.insert(unionPool.end(), arc.begin(), arc.end());
    do {
        Xr2 = unionPool[rand() % unionPool.size()];
    } while (Xr2.genome == Xi.genome || Xr2.genome == Xr1.genome || Xr2.genome == Xpbest.genome);
    Individual V;
    V.genome.resize(D);
    for (int j = 0; j < D; ++j) {

        // calculating genome value and clamping in (min, max)
        double val = Xi.genome[j] + Fi * (Xpbest.genome[j] - Xi.genome[j]) + Fi * (Xr1.genome[j] - Xr2.genome[j]);
        V.genome[j] = std::clamp(val, population.getMinBound(), population.getMaxBound());
    }

    return V;
}

Individual JADEStrategy::crossover(const Individual& Xi, const Individual& Vi, double CR) {
    size_t D = Xi.genome.size();
    Individual U = Xi;
    int jrand = rand() % D;
    U.fitness = -1; // default fitness value for indiv. U

    for (int j = 0; j < D; ++j) {
        if (rand() / (double)RAND_MAX < CR || j == jrand) {
            U.genome[j] = Vi.genome[j];
        }
    }
    return U;
}

void JADEStrategy::updateParameters(std::vector<double>& SF, std::vector<double>& SCR) {
    if (SF.empty()) return;

    // Weighted Lehmer mean
    double sumF = 0, sumF2 = 0;
    for (double f : SF) {
        sumF += f * f;
        sumF2 += f;
    }
    mu_F = sumF / sumF2;

    double sumCR = 0;
    for (double cr : SCR) sumCR += cr;
    mu_CR = sumCR / SCR.size();
}
