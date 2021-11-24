#ifndef ANT_ANTAGE_H
#define ANT_ANTAGE_H

class AntAge {

    int dayBeforeAdult;

public:
    AntAge(int dayBeforeAdult) { this->dayBeforeAdult = dayBeforeAdult };

    bool isAdult() { return this->dayBeforeAdult <= 0 }

};

#endif
