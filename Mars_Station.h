//**************** Abdelrahman Tarek // Kirolos Ashraf // Omar Sayd // Marwan Nader ********************** */

#pragma once
#include "header.h"
#include "Request/Request.h"
#include <fstream>
#include <iostream>
#include "RDY_NM.h"
#include "OUT_missions.h"

// omar syed
// this function is used to print request list
void print_req(LinkedQueue<request *> &req)
{
    LinkedQueue<request *> temp;
    request *item = nullptr;
    while (req.dequeue(item))
    {
        if (New_Request *nrptr = dynamic_cast<New_Request *>(item))
        {
            cout << *nrptr;
        }
        else if (Abort_Request *arptr = dynamic_cast<Abort_Request *>(item))
        {
            cout << *arptr;
        }
        temp.enqueue(item);
    }
    while (temp.dequeue(item))
    {
        req.enqueue(item);
    }
}

class Mars_Station
{
private:
    int current_day;
    int failure_probability;
    int number_of_failed_missions=0;
    int NORMAL_ROVER_SPEED;
    int POLAR_ROVER_SPEED;
    int DIGGING_ROVER_SPEED;
    LinkedQueue<request *> requests;
    LinkedQueue<Mission *> Ready_Digging_Missions;
    LinkedQueue<Mission *> Ready_Polar_Missions;
    LinkedQueue<Complex_Mission *> Ready_Complex_Missions;
    RDY_NM Ready_Normal_Missions;
    OUT_missions Out_Missions;
    priQueue<Mission *> Rescue_Missions;
    priQueue<Mission *> ExecMissions;
    priQueue<Mission *> BackMissions;
    ArrayStack<Mission *> CompletedMissions;
    ArrayStack<Mission *> AbortedMissions;
    LinkedQueue<Mission*> Failed_Missions;
    LinkedQueue<Normal_Rovers *> available_Normal_Rovers;
    LinkedQueue<Polar_Rovers *> available_Polar_Rovers;
    LinkedQueue<Digging_Rovers *> available_Digging_Rovers;
    LinkedQueue<Rescue_Rovers *> available_Rescue_Rovers;
    priQueue<Normal_Rovers *> Checkup_Normal_Rovers;
    priQueue<Polar_Rovers *> Checkup_Polar_Rovers;
    priQueue<Digging_Rovers *> Checkup_Digging_Rovers;
    priQueue<Rescue_Rovers *> Checkup_Rescue_Rovers;

public:

    Mars_Station() : current_day(1) {}
    ~Mars_Station()
    {
        request *reqPtr = nullptr;
        Mission *missionPtr = nullptr;
        int x = 0;
        while (!requests.isEmpty())
        {
            requests.dequeue(reqPtr);
            delete reqPtr;
        }
        while (!available_Normal_Rovers.isEmpty())
        {
            Normal_Rovers *roverPtr = nullptr;
            available_Normal_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!available_Polar_Rovers.isEmpty())
        {
            Polar_Rovers *roverPtr = nullptr;
            available_Polar_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!available_Digging_Rovers.isEmpty())
        {
            Digging_Rovers *roverPtr = nullptr;
            available_Digging_Rovers.dequeue(roverPtr);
            delete roverPtr;
        }
        while (!Checkup_Normal_Rovers.isEmpty())
        {
            Normal_Rovers *roverPtr = nullptr;
            int pri;
            Checkup_Normal_Rovers.dequeue(roverPtr,pri);
            delete roverPtr;
        }
        while (!Checkup_Polar_Rovers.isEmpty())
        {
            Polar_Rovers *roverPtr = nullptr;
            int pri;
            Checkup_Polar_Rovers.dequeue(roverPtr,pri);
            delete roverPtr;
        }
        while (!Checkup_Digging_Rovers.isEmpty())
        {
            Digging_Rovers *roverPtr = nullptr;
            int pri;
            Checkup_Digging_Rovers.dequeue(roverPtr,pri);
            delete roverPtr;
        }
        while (!AbortedMissions.isEmpty())
        {
            Mission *missionPtr = nullptr;
            AbortedMissions.pop(missionPtr);
            delete missionPtr;
        }
        while (!CompletedMissions.isEmpty())
        {
            Mission *missionPtr = nullptr;
            CompletedMissions.pop(missionPtr);
            delete missionPtr;
        }
        while (Ready_Digging_Missions.dequeue(missionPtr))
        {
            delete missionPtr;
        }
        while (Ready_Polar_Missions.dequeue(missionPtr))
        {
            delete missionPtr;
        }
        while (Ready_Normal_Missions.dequeue(missionPtr))
        {
            delete missionPtr;
        }
        while (Out_Missions.dequeue(missionPtr, x))
        {
            delete missionPtr;
        }
        while (ExecMissions.dequeue(missionPtr, x))
        {
            delete missionPtr;
        }
        while (BackMissions.dequeue(missionPtr, x))
        {
            delete missionPtr;
        }
    }


