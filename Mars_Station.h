//********************************************abdelrahman Tarek    ************************************** */

#pragma once
#include "header.h"
#include "Request\REQUEST.h"



class Mars_Station {
private:
    int current_day;
    LinkedQueue<request*> requests;
    LinkedQueue<Mission*> Ready_Digging_Missions;
    LinkedQueue<Mission*> Ready_Polar_Missions;
    LinkedQueue<Mission*> Ready_Normal_Missions;
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
    Mars_Station() : current_day(0) {}
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
    LinkedQueue<Mission*> getReadyNormalMissions() const {
        return Ready_Normal_Missions;
    }






};
