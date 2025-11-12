//********************************************abdelrahman Tarek    ************************************** */

#include "Rover.h"
#pragma once
class Polar_Rovers : public Rover
{
    private:
    const int speed; // Assuming a constant speed for Polar Rovers
    public:
    Polar_Rovers(int s,int dbc, int cd)
        : Rover(dbc, cd), speed(s) {}
    ~Polar_Rovers() {}

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
        return rover_id;
    }
    int getMissionsDone() const override {
        return missions_done;
    }
    void incrementMissionsDone() override {
        ++missions_done;
    }
    char getType() const override {
        return 'P';
    }

};

std::ostream& operator<<(std::ostream& os, const Polar_Rovers& rover) {
        os << "Polar Rover ID: " << rover.getRoverID() << ", Speed: " << rover.getSpeed() << ", Days Before Checkup: " << rover.getDaysBeforeCheckup() << ", Checkup Duration: " << rover.getCheckupDuration() << ", Missions Done: " << rover.getMissionsDone() << std::endl;
           return os;
    }