#include "Rover.h"
#pragma once

using namespace std;


class Rescue_Rovers : public Rover
{
    private:
    const int speed; // Assuming a constant speed for Rescue Rovers
    public:
    Rescue_Rovers(int s,int dbc, int cd)
        : Rover(dbc, cd), speed(s) {}
    ~Rescue_Rovers() {}

    int getDaysBeforeCheckup() const override {
        return NUM_OF_MISSION_BEFORE_CHECKUP;
    }
    int getSpeed() const override {
        return speed;
    }
    int getCheckupDuration() const override {
        return checkup_duration;
    }
    int getRoverID() const override {
        return Rover::rover_id;
    }
    int getMissionsDone() const override {
        return missions_done;
    }
    void incrementMissionsDone() override {
        ++missions_done;
    }
    char getType() const override {
        return 'R';
    }

};

std::ostream& operator<<(std::ostream& os, const Rescue_Rovers* rover) {
    os << rover->getRoverID();
    return os;
}

