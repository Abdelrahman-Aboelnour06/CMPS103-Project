//********************************************abdelrahman Tarek    ************************************** */

#include <iostream>
#include "../Mars_Station.h"
#ifndef REQUEST_H
#define REQUEST_H
class request {
protected:
    int request_id;
    int request_day;
public:
    request(int id, int day) : request_id(id), request_day(day) {}
    ~request() {}
    virtual int getRequestID() const = 0;
    virtual int getRequestDay() const = 0;

};

#endif
