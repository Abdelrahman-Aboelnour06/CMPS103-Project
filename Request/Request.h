//********************************************abdelrahman Tarek    ************************************** */

#pragma once
#include <iostream>
#include "../Mars_Station.h"

class REQUEST {
protected:
    int request_id;
    int request_day;
public:
    REQUEST(int id, int day) : request_id(id), request_day(day) {}
     ~REQUEST() {}
    virtual int getRequestID() const = 0;
    virtual int getRequestDay() const = 0;
    virtual void operate(Mars_Station& station) = 0;

};

