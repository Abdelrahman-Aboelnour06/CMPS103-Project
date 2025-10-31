#pragma once
#include <iostream>

class Request {
protected:
    int request_id;
    int request_day;
public:
    Request(int id, int day) : request_id(id), request_day(day) {}
    virtual ~Request() {}
    virtual int getRequestID() const = 0;
    virtual int getRequestDay() const = 0;

};

