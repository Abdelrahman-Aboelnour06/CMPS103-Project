//********************************************abdelrahman Tarek    ************************************** */
#pragma once
#include "REQUEST.h"
#include "../Rovers/polar_Rovers.h"
#include "../Rovers/Normal_Rovers.h"
#include "../Rovers/Digging_Rovers.h"
#include "../Mars_Station.h"


class New_Request : public request
{
    int location_distance;
    int mission_duration;
    char mission_type; // 'P' for Polar, 'N' for Normal, 'D' for Digging
public:
    New_Request(int id, int day, int loc, int duration, char type)
        : request(id, day), location_distance(loc), mission_duration(duration), mission_type(type) 
    {

    }
    int getLocation() const {
        return location_distance;
    }

    int getMissionDuration() const {
        return mission_duration;
    }

    int getRequestID() const override {
        return request::request_id;
    }
    int getRequestDay() const override {
        return request::request_day;
    }
    char getMissionType() const {
        return mission_type;
    }
    void operate(Mars_Station& station)
    {
        Mission* newMission = new Mission(getRequestID(), location_distance, mission_duration, mission_type, getRequestDay());
        char type = getMissionType();
        if (type == 'N') {
            station.getReadyNormalMissions().enqueue(newMission);
        }
        else if (type == 'P') {
            station.getReadyPolarMissions().enqueue(newMission);
        }
        else if (type == 'D') {
            station.getReadyDiggingMissions().enqueue(newMission);
        }
	}



};

std::ostream& operator<<(std::ostream& os, const New_Request& req) {
    os << "New Request ID: " << req.getRequestID() << "\n"
        << "Request Day: " << req.getRequestDay() << "\n"
        << "Location Distance: " << req.getLocation() << "\n"
        << "New_Request Duration: " << req.getMissionDuration() << "\n"
        << "New_Request Type: " << req.getMissionType() << "\n" << std::endl;

    return os;
}
