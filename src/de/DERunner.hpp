#pragma once
#include "de/DEBase.hpp"
#include <memory>

class DERunner {
public:
    DERunner(std::unique_ptr<DEBase> strategy);
    void run(Population& pop, int generations);

private:
    std::unique_ptr<DEBase> strategy;
};