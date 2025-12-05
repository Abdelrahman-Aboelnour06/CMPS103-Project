//********************************************abdelrahman Tarek    ************************************** */

#include "Rover.h"
#pragma once


class Normal_Rovers : public Rover
{
    const int speed; // Assuming a constant speed for Normal Rovers
public:
    Normal_Rovers(int s, int dbc, int cd)
        : Rover(dbc, cd), speed(s) {}

    ~Normal_Rovers() {}

    int getSpeed() const override {
        return speed;
    }

    int getDaysBeforeCheckup() const override {
        return NUM_OF_MISSION_BEFORE_CHECKUP;
    }

    int getCheckupDuration() const override {
        return checkup_duration;
    }

    int getRoverID() const override {
        return rover_id;
    }

    int getMissionsDone() const override {
        return missions_done;
    }

    void incrementMissionsDone() override {
        ++missions_done;
    }
   
    char getType() const override {
        return 'N';
    }
};

std::ostream& operator<<(std::ostream& os, const Normal_Rovers* rover) {
    os << rover->getRoverID();
    return os;
}
 

