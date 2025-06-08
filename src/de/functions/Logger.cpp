#include "Logger.hpp"
#include <fstream>
#include <iomanip>


void Logger::saveResultsToCSV(const std::vector<ExperimentResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    file << "Strategy,Function,BestFitness,Dim,PopSize,Range,Generations,TimeSec\n";
    for (const auto& r : results) {
        file << r.strategy << ","
            << r.function << ","
            << std::setprecision(10) << r.fitness << ","
            << r.dim << ","
            << r.pop_size << ","
            << r.range << ","
            << r.generations << ","
            << std::setprecision(6) << r.time << "\n";
    }
    file.close();
}

