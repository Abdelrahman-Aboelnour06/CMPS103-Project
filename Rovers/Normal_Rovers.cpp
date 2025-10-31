#include "Rover.h"
#include <iostream>
#pragma once


class Normal_Rovers : public Rover
{
   
public:
    Normal_Rovers(int s, int dbc, int cd)
        : Rover(s, dbc, cd) {}

    ~Normal_Rovers() {}

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
    std::ostream& operator<<(std::ostream& os) {
        os << "Normal Rover ID: " << getRoverID() << "\n"
           << "Speed: " << getSpeed() << "\n"
           << "Days Before Checkup: " << getDaysBeforeCheckup() << "\n"
           << "Checkup Duration: " << getCheckupDuration() << "\n"
           << "Missions Done: " << getMissionsDone() << "\n";
        return os;
    }
};



