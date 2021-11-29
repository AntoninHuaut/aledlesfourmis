#ifndef ANT_AGE_H
#define ANT_AGE_H

class Age {

    int hoursBeforeAdult;

public:
    explicit Age(int hoursBeforeAdult) { this->hoursBeforeAdult = hoursBeforeAdult; };

    bool isAdult() const { return this->hoursBeforeAdult <= 0; };

};

#endif
