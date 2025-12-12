// Created by Kirolos Ashraf and Abdelrahman Tarek
#pragma once
#include <iostream>
#include <cmath>
#include "../Rovers/Rover.h"

using namespace std;
enum class STATE
{
    NOTREADY,
    READY,
    OUT,
    EXECUTING,
    BACK,
    DONE,
    ABORTED,
    FAILED
};

class Mission
{
protected:
    STATE mission_state;
    int mission_id;
    int location_distance;
    int mission_duration; // number of days the mission would take once the rover gets to its distenation
    Rover *assignedRover;
    char mission_type;
    // 'P' for Polar, 'N' for Normal, 'D' for Digging 'C' for Complex and 'R' for Rescue
    int Ready_Day;              // the day the mission was ready
    int Assigned_to_Rover_Day;  // the day the mission was assigned to a rover
    int Waiting_Days;           // Waiting days
    int Journey_days;           // the number of days the journey would take to get to the distination (vice versa)
    int Execution_start_day;    // the day the mission starts executing
    int Total_days;             // Total time(days) for a rover to reach the target location then execute the mission then come back to the station
    int Finished_day;           // the day the mission was finished
    int finished_execution_day; // the day the mission finished execution
public:
    Mission(int id, int loc, int duration, char M_type, int readyDay)
        : mission_id(id), location_distance(loc), mission_duration(duration), mission_type(M_type), Ready_Day(readyDay)
    {
        assignedRover = nullptr;
        Assigned_to_Rover_Day = -1;
        Waiting_Days = 0;
        Journey_days = 0;
        Execution_start_day = -1;
        finished_execution_day = -1;
        Total_days = 0;
        Finished_day = -1;
        mission_state = STATE::NOTREADY;
    }
    virtual void setRover(Rover *R)
    {
        assignedRover = R;
    }
    void set_assign_to_rover_day(int d)
    {
        Assigned_to_Rover_Day = d;
    }
    void set_waiting_days()
    {
        Waiting_Days = Assigned_to_Rover_Day - Ready_Day;
    }
    void setJourney_days()
    {
        // distance in KM, day on mars = 25h, speed in KM/h
        Journey_days = ceil((location_distance / assignedRover->getSpeed()) / 25.0);
    }
    void setExecution_start_day()
    {
        Execution_start_day = Assigned_to_Rover_Day + Journey_days;
    }
    void setTotal_days()
    {
        Total_days = (2 * Journey_days) + mission_duration;
    }
    void setFinished_day()
    {
        Finished_day = Ready_Day + Waiting_Days + Total_days;
    }
    void set_finished_execution_day()
    {
        finished_execution_day = Execution_start_day + mission_duration;
    }
    void setFinished_day_parameterized(int day) {
		Finished_day = day;
    }
    
    void setMissionParameters(int currentDay)
    {
        set_assign_to_rover_day(currentDay);
        set_waiting_days();
        setJourney_days();
        setExecution_start_day();
        setTotal_days();
        setFinished_day();
        set_finished_execution_day();
    }
    virtual Rover *getassignedRover() const { return assignedRover; }
    virtual Rover* getassignedRover2() const { return nullptr; }
    int getID() const { return mission_id; }
    int getLocation() const { return location_distance; }
    int getmissionDuration() const { return mission_duration; }
    virtual char getMissionType() const { return mission_type; }
    virtual void setmissionstate(STATE s) { mission_state = s; }
    virtual STATE getmissionstate() const { return mission_state; }
    int get_ready_day() const { return Ready_Day; }
    int get_assigned_to_rover_day() const { return Assigned_to_Rover_Day; }
    int get_waiting_days() const { return Waiting_Days; }
    int get_journey_days() const { return Journey_days; }
    int get_execution_start_day() const { return Execution_start_day; }
    int get_total_days() const { return Total_days; }
    int get_finished_day() const { return Finished_day; }
    int get_assigned_rover_id() { return assignedRover->getRoverID(); }
    int get_remaining_day() { return Journey_days; }
    int get_finished_execution_day() const { return finished_execution_day; }
};

// omar syed
std::ostream &operator<<(std::ostream &output, const Mission *m)
{
    output << m->getID();
    return output;
}