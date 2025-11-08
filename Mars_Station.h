//********************************************abdelrahman Tarek    ************************************** */

#pragma once
#include "header.h"
#include "Request/Request.h"
#include <fstream>
#include <iostream>
#include "RDY_NM.h"
#include "OUT_missions.h"
#include <cstdlib>
#include <ctime>


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
    ~Mars_Station() {}
    void assigningMissionsToRovers() {
        bool isPRsEmpty = available_Polar_Rovers.isEmpty();
        bool isNRsEmpty = available_Normal_Rovers.isEmpty();
        bool isDRsEmpty = available_Digging_Rovers.isEmpty();
		if (isPRsEmpty && isNRsEmpty && isDRsEmpty) {
            return;
		}
        if (!Ready_Polar_Missions.isEmpty()) {
            assignPMs();
        }
        isPRsEmpty = available_Polar_Rovers.isEmpty();
        isNRsEmpty = available_Normal_Rovers.isEmpty();
        isDRsEmpty = available_Digging_Rovers.isEmpty();
        if (isPRsEmpty && isNRsEmpty && isDRsEmpty) {
            return;
        }
		if (!Ready_Digging_Missions.isEmpty()) {
			assignDMs();
		}
		isPRsEmpty = available_Polar_Rovers.isEmpty();
		isNRsEmpty = available_Normal_Rovers.isEmpty();
		isDRsEmpty = available_Digging_Rovers.isEmpty();
		if (isPRsEmpty && isNRsEmpty && isDRsEmpty) {
			return;
		}
		if (!Ready_Normal_Missions.isEmpty()) {
			assignNMs();
		}
    }
    void assignPMs() {
        while (!Ready_Polar_Missions.isEmpty()) {
            Mission* missionPtr = nullptr;
            if (!available_Polar_Rovers.isEmpty()) {
                Ready_Polar_Missions.dequeue(missionPtr);
                Polar_Rovers* roverPtr;
                available_Polar_Rovers.dequeue(roverPtr);
                missionPtr->setRover(roverPtr);
            }
			else if (!available_Normal_Rovers.isEmpty()) {
				Ready_Polar_Missions.dequeue(missionPtr);
				Normal_Rovers* roverPtr;
				available_Normal_Rovers.dequeue(roverPtr);
				missionPtr->setRover(roverPtr);
			}
			else if (!available_Digging_Rovers.isEmpty()) {
				Ready_Polar_Missions.dequeue(missionPtr);
				Digging_Rovers* roverPtr;
				available_Digging_Rovers.dequeue(roverPtr);
				missionPtr->setRover(roverPtr);
			}
			else {
				// No available rovers
				break;
			}
			//set other mission parameters
			missionPtr->setLDY(current_day);
			missionPtr->setWDYs();
			missionPtr->setJDYs();
			missionPtr->setEDY();
			missionPtr->setTDYs();
			missionPtr->setFDY();
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
			missionPtr->setLDY(current_day);
			missionPtr->setWDYs();
			missionPtr->setJDYs();
			missionPtr->setEDY();
			missionPtr->setTDYs();
			missionPtr->setFDY();
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
			missionPtr->setLDY(current_day);
			missionPtr->setWDYs();
			missionPtr->setJDYs();
			missionPtr->setEDY();
			missionPtr->setTDYs();
			missionPtr->setFDY();
			//add to ÒUT missions
			Out_Missions.enqueue(missionPtr, missionPtr->getEDY());
        }
    }


    void ChecknewRequests()
    {
        request* temp = nullptr;
        while(!requests.isEmpty() && requests.peek(temp) && temp->getRequestDay() == current_day)
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
        }
        if (rand() % 100 < 20)
        {
            Rover* donerover = nullptr;
            donerover = backmission->getassignedRover();
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
            else if(!Checkup_Digging_Rovers.isEmpty())
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
    void printall()
    {
		cout << "Current Day: " << current_day << endl;
		cout << "===============Requests Lists===============" << endl;
    }
    void simulator()
    {
        ChecknewRequests();
        moveroversfromcheckuptoavailable();
        moveexecutedtoback();
        moveouttoexecuted();
        incrementDay();
    }
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
    /*======================================Omar Syed======================================*/
    void SET_AVAIL_PR(Polar_Rovers*&Avail_PR) {
        available_Polar_Rovers.enqueue(Avail_PR);
        POLAR_ROVER_SPEED = Avail_PR->getSpeed();
    }

    void SET_AVAIL_DR(Digging_Rovers*&Avail_DR) {
        available_Digging_Rovers.enqueue(Avail_DR);
        DIGGING_ROVER_SPEED = Avail_DR->getSpeed();
    }

    void SET_AVAIL_NR(Normal_Rovers*&Avail_NR) {
        available_Normal_Rovers.enqueue(Avail_NR);
        NORMAL_ROVER_SPEED = Avail_NR->getSpeed();
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
    /*void SET_RDM(Mission*DM) {
        Ready_Digging_Missions.enqueue(DM);
    }
    void SET_RPM(Mission*PM) {
        Ready_Digging_Missions.enqueue(PM);
    }
    void SET_RNM(Mission*NM) {
        Ready_Digging_Missions.enqueue(NM);
    }*/

    /*======================================Omar Syed======================================*/
}; 
