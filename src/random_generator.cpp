#include "../include/random_generator.h"

RandomGenerator::RandomGenerator()
    : gen(std::random_device{}()) {}

int RandomGenerator::get_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}