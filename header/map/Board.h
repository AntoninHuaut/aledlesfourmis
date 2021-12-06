#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include <random>
#include <SFML/Graphics.hpp>
#include "BoardCell.h"
#include "BasicCell.h"
#include "ColonyCell.h"
#include "../Config.h"
#include "../core/TileEnum.h"

using namespace std;
using namespace sf;

class Queen;

class Board : public sf::Drawable, public sf::Transformable {

    BoardCell ***cells;
    list<ColonyCell *> *coloniesCells;
    int currentTick = 0;
    int remainingTickBeforeSlaveOwnerSpawn;

    list<Ant *> *antList;
    Queen *antQueen;

    sf::VertexArray floor_vertex;
    sf::VertexArray layer_vertex;

    sf::Texture m_tileSet;

    bool windowClosed = false;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    BasicCell *findExpandableBasicCell();

public:
    explicit Board(BoardCell ***cells);

    ~Board() override;

    int getCurrentTick() const { return currentTick; }

    void tick();

    bool isWindowClosed() const { return windowClosed; }

    void setRemainingTickBeforeSlaveOwnerSpawn() {
        remainingTickBeforeSlaveOwnerSpawn = CustomRandom::randInt(Config::get()->getSlaveOwnerMinTickRandom(),
                                                                   Config::get()->getSlaveOwnerMaxTickRandom()) * 24;
    }

    void createSlaveOwner();

    void setWindowClosed(bool newWindowClosed) {
        this->windowClosed = newWindowClosed;
    }

    bool isQueenAlive() {
        return antQueen != nullptr;
    }

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> getNearbyCells(int height, int length);

    bool calcLayer();

    bool calcFloor();

    int catchLarva(int nbToCatch) const;

    list<ColonyCell *> *getColoniesCells() const {
        return coloniesCells;
    }

    void addColoniesCell(ColonyCell *newColoniesCells) {
        coloniesCells->push_back(newColoniesCells);
    }

    list<Ant *> *getAntList() const {
        return antList;
    }

    void addAntToList(Ant *ant) {
        antList->push_back(ant);
    }

    Queen *getAntQueen() const {
        return antQueen;
    }

    void setAntQueen(Queen *newAntQueen) {
        antQueen = newAntQueen;
    }

    BoardCell *getCenterCell();

    void expandColonies();
};

#endif