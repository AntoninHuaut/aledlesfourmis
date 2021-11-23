#ifndef FOURMIS_QUEEN_H
#define FOURMIS_QUEEN_H

#include "Ant.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    Queen(): Ant(365000, 0.01) {};

};


#endif //FOURMIS_QUEEN_H
