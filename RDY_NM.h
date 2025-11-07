// Created by Kirolos Ashraf
#include <iostream>
#include "ADT/LinkedQueue.h"
#include "Mission/Mission.h"
using namespace std;

//a class derived from Queue
//class RDY_NM : public LinkedQueue<mission*>
//{  //add "AbortMission(ID)"  function   }  

//  Queue: The normal operation of the list is FCFS (by RDY day)
//-Derived: to add AbortMission(ID) that removes the mission form the list and returns a pointer to it

class RDY_NM : public LinkedQueue<Mission*> {
public:
//	Mission* AbortMission(int ID) {
//		if (isEmpty()) {
//			return nullptr; // Queue is empty
//		}
//		LinkedQueue<Mission*> tempQueue;
//		Mission* abortedMission = nullptr;
//		Mission* currentMission = nullptr;
//
//		while (this->dequeue(currentMission)) {
//			if (currentMission != nullptr && currentMission->getID() == ID && abortedMission == nullptr) {
//				abortedMission = currentMission; // Found the mission to abort
//			}
//			else {
//				tempQueue.enqueue(currentMission); // Keep the mission in the temp queue
//			}
//		}
//
//		while (tempQueue.dequeue(currentMission)) {
//			this->enqueue(currentMission); // Restore missions back to the original queue
//		}
//		return abortedMission; // Return the aborted mission or nullptr if not found
//	}
	Mission* AbortMission(int ID) {
		if (isEmpty()) {
			return nullptr; // Queue is empty
		}
		Node<Mission*>* current = frontPtr;
		Node<Mission*>* previous = nullptr;
		while (current != nullptr) {
			Mission* currentMission = current->getItem();
			if (currentMission != nullptr && currentMission->getID() == ID) {
				// Found the mission to abort
				if (previous == nullptr) {
					// The mission to abort is at the front
					frontPtr = current->getNext();
				}
				else {
					previous->setNext(current->getNext());
				}
				if (current == backPtr) {
					backPtr = previous; // Update backPtr if needed
				}
				Mission* abortedMission = currentMission;
				delete current; // Free the memory of the node
				return abortedMission; // Return the aborted mission
			}
			previous = current;
			current = current->getNext();
		}
		return nullptr; // Mission with the given ID not found
	}
};
