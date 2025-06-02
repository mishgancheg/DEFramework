#pragma once

#include <vector>
#include <cstdlib>
#include "Individual.hpp" 

class Archive {
private:
    std::vector<Individual> individuals;
    size_t maxSize;

public:
    Archive(size_t maxSize);

    void add(const Individual& ind);
    const Individual& getRandom() const;
    const std::vector<Individual>& getAll() const;
    void clear();
    size_t size() const;
};
