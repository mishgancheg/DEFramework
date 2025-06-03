#include "de/DERunner.hpp"

DERunner::DERunner(std::unique_ptr<DEBase> strategy, bool output): strategy(std::move(strategy)), out(output){
}

void DERunner::run(Population& pop, int generations) {
    if (out == 1) {
        for (int i = 0; i < generations; ++i) {
            strategy->evolve(pop);
            std::cout << "I: " << i << "; Best fitness: " << pop.best().fitness<< "\n";
        }
    }
    else {
        for (int i = 0; i < generations; ++i) {
            strategy->evolve(pop);
        }
    }
    
}
