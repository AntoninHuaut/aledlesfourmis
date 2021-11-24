#ifndef ANT_ANTAGE_H
#define ANT_ANTAGE_H

class AntAge {

    int hoursBeforeAdult;

public:
    explicit AntAge(int hoursBeforeAdult) { this->hoursBeforeAdult = hoursBeforeAdult; };

    bool isAdult() const { return this->hoursBeforeAdult <= 0; };

};

#endif
