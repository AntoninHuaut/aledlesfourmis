#ifndef ANT_CUSTOMRANDOM_H
#define ANT_CUSTOMRANDOM_H

#include <cstdlib>

class CustomRandom {

public:
    CustomRandom() = default;

    static int randInt(int minInclusive, int maxInclusive);

};


#endif
