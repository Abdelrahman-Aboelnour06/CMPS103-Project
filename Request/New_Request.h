//********************************************abdelrahman Tarek    ************************************** */
#pragma once
#include "Request.h"
#include "../Rovers/polar_Rovers.h"
#include "../Rovers/Normal_Rovers.h"
#include "../Rovers/Digging_Rovers.h"
#include  "../Mars_Station.h"


class New_Request : public REQUEST {
    int location_distance;
    int mission_duration;
    char rover_type; // 'P' for Polar, 'N' for Normal, 'D' for Digging
public:
    New_Request(int id, int day, int loc, int duration, char type)
        : REQUEST(id, day), location_distance(loc), mission_duration(duration), rover_type(type) {}

    int getLocation() const {
        return location_distance;
    }

    int getMissionDuration() const {
        return mission_duration;
    }

    int getRequestID() const  {
        return REQUEST::request_id;
    }
    int getRequestDay() const  {
        return REQUEST::request_day;
    }
    char getRoverType() const {
        return rover_type;
    }

    void operate(Mars_Station& station) {
       if (rover_type == 'P') {
            Mission *thisMission = new Mission(getRequestID(),getLocation(), getMissionDuration(), rover_type);
            station.getReadyPolarMissions().enqueue(thisMission);
        } else if (rover_type == 'N') {
            Mission *thisMission = new Mission(getRequestID(),getLocation(), getMissionDuration(), rover_type);
            station.getReadyNormalMissions().enqueue(thisMission);
        } else if (rover_type == 'D') {
            Mission *thisMission = new Mission(getRequestID(),getLocation(), getMissionDuration(), rover_type);
            station.getReadyDiggingMissions().enqueue(thisMission);
        }
    }
  
};

std::ostream& operator<<(std::ostream& os, const New_Request& req) {
    os << "New Request ID: " << req.getRequestID() << "\n"
       << "Request Day: " << req.getRequestDay() << "\n"
       << "Location Distance: " << req.getLocation() << "\n"
       << "New_Request Duration: " << req.getMissionDuration() << "\n"
       << "New_Request Type: " << req.getRoverType() << "\n" << std::endl;

    return os;
}
