#ifndef ANT_AGEADULT_H
#define ANT_AGEADULT_H

class AgeAdult {

    int hoursBeforeAdult;

public:
    explicit AgeAdult(int hoursBeforeAdult) { this->hoursBeforeAdult = hoursBeforeAdult; };

    bool isAdult() const { return this->hoursBeforeAdult <= 0; };

    void incrementAge() {
        if (hoursBeforeAdult > 0) {
            hoursBeforeAdult--;
        }
    }
};

#endif
