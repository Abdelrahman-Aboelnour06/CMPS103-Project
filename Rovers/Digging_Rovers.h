//********************************************abdelrahman Tarek    ************************************** */

#include "Rover.h"
#pragma once

class Digging_Rovers : public Rover
{
    const int speed; // Assuming a constant speed for Digging Rovers
public:
    Digging_Rovers(int s, int dbc, int cd)
        : Rover(dbc, cd), speed(s) {}

    ~Digging_Rovers() {}

    int getSpeed() const override {
        return speed;
    }

    int getDaysBeforeCheckup() const override {
        return Days_before_checkup;
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

  
};

std::ostream& operator<<(std::ostream& os, const Digging_Rovers& rover) {
        os << "Digging Rover ID: " << rover.getRoverID() << "\n"
           << "Speed: " << rover.getSpeed() << "\n"
           << "Days Before Checkup: " << rover.getDaysBeforeCheckup() << "\n"
           << "Checkup Duration: " << rover.getCheckupDuration() << "\n"
           << "Missions Done: " << rover.getMissionsDone() << "\n"
           << std::endl;
    return os;
}
    