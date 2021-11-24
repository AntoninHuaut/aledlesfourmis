#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H


class Config {

public:
    static double DEFAULT_FOOD_CONSUMING_TICK;
    static int DEFAULT_DAY_BEFORE_DEATH;

    static int NEW_ANT_EVERY_DAY;
    static double QUEEN_FOOD_CONSUMING_TICK;
    static int QUEEN_DAY_BEFORE_DEATH;

    static int WORKER_DAY_BEFORE_ADULT;
    static int WORKER_MAX_FOOD_CARRIED_AMOUNT;

    static int SCOOT_DAY_BEFORE_ADULT;

    static int SOLDIER_DAY_BEFORE_VISITE_COLONY;

    static int SLAVE_OWNER_MAX_DAY_SURVIVE_BEFORE_FEEDING;

    static int ROCK_MAX_ANT_ON_CELL;
    static int BASIC_CELL_MAX_ANT_ON_CELL;
    static int COLONY_MAX_ANT_ON_CELL;

    static double ROCK_PERCENT;
    static double ROCK_SIZE_ONE_PERCENT;
    static double ROCK_SIZE_TWO_PERCENT;
    static double ROCK_SIZE_THREE_PERCENT;
    static double ROCK_SIZE_FOUR_PERCENT;
    static double ROCK_SIZE_FIVE_PERCENT;
    static double ROCK_SIZE_SIZE_PERCENT;

    static double FOOD_CASE_NUMER_PERCENT;
    static int FOOD_UNIT_VALUE;

    static int LENGTH;
    static int HEIGHT;

};


#endif
