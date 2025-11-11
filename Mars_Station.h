//**************** Abdelrahman Tarek // Kirolos Ashraf // Omar Sayd // Marwan Nader ********************** */

#pragma once
#include "header.h"
#include "Request/Request.h"
#include <fstream>
#include <iostream>
#include "RDY_NM.h"
#include "OUT_missions.h"
//omar syed 
//this function is used to print request list
void print_req(LinkedQueue<request*>req) {
    request* item = nullptr;
    New_Request* nrptr = nullptr;
    Abort_Request* arptr = nullptr;
    while (!req.isEmpty()) {
        req.dequeue(item);
        nrptr = dynamic_cast<New_Request*>(item);
        arptr = dynamic_cast<Abort_Request*>(item);
        if (nrptr) {
            cout << *nrptr;
        }
        else {
            cout << *arptr;
        }
    }
}


class Mars_Station {
private:
    int current_day;
    int NORMAL_ROVER_SPEED;
    int POLAR_ROVER_SPEED;
    int DIGGING_ROVER_SPEED;
    LinkedQueue<request*> requests;
    LinkedQueue<Mission*> Ready_Digging_Missions;//Will Be Loaded From Request List
    LinkedQueue<Mission*> Ready_Polar_Missions;  //Will Be Loaded From Request List
    RDY_NM Ready_Normal_Missions;                //Will Be Loaded From Request List
    OUT_missions Out_Missions;
    priQueue<Mission*> ExecMissions;
    priQueue<Mission*> BackMissions;
    ArrayStack<Mission*> CompletedMissions;
    ArrayStack<Mission*> AbortedMissions;
    LinkedQueue<Normal_Rovers*> available_Normal_Rovers;   //Will Be Loaded From Request List
    LinkedQueue<Polar_Rovers*> available_Polar_Rovers;     //Will Be Loaded From Request List
    LinkedQueue<Digging_Rovers*> available_Digging_Rovers; //Will Be Loaded From Request List
    LinkedQueue<Normal_Rovers*> Checkup_Normal_Rovers;     //Will Be Loaded From Request List
    LinkedQueue<Polar_Rovers*> Checkup_Polar_Rovers;       //Will Be Loaded From Request List
    LinkedQueue<Digging_Rovers*> Checkup_Digging_Rovers;   //Will Be Loaded From Request List
public:

    Mars_Station() : current_day(1) {}
    ~Mars_Station() {
        request* reqPtr = nullptr;
        Mission* missionPtr = nullptr;
        int x=0;
        while (!requests.isEmpty()) {
            requests.dequeue(reqPtr);
            delete reqPtr;
        }
        while (!available_Normal_Rovers.isEmpty()) {
            Normal_Rovers* roverPtr = nullptr;
            available_Normal_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!available_Polar_Rovers.isEmpty()) {
            Polar_Rovers* roverPtr = nullptr;
            available_Polar_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!available_Digging_Rovers.isEmpty()) {
            Digging_Rovers* roverPtr = nullptr;
            available_Digging_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!Checkup_Normal_Rovers.isEmpty()) {
            Normal_Rovers* roverPtr = nullptr;
            Checkup_Normal_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!Checkup_Polar_Rovers.isEmpty()) {
            Polar_Rovers* roverPtr = nullptr;
            Checkup_Polar_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!Checkup_Digging_Rovers.isEmpty()) {
            Digging_Rovers* roverPtr = nullptr;
            Checkup_Digging_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!AbortedMissions.isEmpty()) {
            Mission* missionPtr = nullptr;
            AbortedMissions.pop(missionPtr);
            delete missionPtr;
        }
        while (!CompletedMissions.isEmpty()) {
            Mission* missionPtr = nullptr;
            CompletedMissions.pop(missionPtr);
            delete missionPtr;
        }
        while (Ready_Digging_Missions.dequeue(missionPtr)) {
            delete missionPtr;
        }
        while (!Ready_Polar_Missions.dequeue(missionPtr)) {
            delete missionPtr;
        }
        while (!Ready_Normal_Missions.dequeue(missionPtr)) {
            delete missionPtr;
        }
        while (!Out_Missions.dequeue(missionPtr,x)) {
            delete missionPtr;
        }
        while (!ExecMissions.dequeue(missionPtr,x)) {
            delete missionPtr;
        }
        while (!BackMissions.dequeue(missionPtr,x)) {
            delete missionPtr;
        }


    }

