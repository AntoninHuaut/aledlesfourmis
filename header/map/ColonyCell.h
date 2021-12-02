#ifndef ANT_COLONYCELL_H
#define ANT_COLONYCELL_H

#include "BoardCell.h"
#include "../Config.h"

class ColonyCell : public BoardCell {

public:
    ColonyCell(int posHeight, int posLength) :
            BoardCell(posHeight, posLength, Config::get()->getColonyMaxAntOnCell(), ColonyCellType) {
        this->setVisited(true);
    };

};

#endif
