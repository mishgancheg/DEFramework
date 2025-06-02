#pragma once
#include "de/Population.hpp"

class DEBase {
public:
    static constexpr double PI = 3.14159265358979323846;
    virtual void evolve(Population& pop) = 0;
    virtual ~DEBase() = default;
};