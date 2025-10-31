#pragma once
#include "header.h"



class Mars_Station {
private:
    int current_day;
    LinkedQueue<Request*> requests;
    LinkedQueue<Request*> Ready_Digging_Missions;
    LinkedQueue<Request*> Ready_Polar_Missions;
    // LinkedQueue<Request*> Ready_Normal_Missions;
    //  priQueue OUT missions;
    priQueue<Request*> ExecMissions; 
    priQueue<Request*> BackMissions;
    ArrayStack<Request*> CompletedMissions;
    ArrayStack<Request*> AbortedMissions;
    LinkedQueue<Normal_Rovers*> available_Normal_Rovers;
    LinkedQueue<Polar_Rovers*> available_Polar_Rovers;
    LinkedQueue<Digging_Rovers*> available_Digging_Rovers;
    LinkedQueue<Normal_Rovers*>  Checkup_Normal_Rovers;
    LinkedQueue<Polar_Rovers*>   Checkup_Polar_Rovers;
    LinkedQueue<Digging_Rovers*> Checkup_Digging_Rovers;
    public:
    


};
