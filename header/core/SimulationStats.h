#ifndef ANT_SIMULATIONSTATS_H
#define ANT_SIMULATIONSTATS_H

#include <cstring>

class SimulationStats {

    int currentTPS;
    int wantedTPS;

    int foodAmount;

    bool isGameEnded;
    //string endMessage;

    int workerAmount;
    int soldierAmount;
    int scoutAmount;
    int slaveOwnerAmount;

};


#endif
