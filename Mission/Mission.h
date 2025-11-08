// Created by Kirolos Ashraf and Abdelrahman Tarek
#pragma once
#include <iostream>
#include <cmath>
#include "../Rovers/Rover.h"

using namespace std;


class Mission {
protected:
    int mission_id;
    int location_distance;
    int mission_duration; // number of days the mission would take once the rover gets to its distenation
    Rover* assignedRover;
    char mission_type;
    // 'P' for Polar, 'N' for Normal, 'D' for Digging
    int RDY; // the day the mission was ready
    int LDY; // the day the mission was assigned to a rover
    int WDYs; // Waiting days
    int JDYs; // the number of days the journey would take to get to the distination (vice versa)
  	int EDY; // the day the mission starts executing
    int TDYs; // Total time(days) for a rover to reach the target location then execute the mission then come back to the station
	  int FDY; // the day the mission was finished
public:
    Mission(int id, int loc, int duration, char M_type, int readyDay)
        : mission_id(id), location_distance(loc), mission_duration(duration), mission_type(M_type), RDY(readyDay) {
        assignedRover = nullptr;
		LDY = -1;
		WDYs = 0;
		JDYs = 0;
		EDY = -1;
		TDYs = 0;
		FDY = -1;
    }
    void setRover(Rover* R) {
		assignedRover = R;
	}
    void setLDY(int d) {
		LDY = d;
    }
    void setWDYs() {
		WDYs = LDY - RDY;
    }
    void setJDYs() {
        // distance in KM, day on mars = 25h, speed in KM/h
        JDYs = ceil((location_distance / assignedRover->getSpeed()) / 25.0);
    }
    void setEDY() {
		EDY = LDY + JDYs;
    }
    void setTDYs() {
		TDYs = (2 * JDYs) + mission_duration;
    }
    void setFDY() {
		FDY = RDY + WDYs + TDYs;
    }
    void setMissionParameters(int currentDay) {
		this->setLDY(currentDay);
		this->setWDYs();
		this->setEDY();
		this->setJDYs();
		this->setTDYs();
		this->setFDY();
    }
	int getID() const { return mission_id; }
	int getLocation() const { return location_distance; }
	int getmissionDuration() const { return mission_duration; }
	char getMissionType() const { return mission_type; }
	int getRDY() const { return RDY; }
	int getLDY() const { return LDY; }
	int getWDYs() const { return WDYs; }
	int getJDYs() const { return JDYs; }
	int getEDY() const { return EDY; }
	int getTDYs() const { return TDYs; }
	int getFDY() const { return FDY; }
};

//omar syed
std::ostream& operator<<(std::ostream& output, const Mission& m) {
    output << "Mission ID: " << m.getID() << "\n"
        << "location_distance: " << m.getLocation()<< "\n"
        << "mission_duration: " << m.getmissionDuration()<< "\n"
        << "mission_type: " << m.getMissionType()<< "\n"
        << "RDY : " << m.getRDY()<< "\n" << std::endl;

    return output;
}