    //omar syed
    void FILE_LOADING(string fileName) {
        //read data from a file and store it into data structures
        //open the file
        int roverCounts[3] = { 0,0,0 };
        int roverSpeed[3] = { 0 ,0,0 };
        int* checkupDurations = nullptr;
        int checkupNum = 0;
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }
        //read data from the file
        int i = 0;

        while (i < 3) {
            file >> roverCounts[i];
            i++;
        }
        i = 0;

        while (i < 3) {
            file >> roverSpeed[i];
            i++;
        }
        file >> checkupNum;
        checkupDurations = new int[checkupNum];
        i = 0;
        while (i < checkupNum)
        {
            file >> checkupDurations[i];
            i++;

        }
        Digging_Rovers* nDptr = nullptr;
        Polar_Rovers* nPptr = nullptr;
        Normal_Rovers* nNptr = nullptr;
        for (int j = 0; j < roverCounts[0]; j++) {
            nDptr = new Digging_Rovers(roverSpeed[0], checkupNum, checkupDurations[0]);
            this->available_Digging_Rovers.enqueue(nDptr);
            DIGGING_ROVER_SPEED = roverSpeed[0];
        }
        for (int j = 0; j < roverCounts[1]; j++) {
            nPptr = new Polar_Rovers(roverSpeed[1], checkupNum, checkupDurations[1]);
            this->available_Polar_Rovers.enqueue(nPptr);
            POLAR_ROVER_SPEED = roverSpeed[1];
        }
        for (int j = 0; j < roverCounts[2]; j++) {
            nNptr = new Normal_Rovers(roverSpeed[2], checkupNum, checkupDurations[2]);
            this->available_Normal_Rovers.enqueue(nNptr);
            NORMAL_ROVER_SPEED = roverSpeed[2];
        }



        int requestNum;
        file >> requestNum;
        char requestType;