    int getprobability_of_failure() const
    {
        return failure_probability;
    }
    // omar syed
    void setFailureProbability(int p)
    {
        failure_probability = p;
    }
    void FILE_LOADING(string fileName)
    {
        // read data from a file and store it into data structures
        // open the file
        int roverCounts[4] = {0, 0, 0, 0};
        int roverSpeed[4] = {0, 0, 0, 0};
        int *checkupDurations = nullptr;
        int checkupNum = 0;
        ifstream file(fileName);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        // read data from the file
        int i = 0;
        file >> roverCounts[0] >> roverCounts[1] >> roverCounts[2] >> roverCounts[3];
        file >> roverSpeed[0] >> roverSpeed[1] >> roverSpeed[2] >> roverSpeed[3];
        file >> checkupNum;
        checkupDurations = new int[4];

        i = 0;
        while (i < 4)
        {
            file >> checkupDurations[i];
            i++;
        }
        Digging_Rovers *nDptr = nullptr;
        Polar_Rovers *nPptr = nullptr;
        Normal_Rovers *nNptr = nullptr;
        Rescue_Rovers *nRptr;
        for (int j = 0; j < roverCounts[0]; j++)
        {
            nDptr = new Digging_Rovers(roverSpeed[0], checkupNum, checkupDurations[0]);
            this->available_Digging_Rovers.enqueue(nDptr);
        }
        DIGGING_ROVER_SPEED = roverSpeed[0];
        for (int j = 0; j < roverCounts[1]; j++)
        {
            nPptr = new Polar_Rovers(roverSpeed[1], checkupNum, checkupDurations[1]);
            this->available_Polar_Rovers.enqueue(nPptr);
        }
        POLAR_ROVER_SPEED = roverSpeed[1];
        for (int j = 0; j < roverCounts[2]; j++)
        {
            nNptr = new Normal_Rovers(roverSpeed[2], checkupNum, checkupDurations[2]);
            this->available_Normal_Rovers.enqueue(nNptr);
            NORMAL_ROVER_SPEED = roverSpeed[2];
        }
        for (int j = 0; j < roverCounts[3]; j++)
        {
            nRptr = new Rescue_Rovers(roverSpeed[3], checkupNum, checkupDurations[3]);
            this->available_Rescue_Rovers.enqueue(nRptr);
        }

        delete[] checkupDurations;


        int probability_of_failure;
        file >> probability_of_failure;
        this->setFailureProbability(probability_of_failure);

        int requestNum;
        file >> requestNum;
        char requestType;

        while (requestNum--)
        {
            file >> requestType;

            request *requestptr = nullptr;

            if (requestType == 'R')
            {
                char type;
                int RDAY, ID, TLOC, DUR;
                file >> type >> RDAY >> ID >> TLOC >> DUR;
                // cast the requestptr
                requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
            }
            else if (requestType == 'X')
            {
                int Xday;
                int id;
                file >> Xday >> id;
                requestptr = new Abort_Request(Xday, id);
            }
            // store in the request queue in Mars Station
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
    // omar syed

    // Created By Kirolos Ashraf to assign missions to available rovers / abort

    bool isRoversQueuesEmpty()
    {
        // function to check if there are any available rovers at all
        return available_Polar_Rovers.isEmpty() && available_Normal_Rovers.isEmpty() && available_Digging_Rovers.isEmpty();
    }

    void assigningMissionsToRovers()
    {
        assignRescueMissions();
            
        if (isRoversQueuesEmpty())
        {
            return;
        }

        if (!Ready_Complex_Missions.isEmpty()){
            assignCMs(); // start assigning CMs
        }
        if (!Ready_Polar_Missions.isEmpty())
        {
            assignPMs(); // start assigning PMs
        }
        if (!Ready_Digging_Missions.isEmpty() && !available_Digging_Rovers.isEmpty())
        {
            assignDMs(); // start assigning DMs
        }

        if (!Ready_Normal_Missions.isEmpty() && (!available_Normal_Rovers.isEmpty() || !available_Polar_Rovers.isEmpty()))
        {
            assignNMs(); // start assigning NMs
        }

    }
   void checkMissionFailure() {
    Mission* m = nullptr;
    int pri = 0;
    
    // --- Handle Out_Missions ---
    int count = Out_Missions.getCount();
    priQueue<Mission*> tempQueue; // Temporary queue to hold survivors
    
    // 1. Process all missions in Out_Missions
    for (int i = 0; i < count; i++) {
        Out_Missions.dequeue(m, pri);
        int randProb = rand() % 100 + 1; 
        
        bool isRescueRover = (m->getassignedRover()->getType() == 'R');

        if (randProb <= failure_probability && !isRescueRover) { 
            handleFailure(m); 
            number_of_failed_missions++;   
        } else {
            // Store survivor in tempQueue instead of putting it back immediately
            tempQueue.enqueue(m, pri);
        }
    }

    // 2. Restore survivors from tempQueue back to Out_Missions
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(m, pri);
        Out_Missions.enqueue(m, pri);
    }

    // --- Handle ExecMissions ---
    count = ExecMissions.getCount();
    
    // 3. Process all missions in ExecMissions
    for (int i = 0; i < count; i++) {
        ExecMissions.dequeue(m, pri);
        int randProb = rand() % 100 + 1;
        
        bool isRescueRover = (m->getassignedRover()->getType() == 'R');

        if (randProb <= failure_probability && !isRescueRover) {
            handleFailure(m);
            number_of_failed_missions++;
        } else {
            // Store survivor in tempQueue
            tempQueue.enqueue(m, pri);
        }
    }

    // 4. Restore survivors from tempQueue back to ExecMissions
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(m, pri);
        ExecMissions.enqueue(m, pri);
    }
}
    void handleFailure(Mission* m) {
    Rover* failedRover = m->getassignedRover();
    
    // Calculate journey back
    int journeyBack = 0;
    if (m->getmissionstate() == STATE::OUT) {
        journeyBack = current_day - m->get_assigned_to_rover_day();
    } else {
        journeyBack = m->get_journey_days();
    }
    
    // 1. Handle Failed Rover (r1)
    if(failedRover) {
        failedRover->setCheckupEndDay(current_day + journeyBack + failedRover->getCheckupDuration());
        failedRover->resetMissionsDone(); 
        
        char rType = failedRover->getType();
        if (rType == 'N') Checkup_Normal_Rovers.enqueue((Normal_Rovers*)failedRover, failedRover->getCheckupEndDay());
        else if (rType == 'P') Checkup_Polar_Rovers.enqueue((Polar_Rovers*)failedRover, failedRover->getCheckupEndDay());
        else if (rType == 'D') Checkup_Digging_Rovers.enqueue((Digging_Rovers*)failedRover, failedRover->getCheckupEndDay());
        else if (rType == 'R') Checkup_Rescue_Rovers.enqueue((Rescue_Rovers*)failedRover, failedRover->getCheckupEndDay());
    }

    // 2. Handle Second Rover (r2) for Complex Missions
    if (m->getMissionType() == 'C') {
        Complex_Mission* cMission = dynamic_cast<Complex_Mission*>(m);
        Rover* rover2 = cMission->getassignedRover2();
        
        if (rover2) {
            // Recalculate journey for r2 if needed, or use same logic
            int journeyBack2 = ceil((double)m->getLocation() / rover2->getSpeed() / 25.0);
            
            rover2->setCheckupEndDay(current_day + journeyBack2 + rover2->getCheckupDuration());
            rover2->resetMissionsDone();

            char rType2 = rover2->getType();
            if (rType2 == 'N') Checkup_Normal_Rovers.enqueue((Normal_Rovers*)rover2, rover2->getCheckupEndDay());
            else if (rType2 == 'P') Checkup_Polar_Rovers.enqueue((Polar_Rovers*)rover2, rover2->getCheckupEndDay());
            else if (rType2 == 'D') Checkup_Digging_Rovers.enqueue((Digging_Rovers*)rover2, rover2->getCheckupEndDay());
            // Note: r2 is never 'R' type in a normal complex mission setup
            cMission->setRover(nullptr, nullptr); // Clear both rovers
        }
    }

    m->setmissionstate(STATE::FAILED);
    m->setRover(nullptr); // Clear r1 so it can be replaced by Rescue Rover
    Failed_Missions.enqueue(m); 
}


void assignRescueMissions()
{
    Mission* failedMission = nullptr;
    Rescue_Rovers* rescueRover = nullptr;

    while (!Failed_Missions.isEmpty() && !available_Rescue_Rovers.isEmpty())
    {
        Failed_Missions.dequeue(failedMission);
        available_Rescue_Rovers.dequeue(rescueRover);

        // FIX: Explicitly handle Complex Missions to ensure the internal pointer is updated
        if (failedMission->getMissionType() == 'C') {
            Complex_Mission* cMission = dynamic_cast<Complex_Mission*>(failedMission);
            if (cMission) {
                
                cMission->setRover((Digging_Rovers*)rescueRover, nullptr); 
            } 
            else {
                failedMission->setRover(rescueRover);
            }
        } 
        else {
            failedMission->setRover(rescueRover);
        }

        failedMission->setMissionParameters(current_day); 
        failedMission->setmissionstate(STATE::OUT); 
        
        Out_Missions.enqueue(failedMission, failedMission->get_execution_start_day());
    }
}

