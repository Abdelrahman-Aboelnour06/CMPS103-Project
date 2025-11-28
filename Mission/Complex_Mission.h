#pragma once
#include <iostream>
#include <cmath>
#include "../Rovers/Rover.h"
#include "../Rovers/Digging_Rovers.h"
#include "Mission.h"

using namespace std;


class Complex_Mission : public Mission {
    Digging_Rovers* assignedDigRover;
 public:
    Complex_Mission(int id, int loc, int duration,int readyDay)
        : Mission(id, loc, duration, 'C', readyDay) {
        assignedDigRover = nullptr;
    }

    void set_Digging_Rover(Digging_Rovers* R) {
        assignedDigRover = R;
        setRover(R); // Also set the base class Rover pointer
    }

    Digging_Rovers* get_Assigned_Digging_Rover() const {
        return assignedDigRover;
    }

    char getMissionType() const override { return 'C'; }

};
