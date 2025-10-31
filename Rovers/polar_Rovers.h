//********************************************abdelrahman Tarek    ************************************** */

#include "Rover.h"
#pragma once
class Polar_Rovers : public Rover
{
    public:
    Polar_Rovers(int s, int dbc, int cd)
        : Rover(s, dbc, cd) {}
    ~Polar_Rovers() {}
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

std::ostream& operator<<(std::ostream& os, const Polar_Rovers& rover) {
        os << "Polar Rover ID: " << rover.getRoverID() << "\n"
           << "Speed: " << rover.getSpeed() << "\n"
           << "Days Before Checkup: " << rover.getDaysBeforeCheckup() << "\n"
           << "Checkup Duration: " << rover.getCheckupDuration() << "\n"
           << "Missions Done: " << rover.getMissionsDone() << "\n"<<std::endl;
           return os;
    }