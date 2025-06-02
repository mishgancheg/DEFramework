#include "de/DERunner.hpp"

DERunner::DERunner(std::unique_ptr<DEBase> strategy)
    : strategy(std::move(strategy)) {
}

void DERunner::run(Population& pop, int generations) {
    for (int i = 0; i < generations; ++i) {
        strategy->evolve(pop);
    }
}