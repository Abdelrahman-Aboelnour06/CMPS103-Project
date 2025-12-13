#pragma once
#include <iostream>
#include <cmath>
#include "../Rovers/Rover.h"
#include "../Rovers/Digging_Rovers.h"
#include "Mission.h"


class Rescue_Mission : public Mission {
    Mission* assignedMission;
public:
    Rescue_Mission(Mission* assignedMission, int id, int loc, int duration, int readyDay)
        : Mission(id, loc, duration, 'R', readyDay), assignedMission(assignedMission) {
    }

    char getMissionType() const override { return 'R'; }

};

std::ostream &operator<<(std::ostream &output, const Rescue_Mission *m)
{
    output << m->getID();
    return output;
}