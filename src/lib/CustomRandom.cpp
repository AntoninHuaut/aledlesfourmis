#include "../../header/lib/CustomRandom.h"

int CustomRandom::randInt(int minInclusive, int maxInclusive) {
    return rand() % (maxInclusive - minInclusive + 1) + minInclusive; // NOLINT(cert-msc50-cpp)
}