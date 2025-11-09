// done by abdelrahman Tarek
#include "REQUEST.h"
#include "../header.h"
#include "../Mars_Station.h"
#include "../Mission/mission.h"
#include "../Mission/Mission.h"
#include <iostream>
#pragma once

class Abort_Request : public request
{
    int aborted_request_id;
public:
    Abort_Request(int day, int aborted_id)
        : request(0, day), aborted_request_id(aborted_id) {}

    int getAbortedRequestID() const {
        return aborted_request_id;
    }

    int getRequestID() const  {
        return request::request_id;
    }
    int getRequestDay() const  {
        return request::request_day;
    }
    void operate(Mars_Station& station) override;
};

std::ostream& operator<<(std::ostream& os, const Abort_Request& req) {
    os << "Abort Request ID: " << req.getRequestID() << "\n"
       << "Request Day: " << req.getRequestDay() << "\n"
       << "Aborted Mission ID: " << req.getAbortedRequestID() << "\n" << std::endl;

    return os;
}