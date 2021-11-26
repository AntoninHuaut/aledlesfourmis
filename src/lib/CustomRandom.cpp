#include "../../header/lib/CustomRandom.h"

CustomRandom *CustomRandom::instance = nullptr;

int CustomRandom::randInt(int minInclusive, int maxInclusive) {
    return rand() % (maxInclusive - minInclusive + 1) + minInclusive;
}