// L_SHADEStrategy.hpp
#include "L_SHADE.hpp"
#include <algorithm>
#include <random>
#include <cmath>

L_SHADEStrategy::L_SHADEStrategy(
    size_t archiveSize, 
    int NP_init, 
    int NP_min,
    int iterations
):  JADEStrategy(archiveSize),
    NP_init(NP_init),
    NP_min(NP_min),
    iterations(iterations) {
    Fs = std::vector<double>(H, 0.5);
    CRs = std::vector<double>(H, 0.5);
}

void L_SHADEStrategy::setGeneration(int g) {
    curr_generation = g;
}

void L_SHADEStrategy::evolve(Population& pop) {
    std::vector<double> SF, SCR;
    std::vector<Individual> newGeneration;
    auto& individuals = pop.getIndividuals();
    int NP = individuals.size();
    int D = individuals[0].genome.size();

    // calculating current pop size
    int NP_new = std::round(NP_min + (NP_init - NP_min) * (iterations - curr_generation) / (double)iterations);

    for (int i = 0; i < NP; ++i) {
        int k = rand() % H;
        double Fi = std::clamp(sampleCauchy(Fs[k], 0.1, pop.getRNG()), 0.0, 1.0); // making new F value. Cauchy distr [0;1]
        double CRi = std::clamp(sampleNormal(CRs[k], 0.1, pop.getRNG()), 0.0, 1.0); // making new CR value. Normal distr [0;1]

        Individual Vi = mutate(individuals[i], pop, Fi);
        Individual Ui = crossover(individuals[i], Vi, CRi);

        Ui.fitness = pop.evaluate(Ui.genome);

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

    // reducing population (LPSR)
    reducePopulation(pop, NP_new);
}

void L_SHADEStrategy::reducePopulation(Population& population, int newSize) {
    auto& individuals = population.getIndividuals();
    if ((int)individuals.size() > newSize) {
        std::sort(individuals.begin(), individuals.end(), [](const Individual& a, const Individual& b) {
            return a.fitness < b.fitness;
            });
        individuals.resize(newSize);
    }
}

void L_SHADEStrategy::updateParameters(const std::vector<double>& SF, const std::vector<double>& SCR) {
    if (SF.empty()) return;

    double sumW = 0;
    std::vector<double> weights;
    for (double f : SF) {
        double w = f * f;
        weights.push_back(w);
        sumW += w;
    }

    double muF = 0;
    for (size_t i = 0; i < SF.size(); ++i)
        muF += weights[i] * SF[i];
    muF /= sumW;

    double muCR = 0;
    for (double cr : SCR) muCR += cr;
    muCR /= SCR.size();

    Fs[memoryIndex] = muF;
    CRs[memoryIndex] = muCR;
    memoryIndex = (memoryIndex + 1) % H;
}


