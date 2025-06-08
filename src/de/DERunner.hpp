#pragma once
#include "de/DEBase.hpp"
#include <memory>
#include <iostream>

class DERunner {
public:
    DERunner(std::unique_ptr<DEBase> strategy, bool output = false);
    void run(Population& pop, int generations);
    std::vector<double> getValues();
private:
    std::unique_ptr<DEBase> strategy;
    bool out;
    std::vector<double> values;
};