    void assignCMs()
    {
        while (!Ready_Complex_Missions.isEmpty())
        {
            Complex_Mission *missionPtr = nullptr;
            if (!available_Digging_Rovers.isEmpty() && (!available_Polar_Rovers.isEmpty() || !available_Normal_Rovers.isEmpty()))
            {
                 if (!available_Normal_Rovers.isEmpty())
                {
                    Ready_Complex_Missions.dequeue(missionPtr);
                    Digging_Rovers *dRoverPtr;
                    Normal_Rovers *nRoverPtr;
                    available_Digging_Rovers.dequeue(dRoverPtr);
                    available_Normal_Rovers.dequeue(nRoverPtr);
                    missionPtr->setRover(dRoverPtr, nRoverPtr);
                }
                else
                if (!available_Polar_Rovers.isEmpty())
                {
                    Ready_Complex_Missions.dequeue(missionPtr);
                    Digging_Rovers *dRoverPtr;
                    Polar_Rovers *pRoverPtr;
                    available_Digging_Rovers.dequeue(dRoverPtr);
                    available_Polar_Rovers.dequeue(pRoverPtr);
                    missionPtr->setRover(dRoverPtr, pRoverPtr);
                }
               
            }
            else
            {
                break;
            }
            // set other mission parameters
            missionPtr->setMissionParameters(current_day);
            // add to OUT missions
            Out_Missions.enqueue(missionPtr, missionPtr->get_execution_start_day());
            missionPtr->setmissionstate(STATE::OUT);
        }
    }
    void assignPMs()
    {
        while (!Ready_Polar_Missions.isEmpty())
        {
            Mission *missionPtr = nullptr;
            bool assigned = false;
            if (!available_Polar_Rovers.isEmpty())
            {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr))
                {
                    Polar_Rovers *roverPtr;
                    available_Polar_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    assigned = true;
                }
                else
                {
                    continue; // skip to next iteration if mission was aborted
                }
            }
            else if (!available_Normal_Rovers.isEmpty())
            {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr))
                {
                    Normal_Rovers *roverPtr;
                    available_Normal_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    assigned = true;
                }
                else
                {
                    continue; // skip to next iteration if mission was aborted
                }
            }
            else if (!available_Digging_Rovers.isEmpty())
            {
                Ready_Polar_Missions.dequeue(missionPtr);
                if (!autoAbortPMs(missionPtr))
                {
                    Digging_Rovers *roverPtr;
                    available_Digging_Rovers.dequeue(roverPtr);
                    missionPtr->setRover(roverPtr);
                    assigned = true;
                }
                else
                {
                    continue; // skip to next iteration if mission was aborted
                }
            }
            else
            {
                // No available rovers
                break;
            }
            if (assigned)
            {
                // set other mission parameters
                // add to �UT missions
                missionPtr->setMissionParameters(current_day);
                Out_Missions.enqueue(missionPtr, missionPtr->get_execution_start_day());
                missionPtr->setmissionstate(STATE::OUT);
            }
        }
    }
    void assignDMs()
    {
        while (!Ready_Digging_Missions.isEmpty())
        {
            Mission *missionPtr = nullptr;
            if (!available_Digging_Rovers.isEmpty())
            {
                Ready_Digging_Missions.dequeue(missionPtr);
                Digging_Rovers *roverPtr;
                available_Digging_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else
            {
                // No available digging rovers
                break;
            }
            // set other mission parameters
            missionPtr->setMissionParameters(current_day);
            // add to OUT missions
            Out_Missions.enqueue(missionPtr, missionPtr->get_execution_start_day());
            missionPtr->setmissionstate(STATE::OUT);
        }
    }
    void assignNMs()
    {
        while (!Ready_Normal_Missions.isEmpty())
        {
            Mission *missionPtr = nullptr;
            if (!available_Normal_Rovers.isEmpty())
            {
                Ready_Normal_Missions.dequeue(missionPtr);
                Normal_Rovers *roverPtr;
                available_Normal_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else if (!available_Polar_Rovers.isEmpty())
            {
                Ready_Normal_Missions.dequeue(missionPtr);
                Polar_Rovers *roverPtr;
                available_Polar_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
            else
            {
                // No available rovers
                break;
            }
            // set other mission parameters
            missionPtr->setMissionParameters(current_day);
            // add to �UT missions
            Out_Missions.enqueue(missionPtr, missionPtr->get_execution_start_day());
            missionPtr->setmissionstate(STATE::OUT);
        }
    }

    bool autoAbortPMs(Mission *m)
    {
        // any pm waiting in the ready list for more than double its duration should be automatically aborted
        if ((current_day - m->get_ready_day()) > (2 * m->getmissionDuration()))
        {
            AbortedMissions.push(m);
            return true;
        }
        return false;
    }

    bool AbortMission(int missionID)
    {
        Mission *abortedMission = nullptr;
        if (abortedMission = Ready_Normal_Missions.AbortMission(missionID))
        {
            AbortedMissions.push(abortedMission);
            return true;
        }
        else if (abortedMission = Out_Missions.AbortMission(missionID))
        {
            int backJourney = 2 * current_day - abortedMission->get_assigned_to_rover_day();
            abortedMission->setmissionstate(STATE::ABORTED);
            abortedMission->setFinished_day_parameterized(backJourney);
            BackMissions.enqueue(abortedMission, backJourney);
            return true;
        }
        return false;
    }
    // end of assigning / aborting - Created By Kirolos Ashraf

    void ChecknewRequests()
    {
        request *temp = nullptr;
        requests.peek(temp);
        while (!requests.isEmpty() && temp->getRequestDay() <= current_day)
        {
            requests.dequeue(temp);
            temp->operate(*this);
            requests.peek(temp);
        }
    }
void movebacktodone_abort()
{
    Mission *backmission = nullptr;
    int pri;
    int count = BackMissions.getCount(); 
    priQueue<Mission *> tempQueue;

    for (int i = 0; i < count; i++)
    {
        BackMissions.dequeue(backmission, pri);

        int finDay = backmission->get_finished_day(); 

        if (finDay <= current_day) 
        {
            if (backmission->getMissionType() == 'C')
            {
                CompletedMissions.push(backmission);
                backmission->setmissionstate(STATE::DONE);

                Complex_Mission* cMission = dynamic_cast<Complex_Mission*>(backmission);
                if (cMission) {
                    Rover* r1 = cMission->getassignedRover();
                    
                    bool isRescued = (r1 && r1->getType() == 'R');

                    if (r1) {
                        r1->incrementMissionsDone();
                        Rovermaintancecheckup(r1);
                    }
                    
                    if (!isRescued) {
                        Rover* r2 = cMission->getassignedRover2();
                        if (r2) {
                            r2->incrementMissionsDone();
                            Rovermaintancecheckup(r2);
                        }
                    }
                }
            }
            else if (backmission->getmissionstate() == STATE::ABORTED)
            {
                AbortedMissions.push(backmission);
                Rover *abortrover = backmission->getassignedRover();
                if (abortrover) Rovermaintancecheckup(abortrover);
            }
            else
            {
                CompletedMissions.push(backmission);
                backmission->setmissionstate(STATE::DONE);
                Rover *donerover = backmission->getassignedRover();
                if (donerover) {
                    donerover->incrementMissionsDone();
                    Rovermaintancecheckup(donerover);
                }
            }
        }
        else
        {
            tempQueue.enqueue(backmission, pri);
        }
    }
    while (!tempQueue.isEmpty())
    {
        tempQueue.dequeue(backmission, pri);
        BackMissions.enqueue(backmission, pri);
    }
}
    void Rovermaintancecheckup(Rover *donerover)
    {
        if (donerover->getMissionsDone() >= donerover->getDaysBeforeCheckup())
        {
            donerover->setCheckupEndDay(current_day + donerover->getCheckupDuration());
            donerover->resetMissionsDone();
            
            if (donerover->getType() == 'N')
            {
                Checkup_Normal_Rovers.enqueue(dynamic_cast<Normal_Rovers *>(donerover), donerover->getCheckupEndDay());
            }
            else if (donerover->getType() == 'P')
            {
                Checkup_Polar_Rovers.enqueue(dynamic_cast<Polar_Rovers *>(donerover), donerover->getCheckupEndDay());
            }
            else if (donerover->getType() == 'D')
            {
                Checkup_Digging_Rovers.enqueue(dynamic_cast<Digging_Rovers *>(donerover), donerover->getCheckupEndDay());
            }
            else if (donerover->getType() == 'R')
            {
                Checkup_Rescue_Rovers.enqueue(dynamic_cast<Rescue_Rovers *>(donerover), donerover->getCheckupEndDay());
            }
        }
        // else
        // {
        //     if (donerover->getType() == 'N')
        //     {
        //         available_Normal_Rovers.enqueue(dynamic_cast<Normal_Rovers *>(donerover));
        //     }
        //     else if (donerover->getType() == 'P')
        //     {
        //         available_Polar_Rovers.enqueue(dynamic_cast<Polar_Rovers *>(donerover));
        //     }
        //     else if (donerover->getType() == 'D')
        //     {
        //         available_Digging_Rovers.enqueue(dynamic_cast<Digging_Rovers *>(donerover));
        //     }
        //     else if (donerover->getType() == 'R')
        //     {
        //         available_Rescue_Rovers.enqueue(dynamic_cast<Rescue_Rovers *>(donerover));
        //     }
        // }
    }
void moveexecutedtoback()
{
    Mission *execmission = nullptr;
    int pri;
    int count = ExecMissions.getCount(); // Get the number of executing missions
    priQueue<Mission *> tempQueue; // Temporary queue to hold missions

    // Iterate through ALL missions in the Execution list
    for (int i = 0; i < count; i++)
    {
        ExecMissions.dequeue(execmission, pri);
        
        int finishDay = execmission->get_finished_execution_day();
        
        // Check if the mission has finished execution
        if (finishDay <= current_day)
        {
            // Move to Back List
            execmission->setmissionstate(STATE::BACK);
            BackMissions.enqueue(execmission, execmission->get_journey_days());
        }
        else
        {
            // Not finished yet, put it back
            tempQueue.enqueue(execmission, pri);
        }
    }
    while (!tempQueue.isEmpty())
    {
        tempQueue.dequeue(execmission, pri);
        ExecMissions.enqueue(execmission, pri);
    }
}
    void moveNRfromcheckup()
    {
        Normal_Rovers *firstNrover = nullptr;
        int pri;
        if (Checkup_Normal_Rovers.dequeue(firstNrover, pri))
        {
            available_Normal_Rovers.enqueue(firstNrover);
        }
    }

    void movePRfromcheckup()
    {
        Polar_Rovers *firstProver = nullptr;
        int pri;
        if (Checkup_Polar_Rovers.dequeue(firstProver,pri))
        {
            available_Polar_Rovers.enqueue(firstProver);
        }
    }

    void moveDRfromcheckup()
    {
        Digging_Rovers *firstDrover = nullptr;
        int pri;
        if (Checkup_Digging_Rovers.dequeue(firstDrover,pri))
        {
            available_Digging_Rovers.enqueue(firstDrover);
        }
    }
    void moveroversfromcheckuptoavailable()
{
    int pri;
    int count;
    priQueue<Normal_Rovers*> tempQueueN;
    priQueue<Polar_Rovers*> tempQueueP;
    priQueue<Digging_Rovers*> tempQueueD;
    priQueue<Rescue_Rovers*> tempQueueR;

    // 1. Normal Rovers
    Normal_Rovers* nr = nullptr;
    count = Checkup_Normal_Rovers.getCount();
    for (int i = 0; i < count; i++) {
        Checkup_Normal_Rovers.dequeue(nr, pri);
        // FIX: Check <= current_day to release any overdue rovers
        if (nr->getCheckupEndDay() <= current_day) { 
            available_Normal_Rovers.enqueue(nr);
        } else {
            tempQueueN.enqueue(nr, pri);
        }
    }
    while (!tempQueueN.isEmpty()) {
        tempQueueN.dequeue(nr, pri);
        Checkup_Normal_Rovers.enqueue(nr, pri);
    }

    // 2. Polar Rovers
    Polar_Rovers* pr = nullptr;
    count = Checkup_Polar_Rovers.getCount();
    for (int i = 0; i < count; i++) {
        Checkup_Polar_Rovers.dequeue(pr, pri);
        if (pr->getCheckupEndDay() <= current_day) {
            available_Polar_Rovers.enqueue(pr);
        } else {
            tempQueueP.enqueue(pr, pri);
        }
    }
    while (!tempQueueP.isEmpty()) {
        tempQueueP.dequeue(pr, pri);
        Checkup_Polar_Rovers.enqueue(pr, pri);
    }

    // 3. Digging Rovers
    Digging_Rovers* dr = nullptr;
    count = Checkup_Digging_Rovers.getCount();
    for (int i = 0; i < count; i++) {
        Checkup_Digging_Rovers.dequeue(dr, pri);
        if (dr->getCheckupEndDay() <= current_day) {
            available_Digging_Rovers.enqueue(dr);
        } else {
            tempQueueD.enqueue(dr, pri);
        }
    }
    while (!tempQueueD.isEmpty()) {
        tempQueueD.dequeue(dr, pri);
        Checkup_Digging_Rovers.enqueue(dr, pri);
    }

    // 4. Rescue Rovers
    Rescue_Rovers* rr = nullptr;
    count = Checkup_Rescue_Rovers.getCount();
    for (int i = 0; i < count; i++) {
        Checkup_Rescue_Rovers.dequeue(rr, pri);
        if (rr->getCheckupEndDay() <= current_day) {
            available_Rescue_Rovers.enqueue(rr);
        } else {
            tempQueueR.enqueue(rr, pri);
        }
    }
    while (!tempQueueR.isEmpty()) {
        tempQueueR.dequeue(rr, pri);
        Checkup_Rescue_Rovers.enqueue(rr, pri);
    }
}
    void moveouttoexecuted()
    {
        Mission *outmission = nullptr;
        int pri;
        while (!Out_Missions.isEmpty() && Out_Missions.peek(outmission, pri))
        {
            int execDay = outmission->get_execution_start_day();
            if (execDay == current_day)
            {
                Out_Missions.dequeue(outmission, pri);
                outmission->setmissionstate(STATE::EXECUTING);
                ExecMissions.enqueue(outmission, outmission->get_finished_execution_day());
            }
            else
            {
                break;
            }
        }
    }
    void incrementDay()
    {
        current_day++;
    }
   
    void simulator()
    {
        ChecknewRequests();
        moveroversfromcheckuptoavailable();
        checkMissionFailure();
        assigningMissionsToRovers();
        moveouttoexecuted();
        moveexecutedtoback();
        movebacktodone_abort();
        incrementDay();
    }
   

    LinkedQueue<Mission *> *getFailedMissions()
    {
        return &Failed_Missions;
    }
    LinkedQueue<request *> *getRequestsQueue()
    {
        return &requests;
    }
    LinkedQueue<Mission *> *getReadyDiggingMissions()
    {
        return &Ready_Digging_Missions;
    }
    LinkedQueue<Mission *> *getReadyPolarMissions()
    {
        return &Ready_Polar_Missions;
    }
    RDY_NM *getReadyNormalMissions()
    {
        return &Ready_Normal_Missions;
    }
    OUT_missions *getOutMissions()
    {
        return &Out_Missions;
    }
    priQueue<Mission *> *getExecMissions()
    {
        return &ExecMissions;
    }
    priQueue<Mission *> *getBackMissions()
    {
        return &BackMissions;
    }
    LinkedQueue<Complex_Mission *> *getReadyComplexMissions()
    {
        return &Ready_Complex_Missions;
    }
   

    LinkedQueue<Complex_Mission *> *getReadyComplexMissionsQueue()
    {
        return &Ready_Complex_Missions;
    }
    
    LinkedQueue<Normal_Rovers *> *getAvailableNormalRovers()
    {
        return &available_Normal_Rovers;
    }

    LinkedQueue<Polar_Rovers *> *getAvailablePolarRovers()
    {
        return &available_Polar_Rovers;
    }

    LinkedQueue<Digging_Rovers *> *getAvailableDiggingRovers()
    {
        return &available_Digging_Rovers;
    }

    LinkedQueue<Rescue_Rovers *> *getAvailableRescueRovers()
    {
        return &available_Rescue_Rovers;
    }

    priQueue<Normal_Rovers *> *getCheckupNormalRovers()
    {
        return &Checkup_Normal_Rovers;
    }

    priQueue<Polar_Rovers *> *getCheckupPolarRovers()
    {
        return &Checkup_Polar_Rovers;
    }

    priQueue<Digging_Rovers *> *getCheckupDiggingRovers()
    {
        return &Checkup_Digging_Rovers;
    }

    priQueue<Rescue_Rovers *> *getCheckupRescueRovers()
    {
        return &Checkup_Rescue_Rovers;
    }

    int get_current_day() const { return current_day; }

    void generateOutputFile(string outputfile)
    {
        ofstream out(outputfile);
        if (!out.is_open())
        {
            cout << "Error: Could not create output file!" << endl;
            return;
        }

        out << "Fday\tID\tRday\tWdays\tMDUR\tTdays\n";

        const int completemissionCount = CompletedMissions.getCount();
        int missionCount = CompletedMissions.getCount() + AbortedMissions.getCount();

        Mission **missions = new Mission *[completemissionCount];

        int totalMissions = 0;
        int normalCount = 0, polarCount = 0, diggingCount = 0,complexcount=0;
        int totalWDAY = 0;
        int totalMDUR = 0;
        int totalTDays = 0;

        int index = 0;
        while (!CompletedMissions.isEmpty())
        {
            Mission *m;
            CompletedMissions.pop(m);
            missions[index++] = m;
        }

        for (int i = 0; i < completemissionCount - 1; i++)
        {
            for (int j = 0; j < completemissionCount - i - 1; j++)
            {
                if ((missions[j]->get_assigned_to_rover_day() + missions[j]->getmissionDuration() + missions[j]->get_remaining_day()) > (missions[j + 1]->get_assigned_to_rover_day() + missions[j + 1]->getmissionDuration() + missions[j + 1]->get_remaining_day()))
                {
                    Mission *temp = missions[j];
                    missions[j] = missions[j + 1];
                    missions[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < completemissionCount; i++)
        {
            Mission *m = missions[i];

            int Rday = m->get_ready_day();
            int Lday = m->get_assigned_to_rover_day();
            int Wdays = Lday - Rday;

            int Tdays = m->getmissionDuration() + m->get_remaining_day();
            int Fday = Lday + Tdays;

            out << Fday << "\t"
                << m->getID() << "\t"
                << Rday << "\t"
                << Wdays << "\t"
                << m->getmissionDuration() << "\t"
                << Tdays << "\n";

            totalMissions++;
            totalWDAY += Wdays;
            totalMDUR += m->getmissionDuration();
            totalTDays += Tdays;

            char type = m->getMissionType();
            if (type == 'N')
            {
                normalCount++;
            }
            else if (type == 'P')
            {
                polarCount++;
            }
            else if (type == 'D')
            {
                diggingCount++;
            }
            else
            if (type == 'C')
            {
                complexcount++;
            }

            CompletedMissions.push(m);
        }

        delete[] missions;

        out << "\n-----------------------------------------------------------\n\n";
        out << "-----------------------------------------------------------\n\n";

        int abortedCount = AbortedMissions.getCount();

        int abortedNormal = 0, abortedPolar = 0;

        ArrayStack<Mission *> tempAborted;
        while (!AbortedMissions.isEmpty())
        {
            Mission *m;
            AbortedMissions.pop(m);
            char type = m->getMissionType();
            if (type == 'N')
            {
                abortedNormal++;
            }
            else if (type == 'P')
            {
                abortedPolar++;
            }
            tempAborted.push(m);
        }

        while (!tempAborted.isEmpty())
        {
            Mission *m;
            tempAborted.pop(m);
            AbortedMissions.push(m);
        }

        normalCount += abortedNormal;
        polarCount += abortedPolar;

        int totalCount = totalMissions + abortedCount;

        out << "Missions: " << totalCount
            << "\t[N: " << normalCount
            << ", P: " << polarCount
            << ", D: " << diggingCount << ", C: " << complexcount << "] "
            << "[" << totalMissions << " DONE, "
            << abortedCount << " Aborted]\n";

        out << "Rovers: " << available_Normal_Rovers.getCount() + available_Polar_Rovers.getCount() + available_Digging_Rovers.getCount()
            << "\t[N: " << available_Normal_Rovers.getCount()
            << ", P: " << available_Polar_Rovers.getCount()
            << ", D: " << available_Digging_Rovers.getCount() << "]\n";

        double avgWdays = (double)totalWDAY / totalMissions;
        double avgMDUR = (double)totalMDUR / totalMissions;
        double avgTdays = (double)totalTDays / totalMissions;

        out << "Avg Wdays = " << avgWdays
            << ", Avg MDUR = " << avgMDUR
            << ", Avg Tdays = " << avgTdays << "\n";

        double Wdays_MDUR = (avgWdays / avgMDUR) * 100;
        double AutoAborted = 0;
        if (abortedCount != 0)
        {
            AutoAborted = ((double)abortedPolar / abortedCount);
        }

        out << "% Avg_Wdays/ Avg_MDUR = " << Wdays_MDUR << "%, "
            << "Auto-aborted= " << AutoAborted * 100 << "%\n";
        out << "Num of failed missions: " << number_of_failed_missions << "\n";
        out.close();
    }

    ArrayStack<Mission *> *getDoneMissions() { return &CompletedMissions; }

    ArrayStack<Mission *> *getAbortedMissions() { return &AbortedMissions; }
};

void New_Request::operate(Mars_Station &station)
{

    char type = getMissionType();
    if (type == 'N')
    {
        Mission *newMission = new Mission(getRequestID(), location_distance, mission_duration, mission_type, getRequestDay());
        station.getReadyNormalMissions()->enqueue(newMission);
        newMission->setmissionstate(STATE::READY);
    }
    else if (type == 'P')
    {
        Mission *newMission = new Mission(getRequestID(), location_distance, mission_duration, mission_type, getRequestDay());
        station.getReadyPolarMissions()->enqueue(newMission);
        newMission->setmissionstate(STATE::READY);
    }
    else if (type == 'D')
    {
        Mission *newMission = new Mission(getRequestID(), location_distance, mission_duration, mission_type, getRequestDay());
        station.getReadyDiggingMissions()->enqueue(newMission);
        newMission->setmissionstate(STATE::READY);
    }
    else if (type == 'C')
    {

        Complex_Mission *complexMission = new Complex_Mission(getRequestID(), location_distance, mission_duration, getRequestDay());
        station.getReadyComplexMissions()->enqueue(complexMission);
        complexMission->setmissionstate(STATE::READY);
    }
}

void Abort_Request::operate(Mars_Station &station)
{
    int abortedID = getAbortedRequestID();
    station.AbortMission(abortedID);
}
