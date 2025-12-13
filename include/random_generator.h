#pragma once
#include <random>

class RandomGenerator {
private:
    std::mt19937 gen;
    
public:
    RandomGenerator();
    int get_int(int min, int max);
};