#pragma once
class Rover {
protected:
    const int speed;
    const int Days_before_checkup;
    const int checkup_duration;
    static int id_counter;
    const int rover_id;
    int missions_done;
public:
    Rover(int s, int dbc, int cd)
        : speed(s), Days_before_checkup(dbc), checkup_duration(cd),
          rover_id(++id_counter), missions_done(0) {}
    virtual ~Rover() = 0;

    virtual int  getSpeed() const = 0;
    virtual int  getDaysBeforeCheckup() const = 0;
    virtual int  getCheckupDuration() const = 0;
    virtual int  getRoverID() const = 0;
    virtual int  getMissionsDone() const = 0;
    virtual void incrementMissionsDone() = 0;
};


int Rover::id_counter = 0;
