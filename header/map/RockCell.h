#ifndef ANT_ROCKCELL_H
#define ANT_ROCKCELL_H

#include "BoardCell.h"
#include "../Config.h"

using namespace std;

class RockCell : public BoardCell {

public:
    RockCell(Board *board, int posHeight, int posLength) :
            BoardCell(board, posHeight, posLength, Config::get()->getRockMaxAntOnCell(), RockCellType) {};

    void addAntOnCell(Ant *antToAdd) override;

    void removeAntOnCell(Ant *antToRemove) override;

    void onNearCellVisited() override;
    
};


#endif
