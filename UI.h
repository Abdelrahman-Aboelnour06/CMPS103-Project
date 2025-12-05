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
        cout << "Current Day: " << currentDay << "\n";
        cout << "==============================================\n";

        cout << "\nPress ENTER to display this day's information...";
        cin.get();

        cout << "==============================================\n\n";
    }

    void end_message() {
        cout << "\n==============================================\n";
           cout << "Simulation ends, Output file created\n";
       }

    

   
   
    

    
    

    
    
};