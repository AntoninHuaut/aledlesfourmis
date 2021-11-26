#ifndef ANT_CUSTOMRANDOM_H
#define ANT_CUSTOMRANDOM_H

#include <cstdlib>

class CustomRandom {

    static CustomRandom *instance;

public:
    CustomRandom() = default;

    static CustomRandom *getInstance() {
        if (instance == nullptr) {
            instance = new CustomRandom();
        }
        return instance;
    }

    int randInt(int minInclusive, int maxInclusive);

};


#endif
