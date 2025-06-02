#include "Archive.hpp"
#include <stdexcept>

Archive::Archive(size_t maxSize) : maxSize(maxSize) {} 

void Archive::add(const Individual& ind) {
    if (individuals.size() < maxSize) {
        individuals.push_back(ind);
    }
    else {
        // Replace random 
        size_t idx = rand() % individuals.size();
        individuals[idx] = ind;
    }
}

const Individual& Archive::getRandom() const {
    if (individuals.empty()) {
        throw std::runtime_error("Archive is empty");
    }
    size_t idx = rand() % individuals.size();
    return individuals[idx];
}

const std::vector<Individual>& Archive::getAll() const {
    return individuals;
}

void Archive::clear() {
    individuals.clear();
}

size_t Archive::size() const {
    return individuals.size();
}
