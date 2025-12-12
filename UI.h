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
        if (mode == 2) {
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
        cout << "Current Day: " << currentDay << "\n";
        cin.get();
        cout << "\n================== Requests List(s) ================== \n";
        if (requestsList->getCount() > 10) {
            cout << requestsList->getCount() << " requests remaining: ";
            requestsList->print(10);
            cout << "... and so on\n";
        }
        else {
            cout << requestsList->getCount() << " requests remaining: ";
            requestsList->print(requestsList->getCount());
            cout << endl;
        }

        cout << "\n================== Ready List(s) ================== \n";
        cout << readyDiggingMissions->getCount() + readyNormalMissions->getCount() + readyPolarMissions->getCount() << " Missions: ";
        if (readyNormalMissions->getCount() > 0) {
            cout << "NMs[";
            readyNormalMissions->print(readyNormalMissions->getCount());
            cout << "]";
        }
        if (readyPolarMissions->getCount() > 0) {
            cout << "PMs[";
            readyPolarMissions->print(readyPolarMissions->getCount());
            cout << "]";
        }
        if (readyDiggingMissions->getCount() > 0) {
            cout << "DMs[";
            readyDiggingMissions->print(readyDiggingMissions->getCount());
            cout << "]";
        }
        cout << endl;
        cout << "\n================== Available Rovers List(s) ================== \n";
        cout << available_Digging_Rovers->getCount() + available_Normal_Rovers->getCount() + available_Polar_Rovers->getCount() << " Available Rovers: ";
        if (available_Normal_Rovers->getCount() > 0) {
            cout << "NR[";
            available_Normal_Rovers->print(available_Normal_Rovers->getCount());
            cout << "] ";
        }
        
        if (available_Polar_Rovers->getCount() > 0) {
            cout << "PR[";
            available_Polar_Rovers->print(available_Polar_Rovers->getCount());
            cout << "] ";
        }
        
        if (available_Digging_Rovers->getCount() > 0) {
            cout << "DR[";
            available_Digging_Rovers->print(available_Digging_Rovers->getCount());
            cout << "] ";
        }
        cout << endl;
        cout << "\n================== Out List(s) ================== \n";
        cout << outMissions->getCount() << " Missions/Rovers: ";
        outMissions->print(outMissions->getCount());
        cout << endl;
        cout << "\n================== Exec List(s) ================== \n";
        cout << execMissions->getCount() << " Missions/Rovers: ";

        priNode<Mission*>* curr = execMissions->getHead();
        int pri = 0;

        while (curr != nullptr) {
            Mission* m = curr->getItem(pri);

            cout << "["
                << m->getID() << "/"
                << m->get_assigned_rover_id() << ", "
                << m->get_remaining_day() << "days] ";

            curr = curr->getNext();
        }

        cout << endl;
        cout << "\n================== Back List(s) ================== \n";
        cout << backMissions->getCount() << " Missions/Rovers: ";

        priNode<Mission*>* curr2 = backMissions->getHead();
        int pri2 = 0;

        while (curr2 != nullptr) {
            Mission* m = curr2->getItem(pri2);

            cout << "["
                << m->getID() << "/"
                << m->get_assigned_rover_id() << ", "
                << m->get_remaining_day() << "days] ";

            curr2 = curr2->getNext();
        }

        cout << endl;
        cout << "\n================== Aborted List(s) ================== \n";
        cout << abortedMissions->getCount() << " Missions: ";
        if(abortedMissions->getCount()>0){
        cout << "[";
        abortedMissions->print(abortedMissions->getCount());
        cout << "]";
        cout << endl;
        }
        cout << endl;
        cout << "\n================== Checkup List(s) ================== \n";
        cout << checkupDiggingRovers->getCount() + checkupNormalRovers->getCount() + checkupPolarRovers->getCount()<<" Rovers: ";
        if (checkupDiggingRovers->getCount() + checkupNormalRovers->getCount() + checkupPolarRovers->getCount()>0) {
            cout << "[";
            if (checkupDiggingRovers->getCount() > 0)
                checkupDiggingRovers->print(checkupDiggingRovers->getCount());
            if (checkupNormalRovers->getCount() > 0)
                checkupNormalRovers->print(checkupNormalRovers->getCount());
            if (checkupPolarRovers->getCount() > 0)
                checkupPolarRovers->print(checkupPolarRovers->getCount());
            cout << "]";
        }
        cout << endl;
        cout << "\n================== Done List(s) ================== \n";
        cout << doneMissions->getCount() << " Missions: ";
        if (doneMissions->getCount() > 0) {
            cout << "[";
            doneMissions->print(doneMissions->getCount());
            cout << "]";
        }
        cout << endl;
        cout << "\n==================================================================\n";

    }

    void end_message() {
        cout << "\n==============================================\n";
           cout << "Simulation ends, Output file created\n";
       }

};