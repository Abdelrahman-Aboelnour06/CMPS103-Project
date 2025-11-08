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
    //omar syed
	int getLOC_DISTANCE() const { return location_distance; }
	int getMISSION_DURATION() const { return mission_duration; }
	char getROVER_TYPE() const { return rover_type; }


};
    //omar syed
    std::ostream& operator<<(std::ostream& output ,Mission m) {
        output << "Mission ID : " << m.getID() << " \n"
            << "Location Distance : " << m.getLOC_DISTANCE() << " \n"
            << "Mission Duration : " << m.getMISSION_DURATION() << " \n"
            << "Rover Tyoe : " << m.getROVER_TYPE() << " \n";
        return output;
    }
    //omar syed