#pragma once
#include <iostream>
#include <cmath>
#include "../Rovers/Rover.h"
#include "../Rovers/Digging_Rovers.h"
#include "Mission.h"


class Rescue_Mission : public Mission {
public:
    Rescue_Mission(int id, int loc, int duration, int readyDay)
        : Mission(id, loc, duration, 'R', readyDay) {
    }

    char getMissionType() const override { return 'R'; }

};