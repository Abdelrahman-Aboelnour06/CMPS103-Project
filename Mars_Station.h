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
    Mars_Station() : current_day(0) {}
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





};
