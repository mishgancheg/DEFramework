#pragma once
#include "de/DEBase.hpp"

class DE_Rand_1_Bin : public DEBase {
public:
    DE_Rand_1_Bin(double F, double CR);
    void evolve(Population& pop) override;

private:
    double F, CR;
};