#ifndef ANT_COLONYCELL_H
#define ANT_COLONYCELL_H

#include "BoardCell.h"
#include "../Config.h"

class ColonyCell : public BoardCell {

public:
    ColonyCell(int posLength, int posHeight) :
            BoardCell(posLength, posHeight, Config::get()->getColonyMaxAntOnCell(), ColonyCellType) {
        this->setVisited(true);
    };

};

#endif
