#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <random>
#include <limits>
using namespace std;

double getRandomNumber (const double minValue = numeric_limits<double>::min(),
                        const double maxValue = numeric_limits<double>::max()) {
  random_device randomSeed;
  mt19937 generateSeed(randomSeed());
  uniform_real_distribution<double> distributionRange(minValue, maxValue);

  return distributionRange(generateSeed);
}

#endif