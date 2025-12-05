// Created by Kirolos Ashraf
#ifndef OUT_MISSIONS_H
#define OUT_MISSIONS_H
#pragma once
#include <iostream>
#include "Mission/Mission.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"

using namespace std;

//class OUT_missions : public priQueue<Mission*> {
//public:
//	Mission* AbortMission(int ID) {
//		if (isEmpty()) {
//			return nullptr; // Queue is empty
//		}
//		priQueue<Mission*> tempQueue;
//		Mission* abortedMission = nullptr;
//		Mission* currentMission = nullptr;
//		int pri; // to hold priority
//		while (this->dequeue(currentMission, pri)) {
//			if (currentMission != nullptr && currentMission->getID() == ID && abortedMission == nullptr) {
//				abortedMission = currentMission; // Found the mission to abort
//			}
//			else {
//				tempQueue.enqueue(currentMission, pri); // Keep the mission in the temp queue
//			}
//		}
//		while (tempQueue.dequeue(currentMission, pri)) {
//			this->enqueue(currentMission, pri); // Restore missions back to the original queue
//		}
//		return abortedMission; // Return the aborted mission or nullptr if not found
//	}
//};

class OUT_missions : public priQueue<Mission*> {
public:
	Mission* AbortMission(int ID) {
		if (isEmpty()) {
			return nullptr; // Queue is empty
		}
		priNode<Mission*>* current = head;
		priNode<Mission*>* previous = nullptr;
		int pri; // to hold priority
		while (current != nullptr) {
			Mission* currentMission = current->getItem(pri);

			if (currentMission != nullptr && currentMission->getMissionType() == 'N' && currentMission->getID() == ID) {
				// Found the mission to abort
				if (previous == nullptr) {
					// The mission to abort is at the head
					head = current->getNext();
				}
				else {
					previous->setNext(current->getNext());
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

	int get_mission_id() const{
		if (isEmpty()) return -1;
		int pri;
		return head->getItem(pri)->getID();
	}

	
	int get_assigned_rover_id()const {
		if (isEmpty()) return -1;
		int pri;
		return head->getItem(pri)->get_assigned_rover_id();
	}
	int get_remaining_day()const {
		if (isEmpty()) return -1;
		int pri;
		return head->getItem(pri)->get_remaining_day();
	}

	void print(int count) const {
		priNode<Mission*>* current = head;
		int printed = 0;
		int pri;

		while (current != nullptr && printed < count) {
			Mission* m = current->getItem(pri);

			cout << "["
				<< m->getID() << "/"
				<< m->get_assigned_rover_id() << ", "
				<< m->get_remaining_day() << "days] ";

			current = current->getNext();
			printed++;
		}
	}

};
//
//std::ostream& operator<<(std::ostream& output, const OUT_missions* m) {
//	output << m->get_mission_id() << "/" << m->get_assigned_rover_id()<<"/"<<m->get_remaining_day()<<"days";
//	return output;
//}
#endif