#pragma once
#include <iostream>
#include <string>
#include "Mars_Station.h"
using namespace std;

class UI {
private:
    int mode; // 1 Interactive         2 Silent

public:
    UI() {
        mode = -1;
    }

    ~UI() {}

    void selectMode() {
        int uInput = -1;
        while (uInput != 1 && uInput != 2) {
            cout << "Select Simulation Mode:\n";
            cout << "1. Interactive Mode\n";
            cout << "2. Silent Mode\n";
            cin >> uInput;

            if (uInput == 1) {
                mode = 1; // Interactive
                
            }
            else if (uInput == 2) {
                mode = 2; // Silent
                
            }
            else {
                cout << "\n Invalid Mode\n\n";
            }
        }
    }

    void silent_message() {
        if (mode == 1) {
            cout << "Silent Mode\n";
            cout << "Simulation Starts...\n";
            return;
        }
        return;
    }

    
    void displayDay(int currentDay,
        LinkedQueue<request*>* requestsList,
        LinkedQueue<Mission*>* readyDiggingMissions,
        LinkedQueue<Mission*>* readyPolarMissions,
        RDY_NM* readyNormalMissions,
        LinkedQueue<Normal_Rovers*>* available_Normal_Rovers,
        LinkedQueue<Polar_Rovers*>* available_Polar_Rovers,
        LinkedQueue<Digging_Rovers*>* available_Digging_Rovers,
        LinkedQueue<Rescue_Rovers*>* available_Rescue_Rovers,
        OUT_missions* outMissions,
        priQueue<Mission*>* execMissions,
        priQueue<Mission*>* backMissions,
        ArrayStack<Mission*>* abortedMissions,
        LinkedQueue<Normal_Rovers*>* checkupNormalRovers,
        LinkedQueue<Polar_Rovers*>* checkupPolarRovers,
        LinkedQueue<Digging_Rovers*>* checkupDiggingRovers,
        LinkedQueue<Rescue_Rovers*>* checkupRescueRovers,
        ArrayStack<Mission*>* doneMissions) {
        if (mode != 1) {
            return;
        }
        cout << "           Current Day: " << currentDay << "\n";
        cout << "==============================================\n";

        cout << "\nPress ENTER to display this day's information...";
        cin.get();

        printRequestList(requestsList);        
        printReadyLists(readyNormalMissions, readyPolarMissions, readyDiggingMissions);        
        printAvailableRovers(available_Normal_Rovers, available_Polar_Rovers,available_Digging_Rovers, available_Rescue_Rovers);        
        printOutList(outMissions);        
        printExecList(execMissions);        
        printBackList(backMissions);        
        printAbortedList(abortedMissions);   
        printCheckupList(checkupNormalRovers, checkupPolarRovers,checkupDiggingRovers, checkupRescueRovers);
        printDoneList(doneMissions);

        cout << "==============================================\n\n";
    }

    void end_message() {
        cout << "\n==============================================\n";
           cout << "Simulation ends, Output file created\n";
       }

