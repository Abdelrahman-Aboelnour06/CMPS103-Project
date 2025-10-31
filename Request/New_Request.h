//********************************************abdelrahman Tarek    ************************************** */
#pragma once
#include "Requests.h"
#include "../Rovers/polar_Rovers.h"
#include "../Rovers/Normal_Rovers.h"
#include "../Rovers/Digging_Rovers.h"


class New_Request : public Request {
    int location_distance;
    int mission_duration;
    char rover_type; // 'P' for Polar, 'N' for Normal, 'D' for Digging
public:
    New_Request(int id, int day, int loc, int duration, char type)
        : Request(id, day), location_distance(loc), mission_duration(duration), rover_type(type) {}

    int getLocation() const {
        return location_distance;
    }

    int getMissionDuration() const {
        return mission_duration;
    }

    int getRequestID() const override {
        return Request::request_id;
    }
    int getRequestDay() const override {
        return Request::request_day;
    }
    char getRoverType() const {
        return rover_type;
    }
  
};
#ifndef _NEW_REQUEST_H_
#define _NEW_REQUEST_H_
std::ostream& operator<<(std::ostream& os, const New_Request& req) {
    os << "New Request ID: " << req.getRequestID() << "\n"
       << "Request Day: " << req.getRequestDay() << "\n"
       << "Location Distance: " << req.getLocation() << "\n"
       << "New_Request Duration: " << req.getMissionDuration() << "\n"
       << "New_Request Type: " << req.getRoverType() << "\n" << std::endl;

    return os;
}
#endif