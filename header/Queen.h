#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    Queen() : Ant(365000, 0.01) {};
    void tick() override;

};


#endif