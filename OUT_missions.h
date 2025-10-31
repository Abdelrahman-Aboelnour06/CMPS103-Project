#pragma once
#include <iostream>
#include "Mission/Mission.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"

using namespace std;

//"a class derived from PriQueue 
//class OUT_missions : public PriQueue<mission*>
//{  //add ""AbortMission(ID)""  function   }     "
//
//"- PriQueue: Missions leave this list according to time to reach target loction
//- Derived: to add AbortMission(ID) that removes the mission form the list and returns a pointer to it"

class OUT_missions : public priQueue<Mission*> {
public:
	Mission* AbortMission(int ID) {
		if (isEmpty()) {
			return nullptr; // Queue is empty
		}
		priQueue<Mission*> tempQueue;
		Mission* abortedMission = nullptr;
		Mission* currentMission = nullptr;
		int pri; // to hold priority
		while (this->dequeue(currentMission, pri)) {
			if (currentMission != nullptr && currentMission->getID() == ID && abortedMission == nullptr) {
				abortedMission = currentMission; // Found the mission to abort
			}
			else {
				tempQueue.enqueue(currentMission, pri); // Keep the mission in the temp queue
			}
		}
		while (tempQueue.dequeue(currentMission, pri)) {
			this->enqueue(currentMission, pri); // Restore missions back to the original queue
		}
		return abortedMission; // Return the aborted mission or nullptr if not found
	}
};