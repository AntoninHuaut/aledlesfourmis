#ifndef ANT_ANTAGE_H
#define ANT_ANTAGE_H

class AntAge {

    int hoursBeforeAdult;

public:
    AntAge(int hoursBeforeAdult) { this->dayBeforeAdult = dayBeforeAdult };

    bool isAdult() { return this->hoursBeforeAdult <= 0 }

};

#endif