        while (requestNum--) {
            file >> requestType;

            request* requestptr = nullptr;

            if (requestType == 'R') {
                char type;
                int RDAY, ID, TLOC, DUR;
                file >> type >> RDAY >> ID >> TLOC >> DUR;
                //cast the requestptr
                requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
            }
            else if (requestType == 'X') {
                int Xday;
                int id;
                file >> Xday >> id;
                requestptr = new Abort_Request(Xday, id);
            }
            //store in the request queue in Mars Station
            if (requestptr)
                this->requests.enqueue(requestptr);
        }
        file.close();
     /*   cout << "\n=== Avail_PR IN MARS STATION === \n";
        this->GET_AVAIL_PR().print();
        cout << "\n=== Avail_NR IN MARS STATION === \n";
        this->GET_AVAIL_NR().print();
        cout << "\n=== Avail_DR IN MARS STATION === \n";
        this->GET_AVAIL_DR().print();*/
    }
    //omar syed


    // Created By Kirolos Ashraf to assign missions to available rovers

    bool isRoversQueuesEmpty() {
        // function to check if there are any available rovers at all
        return available_Polar_Rovers.isEmpty() && available_Normal_Rovers.isEmpty() && available_Digging_Rovers.isEmpty();
    }

    void assigningMissionsToRovers() {
        if (isRoversQueuesEmpty()) {
            // if there are not available rovers, don't execute anything
            return;
        }

        if (!Ready_Polar_Missions.isEmpty()) {
            assignPMs(); // start assigning PMs
        }

        //if (isRoversQueuesEmpty()) {
        //    // if there are not available rovers, don't execute anything
        //    return;
        //}

        if (!Ready_Digging_Missions.isEmpty() && !available_Digging_Rovers.isEmpty()) {
            assignDMs(); // start assigning DMs
        }

        if (!Ready_Normal_Missions.isEmpty() && (!available_Normal_Rovers.isEmpty() || !available_Polar_Rovers.isEmpty())) {
            assignNMs(); // start assigning NMs
        }
    }

    void assignPMs() {
        while (!Ready_Polar_Missions.isEmpty()) {
            Mission* missionPtr = nullptr;
            if (!available_Polar_Rovers.isEmpty()) {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr)) {
                    Polar_Rovers* roverPtr;
                    available_Polar_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                }
            }
            else if (!available_Normal_Rovers.isEmpty()) {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr)) {
                    Normal_Rovers* roverPtr;
                    available_Normal_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                }
            }
            else if (!available_Digging_Rovers.isEmpty()) {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr)) {
                    Digging_Rovers* roverPtr;
                    available_Digging_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                }
            }
            else {
                // No available rovers
                break;
            }
            //set other mission parameters
            missionPtr->setMissionParameters(current_day);
            //add to ÒUT missions
            Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
        }
    }
    void assignDMs() {
        while (!Ready_Digging_Missions.isEmpty()) {
            Mission* missionPtr = nullptr;
            if (!available_Digging_Rovers.isEmpty()) {
                Ready_Digging_Missions.dequeue(missionPtr);
                Digging_Rovers* roverPtr;
                available_Digging_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else {
                // No available digging rovers
                break;
            }
            //set other mission parameters
            missionPtr->setMissionParameters(current_day);
            //add to ÒUT missions
            Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
        }
    }
    void assignNMs() {
        while (!Ready_Normal_Missions.isEmpty()) {
            Mission* missionPtr = nullptr;
            if (!available_Normal_Rovers.isEmpty()) {
                Ready_Normal_Missions.dequeue(missionPtr);
                Normal_Rovers* roverPtr;
                available_Normal_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else if (!available_Polar_Rovers.isEmpty()) {
                Ready_Normal_Missions.dequeue(missionPtr);
                Polar_Rovers* roverPtr;
                available_Polar_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else {
                // No available rovers
                break;
            }
            //set other mission parameters
            missionPtr->setMissionParameters(current_day);
            //add to ÒUT missions
            Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
        }
    }

    bool autoAbortPMs(Mission* m) {
        // any pm waiting in the ready list for more than double its duration should be automatically aborted
		if ((current_day - m->getRDY()) > (2 * m->getmissionDuration())) {
			AbortedMissions.push(m);
			return true;
		}
		return false;
    }
    // end of assigning - Created By Kirolos Ashraf

    void ChecknewRequests()
    {
        request* temp = nullptr;
        requests.peek(temp);
        while (!requests.isEmpty() && temp->getRequestDay() == current_day)
        {
            requests.dequeue(temp);
            temp->operate(*this);
        }
    }
    void movebacktodone()
    {
        Mission* backmission = nullptr;
        int pri;
        if (!BackMissions.isEmpty())
        {
            BackMissions.dequeue(backmission, pri);
            CompletedMissions.push(backmission);
            Rover* donerover = nullptr;
            donerover = backmission->getassignedRover();
            if (rand() % 100 < 20)
            {
                if (donerover->getType() == 'N')
                {
                    Checkup_Normal_Rovers.enqueue(dynamic_cast<Normal_Rovers*>(donerover));
                }
                else if (donerover->getType() == 'P')
                {
                    Checkup_Polar_Rovers.enqueue(dynamic_cast<Polar_Rovers*>(donerover));
                }
                else if (donerover->getType() == 'D')
                {
                    Checkup_Digging_Rovers.enqueue(dynamic_cast<Digging_Rovers*>(donerover));
                }
            }
            else
            {
                if (donerover->getType() == 'N')
                {
                    available_Normal_Rovers.enqueue(dynamic_cast<Normal_Rovers*>(donerover));
                }
                else if (donerover->getType() == 'P')
                {
                    available_Polar_Rovers.enqueue(dynamic_cast<Polar_Rovers*>(donerover));
                }
                else if (donerover->getType() == 'D')
                {
                    available_Digging_Rovers.enqueue(dynamic_cast<Digging_Rovers*>(donerover));
                }
            }
        }
    }
    void moveexecutedtoback()
    {
        Mission* executedmission1 = nullptr;
        Mission* executedmission2 = nullptr;
        int pri1;
        int pri2;
        if (!ExecMissions.isEmpty())
        {
            ExecMissions.dequeue(executedmission1, pri1);
            BackMissions.enqueue(executedmission1, pri1);
            if (!ExecMissions.isEmpty())
            {
                ExecMissions.dequeue(executedmission2, pri2);
                BackMissions.enqueue(executedmission2, pri2);
            }
        }
    }
    void moveNRfromcheckup()
    {
        Normal_Rovers* firstNrover = nullptr;
        if (Checkup_Normal_Rovers.dequeue(firstNrover))
        {
            available_Normal_Rovers.enqueue(firstNrover);
        }
    }
    void movePRfromcheckup()
    {
        Polar_Rovers* firstProver = nullptr;
        if (Checkup_Polar_Rovers.dequeue(firstProver))
        {
            available_Polar_Rovers.enqueue(firstProver);
        }
    }
    void moveDRfromcheckup()
    {
        Digging_Rovers* firstDrover = nullptr;
        if (Checkup_Digging_Rovers.dequeue(firstDrover))
        {
            available_Digging_Rovers.enqueue(firstDrover);
        }
    }
    void moveroversfromcheckuptoavailable()
    {
        if (rand() % 100 < 70)
        {
            if (!Checkup_Normal_Rovers.isEmpty())
            {
                moveNRfromcheckup();
            }
            else if (!Checkup_Polar_Rovers.isEmpty())
            {
                movePRfromcheckup();
            }
            else if (!Checkup_Digging_Rovers.isEmpty())
            {
                moveDRfromcheckup();
            }
        }
    }
    void moveouttoexecuted()
    {
        Mission* outmission = nullptr;
        int pri;
        if (!Out_Missions.isEmpty())
        {
            Out_Missions.dequeue(outmission, pri);
            ExecMissions.enqueue(outmission, pri);
        }
    }
    void incrementDay() {
        current_day++;
    }
    void assignMission()
    {
        Mission* missionPtr;
        while (true)
        {
            if (!Ready_Polar_Missions.isEmpty())
            {
                Ready_Polar_Missions.dequeue(missionPtr);
            }
            else if (!Ready_Digging_Missions.isEmpty()){
                Ready_Digging_Missions.dequeue(missionPtr);
            }
            else if (!Ready_Normal_Missions.isEmpty()){
                Ready_Normal_Missions.dequeue(missionPtr);
            }
            else {
                break; // No missions to assign
            }
            
            int c = rand() % 3;
            switch (c)
            {
            case 0:
                if (!available_Normal_Rovers.isEmpty())
                {
                    Normal_Rovers* roverPtr = nullptr;
                    available_Normal_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
                }
                break;
            case 1:
                if (!available_Polar_Rovers.isEmpty())
                {
                    Polar_Rovers* roverPtr = nullptr;
                    available_Polar_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
                }
                break;
            case 2:
                if (!available_Digging_Rovers.isEmpty())
                {
                    Digging_Rovers* roverPtr = nullptr;
                    available_Digging_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
                }
                break;
            }
        
       
        }
    }
    void printall()
    {
        cout << "Current Day: " << current_day << endl;
        cout << "================= Requests List =================" << endl;
        cout << requests.getCount() << " requests remaining: ";
       // requests.print();
        print_req(requests);
        cout << endl;
        cout << "================= Ready List(s) =================" << endl;
        int totalReady = Ready_Normal_Missions.getCount() + Ready_Polar_Missions.getCount() + Ready_Digging_Missions.getCount();
        cout << totalReady << " Missions: ";
        cout << "NMs"; Ready_Normal_Missions.print();
        cout << " PMs"; Ready_Polar_Missions.print();
        cout << " DMs"; Ready_Digging_Missions.print();
        cout << endl;
        cout << "================= Available Rovers List(s) =================" << endl;
        int totalRovers = available_Normal_Rovers.getCount() + available_Polar_Rovers.getCount() + available_Digging_Rovers.getCount();
        cout << totalRovers << " Available Rovers: ";
        cout << "NR"; available_Normal_Rovers.print();
        cout << " PR"; available_Polar_Rovers.print();
        cout << " DR"; available_Digging_Rovers.print();
        cout << endl;
        cout << "================= OUT List(s) =================" << endl;
        cout << Out_Missions.getCount() << " Missions/Rovers: ";
        Out_Missions.print();
        cout << endl;
        cout << "================= EXEC List(s) =================" << endl;
        cout << ExecMissions.getCount() << " Missions/Rovers: ";
        ExecMissions.print();
        cout << endl;
        cout << "================= BACK List(s) =================" << endl;
        cout << BackMissions.getCount() << " Missions/Rovers: ";
        BackMissions.print();
        cout << endl;
        cout << "================= Aborted List(s) =================" << endl;
        cout << AbortedMissions.getCount() << " Missions: ";
        AbortedMissions.print();
        cout << endl;
        cout << "================= Checkup List(s) =================" << endl;
        int totalCheckup = Checkup_Normal_Rovers.getCount() + Checkup_Polar_Rovers.getCount() + Checkup_Digging_Rovers.getCount();
        cout << totalCheckup << " Rovers: ";
        Checkup_Normal_Rovers.print();
        Checkup_Polar_Rovers.print();
        Checkup_Digging_Rovers.print();
        cout << endl;
        cout << "================= DONE List(s) =================" << endl;
        cout << CompletedMissions.getCount() << " Missions: ";
        CompletedMissions.print();
        cout << endl;
        cout << "===============================================" << endl;
    }
    void simulator()
    {
        ChecknewRequests();
        moveroversfromcheckuptoavailable();
        movebacktodone();
        moveexecutedtoback();
        moveouttoexecuted();
        assigningMissionsToRovers();
        printall();
        incrementDay();
    }
    LinkedQueue<request*>& getRequestsQueue()  {
        return requests;
    }
    LinkedQueue<Mission*>& getReadyDiggingMissions()  {
        return Ready_Digging_Missions;
    }
    LinkedQueue<Mission*>& getReadyPolarMissions()  {
        return Ready_Polar_Missions;
    }
    RDY_NM& getReadyNormalMissions()  {
        return Ready_Normal_Missions;
    }
    OUT_missions& getOutMissions() {
        return Out_Missions;
    }
    //// ==================================== = Omar Syed======================================/
    //void SET_AVAIL_PR(Polar_Rovers*& Avail_PR) {
    //    available_Polar_Rovers.enqueue(Avail_PR);
    //    POLAR_ROVER_SPEED = Avail_PR->getSpeed();
    //}

    //void SET_AVAIL_DR(Digging_Rovers*& Avail_DR) {
    //    available_Digging_Rovers.enqueue(Avail_DR);
    //    DIGGING_ROVER_SPEED = Avail_DR->getSpeed();
    //}

    //void SET_AVAIL_NR(Normal_Rovers*& Avail_NR) {
    //    available_Normal_Rovers.enqueue(Avail_NR);
    //    NORMAL_ROVER_SPEED = Avail_NR->getSpeed();
    //}



  /*  void SET_REQUEST_QUEUE(request* requestptr) {
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
    }*/
    /*void SET_RDM(Mission*DM) {
        Ready_Digging_Missions.enqueue(DM);
    }
    void SET_RPM(Mission*PM) {
        Ready_Digging_Missions.enqueue(PM);
    }
    void SET_RNM(Mission*NM) {
        Ready_Digging_Missions.enqueue(NM);
    }*/

    // ==================================== = Omar Syed======================================/
};


void New_Request::operate(Mars_Station& station) 
{

    Mission* newMission = new Mission(getRequestID(), location_distance, mission_duration, mission_type, getRequestDay());
    char type = getMissionType();
    if (type == 'N') {
        station.getReadyNormalMissions().enqueue(newMission);
    }
    else if (type == 'P') {
        station.getReadyPolarMissions().enqueue(newMission);
    }
    else if (type == 'D') {
        station.getReadyDiggingMissions().enqueue(newMission);
    }
}

void Abort_Request::operate(Mars_Station& station) 
{
    // The operation for aborting a mission will be handled in Mars_Station
}