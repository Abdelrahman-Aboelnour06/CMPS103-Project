#pragma once
#include <iostream>
#include "Mars_Station.h"
using namespace std;

class UI {
private:
    Mars_Station* station;
    int mode;

public:
    UI(){
        mode = -1;
        station = nullptr;
    }

    ~UI() {
        if (station) delete station;
    }

    void selectMode() {
        int uInput=-1;
        while (uInput == -1) {
            cout << "Select Simulation Mode:\n";
            cout << "1-Interactive Mode\n";
            cout << "2-Silent Mode\n";
            cin >> uInput;
            switch (uInput) {
            case 1 : 
                mode = 1;//Interactive
                break;
            case 2:
                mode = 2;//Silent
                break;
            default:
                cout << "Invalid Mode\n";
                break;
            }
        }
    }

    void Simulation() {
        station = new Mars_Station();
        station->FILE_LOADING("input.txt");
    }


  


    void displayDay(int currentDay,
        LinkedQueue<request*>* requestsList,
        LinkedQueue<Mission*>* readyDiggingMissions,
        LinkedQueue<Mission*>* readyPolarMissions,
        RDY_NM* readyNormalMissions,
        LinkedQueue<Normal_Rovers*> available_Normal_Rovers,
    LinkedQueue<Polar_Rovers*> available_Polar_Rovers,
    LinkedQueue<Digging_Rovers*> available_Digging_Rovers,
    LinkedQueue<Rescue_Rovers*> available_Rescue_Rovers,
        OUT_missions* outMissions,
        priQueue<Mission*>* execMissions,
        priQueue<Mission*>* backMissions,
        ArrayStack<Mission*>* abortedMissions,
        LinkedQueue<Rover*>* checkupRovers,
        ArrayStack<Mission*>* doneMissions) {

        cout << "Current Day: " << currentDay << endl;
        cout << "Press Any Key to print next day info\n";
        cin.get();
        //Print Request List
        cout << "=============== Request List =============== \n";
        cout << requestsList->getCount() << " requests remaining: ";
        requestsList->print();
        cout << "\n\n";

        // Ready Lists
        cout << "--- Ready List(s) ---\n";
        int Ready = readyNormalMissions->getCount() +
            readyPolarMissions->getCount() +
            readyDiggingMissions->getCount();
        cout << Ready << " Missions: ";

        if (!readyNormalMissions->isEmpty()) {
            cout << "NMs[";
            readyNormalMissions->print();
            cout << "] ";
        }

        if (!readyPolarMissions->isEmpty()) {
            cout << "PMs[";
            readyPolarMissions->print();
            cout << "] ";
        }

        if (!readyDiggingMissions->isEmpty()) {
            cout << "DMs[";
            readyDiggingMissions->print();
            cout << "]";
        }
        cout << "\n\n";

        // 3. Available Rovers
        cout << "=============== Available Rovers List(s) =============== \n";
        cout <<available_Digging_Rovers.getCount()+available_Normal_Rovers.getCount()+available_Polar_Rovers.getCount()+available_Rescue_Rovers.getCount()<< " Available Rovers: ";
        if (available_Normal_Rovers.getCount() != 0) {
            available_Normal_Rovers.print();
        }
         if (available_Polar_Rovers.getCount() != 0) {
            available_Polar_Rovers.print();
        }
         if (available_Digging_Rovers.getCount() != 0) {
            available_Digging_Rovers.print();
        }
         if (available_Rescue_Rovers.getCount() != 0) {
            available_Rescue_Rovers.print();
        }
        cout << "\n\n";

        cout << "=============== OUT List(s) =============== \n";
        cout << outMissions->getCount() << " Missions/Rovers: ";
        outMissions->print();
        cout << "\n\n";

        cout << "=============== EXEC List(s) =============== \n";
        cout << execMissions->getCount() << " Missions/Rovers: ";
        execMissions->print();
        cout << "\n\n";

        cout << "=============== BACK List(s) =============== \n";
        cout << backMissions->getCount() << " Missions/Rovers: ";
        backMissions->print();
        cout << "\n\n";

        cout << "=============== Aborted List(s) =============== \n";
        cout << abortedMissions->getCount() << " Missions: ";
        // Separate by mission type for display
        cout << "\n\n";

        cout << "=============== Checkup List(s) =============== \n";
        cout << checkupRovers->getCount() << " Rovers: ";
        // Print checkup rovers
        cout << "\n\n";

        cout << "--- DONE List(s) ---\n";
        cout << doneMissions->getCount() << " Missions: ";
        doneMissions->print();
        cout << "\n\n";


    }

    void end_message() {
        if (mode == 1) {
            //Interactive
            cout << "Simulation ends, Output file created\n";
        }
        if (mode == 2) {
            //silent
            cout << "Simulation ends, Output file created\n";
        }
    }
private:
    bool isSimulationComplete() {
        return station->getRequestsQueue()->isEmpty() &&
            station->getReadyNormalMissions()->isEmpty() &&
            station->getReadyDiggingMissions()->isEmpty() &&
            station->getReadyPolarMissions()->isEmpty() &&
            station->getOutMissions()->isEmpty() &&
            station->getExecMissions()->isEmpty() &&
            station->getBackMissions()->isEmpty();
    }
};