    void printRequestList(LinkedQueue<request*>* requestsList) {
        cout << "\n=============== Requests List ===============\n";
        int reqCount = requestsList->getCount();
        cout << reqCount << " requests remaining: ";

        if (reqCount == 0) {
            cout << "(No pending requests)\n";
            return;
        }

        
        LinkedQueue<request*> tempQueue;
        request* reqPtr = nullptr;
        int printed = 0;

        cout << "\n";
        while (requestsList->dequeue(reqPtr) && printed < 10) {
            if (New_Request* nrPtr = dynamic_cast<New_Request*>(reqPtr)) {
                cout << "[R," << nrPtr->getMissionType() << ","
                    << nrPtr->getRequestDay() << "," << nrPtr->getRequestID() << "] ";
            }
            else if (Abort_Request* arPtr = dynamic_cast<Abort_Request*>(reqPtr)) {
                cout << "[X," << arPtr->getRequestDay() << ","
                    << arPtr->getAbortedRequestID() << "] ";
            }
            tempQueue.enqueue(reqPtr);
            printed++;
        }

        
        while (requestsList->dequeue(reqPtr)) {
            tempQueue.enqueue(reqPtr);
        }

        
        while (tempQueue.dequeue(reqPtr)) {
            requestsList->enqueue(reqPtr);
        }

        if (reqCount > 10) {
            cout << "... and " << (reqCount - 10) << " more";
        }
        cout << "\n";
    }

   
    void printReadyLists(RDY_NM* readyNormalMissions,
        LinkedQueue<Mission*>* readyPolarMissions,
        LinkedQueue<Mission*>* readyDiggingMissions) {
        cout << "\n=============== Ready List(s) ===============\n";

        int totalReady = readyNormalMissions->getCount() +
            readyPolarMissions->getCount() +
            readyDiggingMissions->getCount();

        cout << totalReady << " Missions: ";

        if (totalReady == 0) {
            cout << "(No missions ready)\n";
            return;
        }

        cout << "\n";

        
        if (readyNormalMissions->getCount() > 0) {
            cout << "  NMs[" << readyNormalMissions->getCount() << "]: ";
            printMissionIDs(readyNormalMissions);
        }

        
        if (readyPolarMissions->getCount() > 0) {
            cout << "  PMs[" << readyPolarMissions->getCount() << "]: ";
            printMissionIDsFromQueue(readyPolarMissions);
        }

        
        if (readyDiggingMissions->getCount() > 0) {
            cout << "  DMs[" << readyDiggingMissions->getCount() << "]: ";
            printMissionIDsFromQueue(readyDiggingMissions);
        }
        cout << "\n";
    }

    
    void printMissionIDs(RDY_NM* missions) {
        LinkedQueue<Mission*> tempQueue;
        Mission* mPtr = nullptr;
        int count = 0;

        while (missions->dequeue(mPtr) && count < 10) {
            cout << mPtr->getID() << " ";
            tempQueue.enqueue(mPtr);
            count++;
        }

        int remaining = missions->getCount();
        while (missions->dequeue(mPtr)) {
            tempQueue.enqueue(mPtr);
        }

        while (tempQueue.dequeue(mPtr)) {
            missions->enqueue(mPtr);
        }

        if (remaining > 0) {
            cout << "... +" << remaining;
        }
        cout << "\n";
    }

 
    void printMissionIDsFromQueue(LinkedQueue<Mission*>* missions) {
        LinkedQueue<Mission*> tempQueue;
        Mission* mPtr = nullptr;
        int count = 0;

        while (missions->dequeue(mPtr) && count < 10) {
            cout << mPtr->getID() << " ";
            tempQueue.enqueue(mPtr);
            count++;
        }

        int remaining = missions->getCount();
        while (missions->dequeue(mPtr)) {
            tempQueue.enqueue(mPtr);
        }

        while (tempQueue.dequeue(mPtr)) {
            missions->enqueue(mPtr);
        }

        if (remaining > 0) {
            cout << "... +" << remaining;
        }
        cout << "\n";
    }

    
    void printAvailableRovers(LinkedQueue<Normal_Rovers*>* availNR,
        LinkedQueue<Polar_Rovers*>* availPR,
        LinkedQueue<Digging_Rovers*>* availDR,
        LinkedQueue<Rescue_Rovers*>* availRR) {
        cout << "\n=========== Available Rovers List(s) ===========\n";

        int totalAvail = availNR->getCount() + availPR->getCount() +
            availDR->getCount() + availRR->getCount();

        cout << totalAvail << " Available Rovers: ";

        if (totalAvail == 0) {
            return;
        }

        cout << "\n";

        if (availNR->getCount() > 0) {
            cout << "  NR[" << availNR->getCount() << "] ";
        }
        if (availPR->getCount() > 0) {
            cout << "  PR[" << availPR->getCount() << "] ";
        }
        if (availDR->getCount() > 0) {
            cout << "  DR[" << availDR->getCount() << "] ";
        }
        if (availRR->getCount() > 0) {
            cout << "  RR[" << availRR->getCount() << "] ";
        }
        cout << "\n";
    }

    
    void printOutList(OUT_missions* outMissions) {
        cout << "\n================= OUT List(s) =================\n";
        int count = outMissions->getCount();
        cout << count << " Missions/Rovers: ";

        if (count == 0) {
            return;
        }

        cout << "\n";
        printMissionRoverPairs(outMissions);
    }

    
    void printExecList(priQueue<Mission*>* execMissions) {
        cout << "\n================ EXEC List(s) =================\n";
        int count = execMissions->getCount();
        cout << count << " Missions/Rovers: ";

        if (count == 0) {
            return;
        }

        cout << "\n";
        printMissionRoverPairs(execMissions);
    }

    
    void printBackList(priQueue<Mission*>* backMissions) {
        cout << "\n================ BACK List(s) =================\n";
        int count = backMissions->getCount();
        cout << count << " Missions/Rovers: ";

        if (count == 0) {
            return;
        }

        cout << "\n";
        printMissionRoverPairs(backMissions);
    }

    
    void printMissionRoverPairs(priQueue<Mission*>* missions) {
        priQueue<Mission*> tempQueue;
        Mission* mPtr = nullptr;
        int pri;
        int count = 0;

        while (missions->dequeue(mPtr, pri) && count < 10) {
            cout << "  [" << mPtr->getID() << "/"
                << mPtr->getassignedRover()->getRoverID() << ","
                << mPtr->getEDY() << "days] ";
            tempQueue.enqueue(mPtr, pri);
            count++;
        }

        while (missions->dequeue(mPtr, pri)) {
            tempQueue.enqueue(mPtr, pri);
        }

        while (tempQueue.dequeue(mPtr, pri)) {
            missions->enqueue(mPtr, pri);
        }

        cout << "\n";
    }

    
    void printAbortedList(ArrayStack<Mission*>* abortedMissions) {
        cout << "\n============== Aborted List(s) ================\n";
        int count = abortedMissions->getCount();
        cout << count << " Missions: ";
    }

    
    void printCheckupList(LinkedQueue<Normal_Rovers*>* checkupNR,
        LinkedQueue<Polar_Rovers*>* checkupPR,
        LinkedQueue<Digging_Rovers*>* checkupDR,
        LinkedQueue<Rescue_Rovers*>* checkupRR) {
        cout << "\n============== Checkup List(s) ================\n";

        int totalCheckup = checkupNR->getCount() + checkupPR->getCount() +
            checkupDR->getCount() + checkupRR->getCount();

        cout << totalCheckup << " Rovers: ";

        if (totalCheckup == 0) {
            cout << "(No rovers in checkup)\n";
            return;
        }

        cout << "\n";

        if (checkupNR->getCount() > 0) {
            cout << "  NR[" << checkupNR->getCount() << "] ";
        }
        if (checkupPR->getCount() > 0) {
            cout << "  PR[" << checkupPR->getCount() << "] ";
        }
        if (checkupDR->getCount() > 0) {
            cout << "  DR[" << checkupDR->getCount() << "] ";
        }
        if (checkupRR->getCount() > 0) {
            cout << "  RR[" << checkupRR->getCount() << "] ";
        }
        cout << "\n";
    }

    void printDoneList(ArrayStack<Mission*>* doneMissions) {
        cout << "\n================ DONE List(s) =================\n";
        int count = doneMissions->getCount();
        cout << count << " Missions: ";

 
    }
};