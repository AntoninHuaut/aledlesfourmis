#include "../../include/lib/CustomRandom.h"

int CustomRandom::randInt(int minInclusive, int maxInclusive) {
    if (maxInclusive <= minInclusive) return 0;
    int modulo = (maxInclusive - minInclusive + 1);
    if (modulo == 0) return 0;

    return (rand() % modulo) + minInclusive; // NOLINT(cert-msc50-cpp)
}


