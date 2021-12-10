#ifndef ANT_GAME_H
#define ANT_GAME_H

#include "../map/Board.h"

class SimulationStats;

class Game {

    bool pause = false;

    Board *board;
    SimulationStats *stats;

    string gnuPlotFile = "gnuplot.txt";

    string bufferGNUPlot;

    void tickAnts();

    void tickQueen();

public:

    explicit Game(Board *board, SimulationStats *stats) {
        this->board = board;
        this->stats = stats;
        
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