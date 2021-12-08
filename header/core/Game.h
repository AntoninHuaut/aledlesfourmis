#ifndef ANT_GAME_H
#define ANT_GAME_H

#include "../map/Board.h"

class Game {

    bool pause = false;

    Board *board;

    string gnuPlotFile = "gnuplot.txt";

    string bufferGNUPlot;
    
    void tickAnts();

    void tickQueen();

public:

    explicit Game(Board *board) {
        this->board = board;

        ofstream outfile;
        outfile.open(gnuPlotFile); // Erase file
        outfile.close();
    }

    void tickGame();

    void saveCurrentTick();

    void logGNUPlot();

    bool isPause() const;

    void setPause(bool pause);
};


#endif