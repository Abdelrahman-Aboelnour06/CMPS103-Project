#include "Requests.h"
#include <iostream>
#pragma once

class Abort_Request : public Request {
    int aborted_request_id;
public:
    Abort_Request(int day, int aborted_id)
        : Request(0, day), aborted_request_id(aborted_id) {}

    int getAbortedRequestID() const {
        return aborted_request_id;
    }

    int getRequestID() const override {
        return Request::request_id;
    }
    int getRequestDay() const override {
        return Request::request_day;
    }
  
};

std::ostream& operator<<(std::ostream& os, const Abort_Request& req) {
    os << "Abort Request ID: " << req.getRequestID() << "\n"
       << "Request Day: " << req.getRequestDay() << "\n"
       << "Aborted Request ID: " << req.getAbortedRequestID() << "\n" << std::endl;

    return os;
}