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
    }

    

    char getMissionType() const override { return 'C'; }

    void setRover(Digging_Rovers* DR1, Rover* R2){
        assignedDigRover = DR1;
        Mission::setRover(R2); 
    }
    Rover *getassignedRover() const override {
        return Mission::getassignedRover();
    }
    Rover* getassignedRover2() const override {
        return assignedDigRover;
    }

};
