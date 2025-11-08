//********************************************abdelrahman Tarek    ************************************** */

#pragma once
#include "header.h"
#include "Request/Request.h"
#include <fstream>
#include <iostream>
#include "RDY_NM.h"
#include "OUT_missions.h"


class Mars_Station {
private:
    int current_day;
    int NORMAL_ROVER_SPEED;
    int POLAR_ROVER_SPEED;
    int DIGGING_ROVER_SPEED;
    LinkedQueue<request*> requests;
    LinkedQueue<Mission*> Ready_Digging_Missions;
    LinkedQueue<Mission*> Ready_Polar_Missions;
    RDY_NM Ready_Normal_Missions;
    OUT_missions Out_Missions;
    priQueue<Mission*> ExecMissions;
    priQueue<Mission*> BackMissions;
    ArrayStack<Mission*> CompletedMissions;
    ArrayStack<Mission*> AbortedMissions;
    LinkedQueue<Normal_Rovers*> available_Normal_Rovers;
    LinkedQueue<Polar_Rovers*> available_Polar_Rovers;
    LinkedQueue<Digging_Rovers*> available_Digging_Rovers;
    LinkedQueue<Normal_Rovers*> Checkup_Normal_Rovers;
    LinkedQueue<Polar_Rovers*> Checkup_Polar_Rovers;
    LinkedQueue<Digging_Rovers*> Checkup_Digging_Rovers;
    public:
    Mars_Station() : current_day(1) {}
    ~Mars_Station() {}
    LinkedQueue<request*> getRequestsQueue() const {
        return requests;
    }
    LinkedQueue<Mission*> getReadyDiggingMissions() const {
        return Ready_Digging_Missions;
    }
    LinkedQueue<Mission*> getReadyPolarMissions() const {
        return Ready_Polar_Missions;
    }
    RDY_NM getReadyNormalMissions() const {
        return Ready_Normal_Missions;
    }
    OUT_missions getOutMissions() const {
        return Out_Missions;
    }

    void SET_AVAIL_PR(Polar_Rovers*&Avail_PR) {
        available_Polar_Rovers.enqueue(Avail_PR);
    }

    void SET_AVAIL_DR(Digging_Rovers*&Avail_DR) {
        available_Digging_Rovers.enqueue(Avail_DR);
    }

    void SET_AVAIL_NR(Normal_Rovers*&Avail_NR) {
        available_Normal_Rovers.enqueue(Avail_NR);
    }

    

    void SET_REQUEST_QUEUE(request* requestptr) {
        requests.enqueue(requestptr);
    }
    LinkedQueue<Polar_Rovers*>GET_AVAIL_PR()const {
        return available_Polar_Rovers;
    }
    LinkedQueue<Digging_Rovers*>GET_AVAIL_DR()const {
        return available_Digging_Rovers;
    }
    LinkedQueue<Normal_Rovers*>GET_AVAIL_NR()const {
        return available_Normal_Rovers;
    }
}; 
