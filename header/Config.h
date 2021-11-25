#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H


class Config {

public:
    static double DEFAULT_FOOD_CONSUMING_TICK;
    static int DEFAULT_HOURS_BEFORE_DEATH;

    static int NEW_ANT_EVERY_DAY;
    static double QUEEN_FOOD_CONSUMING_TICK;
    static int QUEEN_HOURS_BEFORE_DEATH;

    static int WORKER_HOURS_BEFORE_ADULT;
    static int WORKER_MAX_FOOD_CARRIED_AMOUNT;

    static int SCOOT_HOURS_BEFORE_ADULT;

    static int SOLDIER_HOURS_BEFORE_VISIT_COLONY;

    static int SLAVE_OWNER_MAX_HOURS_SURVIVE_BEFORE_FEEDING;

    static int ROCK_MAX_ANT_ON_CELL;
    static int BASIC_CELL_MAX_ANT_ON_CELL;
    static int COLONY_MAX_ANT_ON_CELL;

    static double ROCK_PERCENT;

    static double FOOD_CASE_NUMBER_PERCENT;
    static int FOOD_UNIT_VALUE;

    static int LENGTH;
    static int HEIGHT;

};

#endif
