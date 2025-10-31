#pragma once
#include <iostream>


class Mission {
protected:
    int mission_id;
    int location_distance;
    int mission_duration;
    char rover_type;
    // 'P' for Polar, 'N' for Normal, 'D' for Digging
public:
    Mission(int id, int loc, int duration, char type)
        : mission_id(id), location_distance(loc), mission_duration(duration), rover_type(type) {}
	int getID() const { return mission_id; }
};