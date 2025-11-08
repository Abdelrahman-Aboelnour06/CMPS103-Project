#include <iostream>
#include "ADT/ArrayStack.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"
#include "Request/Request.h"
#include "Request/New_Request.h"
#include "Request/Abort_Request.h"
#include "Rovers/Digging_Rovers.h"
#include "Rovers/Normal_Rovers.h"
#include "Rovers/polar_Rovers.h"
#include "Rovers/Rover.h"
#include <fstream>
using namespace std;

/*-----------------------------Omar Syed-----------------------------*/

void FILE_LOADING(string fileName, int* roverCounts, int* roverSpeed, int*& checkupDurations, int& checkupNum, LinkedQueue<request*>& requestQueue) {
	//read data from a file and store it into data structures
	//open the file
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	//read data from the file
	int i = 0;

	while (i < 3) {
		file >> roverCounts[i];
		i++;
	}
	i = 0;
	while (i < 3) {
		file >> roverSpeed[i];
		i++;
	}
	file >> checkupNum;
	checkupDurations = new int[checkupNum];
	i = 0;
	while (i < checkupNum)
	{
		file >> checkupDurations[i];
		i++;

	}
	int requestNum;
	file >> requestNum;
	char requestType;

	while (requestNum--) {
		file >> requestType;

		request* requestptr = nullptr;

		if (requestType == 'R') {
			char type;
			int RDAY, ID, TLOC, DUR;
			file >> type >> RDAY >> ID >> TLOC >> DUR;
			//cast the requestptr
			requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
		}
		else if (requestType == 'X') {
			int Xday;
			int id;
			file >> Xday >> id;
			requestptr = new Abort_Request(Xday, id);
		}
		//store in the request queue
		if (requestptr)
			requestQueue.enqueue(requestptr);
	}
	file.close();

}

void DATA_STRUCT_TESTING() {
	cout << "--Testing Queue--\n";
	cout << "--Creating a Queue to missions--\n";
	
	/*===================enqueue=========================*/
	LinkedQueue<Mission*> MISSION_QUEUE;
	cout << "--Testing isEmpty()--\n";
	MISSION_QUEUE.isEmpty() ? cout << "The MISSION_QUEUE is Empty\n" : cout << "MISSION_QUEUE is not empty\n";
	cout << "--Testing enqueue 12  missions--\n";
	Mission* Mptr;
	for (int i = 0; i < 12; i++) {
		if (i % 3 == 0) {
			Mptr = new Mission(i, 2 * i, 4 * i, 'D',3*i);
		}
		else if (i % 3 == 1) {
			Mptr = new Mission(i, 2* i, 4 * i, 'P',3*i);
		}
		else {
			Mptr = new Mission(i, 2 * i, 4 * i, 'N', 3 * i);
		}
		cout << "--Enqueue mission no. " << i << " \n";
		MISSION_QUEUE.enqueue(Mptr);
	}

	/*===================enqueue=========================*/

	/*===================Peek=========================*/
	cout << "--testing Peek()--\n";
	Mission *temp;
	MISSION_QUEUE.peek(temp);
	Mission temp_obj = *temp;
	cout << "The Front Element in queue is :\n ";
	cout << temp_obj;
	/*===================Peek=========================*/

	/*===================Print=========================*/
	cout << "==Testing print()==\n";
	MISSION_QUEUE.print();
	/*===================Print=========================*/

	/*===================Dequeue=========================*/
	cout << "--Testing Dequeue--\n";
	while (MISSION_QUEUE.dequeue(temp)) {
		temp_obj = *temp;
		cout << "Dequeued Element is  : ";
		cout << temp_obj;
	}
	/*===================Dequeue=========================*/

	cout << "--Check IS Empty()--\n";
	MISSION_QUEUE.isEmpty() ? cout << "The MISSION_QUEUE is Empty\n" : cout << "MISSION_QUEUE is not empty\n";
	cout << "==Ending MISSION_QUEUE Testing==\n";

	/*===================Destructor=========================*/
	MISSION_QUEUE.~LinkedQueue();
	/*===================Destructor=========================*/

	/*===================Stack=========================*/
	
	ArrayStack<Mission*>DONE_MISSION_STACK;
	/*===================PUSH=========================*/
	cout << "--Testing isEmpty()--\n";
	DONE_MISSION_STACK.isEmpty() ? cout << "The DONE_MISSION_STACK is Empty\n" : cout << "DONE_MISSION_STACK is not empty\n";
	cout << "--Testing Pushing 12 missions--\n";
	for (int i = 0; i < 12; i++) {
		if (i % 3 == 0) {
			Mptr = new Mission(i, 2 * i, 4 * i, 'D', 3 * i);
		}
		else if(i% 3 == 1){
			Mptr = new Mission(i, 2 * i, 4 * i, 'P', 3 * i);
		}
		else {
			Mptr = new Mission(i, 2 * i, 4 * i, 'N', 3 * i);
		}
		cout << "--Pushing mission no. " << i << " \n";
		DONE_MISSION_STACK.push(Mptr);
	}
	cout << "==Testing IS empty()==\n";
	DONE_MISSION_STACK.isEmpty() ? cout << "The Stack IS Empty \n" : cout << "The Stack IS NOt Empty\n";

	/*===================Print Stack=========================*/
	cout << "==Testing Print()==\n";
		DONE_MISSION_STACK.print();
	/*===================Print Stack=========================*/

		/*===================Peek=========================*/
		cout << "==Testing Peek()==\n";
		DONE_MISSION_STACK.peek(Mptr);
		temp_obj = *Mptr;
		cout << temp_obj;
		/*===================Peek=========================*/

		cout << "==Popping All Elements==\n";
		while (DONE_MISSION_STACK.pop(Mptr)) {
			cout << "==The Popped Element is : \n";
			temp_obj = *Mptr;
			cout << temp_obj;
		}

		cout << "== Ending Stack Testing ==\n";

	/*===================Stack=========================*/

	/*===================PriQueue=========================*/
		cout << "== Testing PriQueue == \n";
		priQueue<Mission*>  MISSION_PRQUEUE;
		cout << "Testing IS empty\n";
		MISSION_PRQUEUE.isEmpty() ? cout << "==MISSION_PriQUEUE is empty==\n" : cout << "==MISSION_PriQUEUE is not empty==\n";
		for (int i = 0; i < 12; i++) {
			if (i % 3 == 0) {
				Mptr = new Mission(i, 2 * i, 4 * i, 'D', 3 * i);
			}
			else if (i % 3 == 1) {
				Mptr = new Mission(i, 2 * i, 4 * i, 'P', 3 * i);
			}
			else {
				Mptr = new Mission(i, 2 * i, 4 * i, 'N', 3 * i);
			}
			cout << "--Enqueue mission no. " << i << " \n";
			MISSION_PRQUEUE.enqueue(Mptr,i%6);
		}
		cout << "Testing IS empty\n";
		MISSION_PRQUEUE.isEmpty() ? cout << "==MISSION_PriQUEUE is empty==\n" : cout << "==MISSION_PriQUEUE is not empty==\n";
		cout << "Printing PRIQUEUE elements\n";
		MISSION_PRQUEUE.print();
		cout << "==Testing Peek==\n";
		int c=1;
		MISSION_PRQUEUE.peek(temp, c);
		temp_obj = *temp;
		cout <<" Pri is : " << c <<" " << temp_obj << endl;

		cout << "== Testing Dequeue == \n ";
		while (MISSION_PRQUEUE.dequeue(temp, c)) {
			temp_obj = *temp;
			cout << "Dequeued Element is : ";
			cout << temp_obj << " Pri is : " << c << endl;
		}

		cout << "==Ending PriQUEUE testing==\n";
		
	/*===================PriQueue=========================*/

}

void SIMULATOR_FUN() {
	
}

void FILE_LOADING(string fileName,Mars_Station*MSTATION) {
	//read data from a file and store it into data structures
	//open the file
	int roverCounts[3] = { 0,0,0 };
	int roverSpeed[3] = { 0 ,0,0 };
	int* checkupDurations = nullptr;
	int checkupNum = 0;
	LinkedQueue<Polar_Rovers*>Avail_PR;
	LinkedQueue<Digging_Rovers*>Avail_DR;
	LinkedQueue<Normal_Rovers*>Avail_NR;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	//read data from the file
	int i = 0;

	while (i < 3) {
		file >> roverCounts[i];
		i++;
	}
	i = 0;
	
	while (i < 3) {
		file >> roverSpeed[i];
		i++;
	}
	file >> checkupNum;
	checkupDurations = new int[checkupNum];
	i = 0;
	while (i < checkupNum)
	{
		file >> checkupDurations[i];
		i++;

	}
	Digging_Rovers* nDptr=nullptr;
	Polar_Rovers* nPptr=nullptr;
	Normal_Rovers* nNptr=nullptr;
	for (int j = 0; j < roverCounts[0]; j++) {
		nDptr = new Digging_Rovers(roverSpeed[0], checkupNum, checkupDurations[0]);
		Avail_DR.enqueue(nDptr);
	}
	for (int j = 0; j < roverCounts[1]; j++) {
		nPptr = new Polar_Rovers(roverSpeed[1], checkupNum, checkupDurations[1]);
		Avail_PR.enqueue(nPptr);
	}
	for (int j = 0; j < roverCounts[2]; j++) {
		nNptr = new Normal_Rovers(roverSpeed[2], checkupNum, checkupDurations[2]);
		Avail_NR.enqueue(nNptr);
	}
	int requestNum;
	file >> requestNum;
	char requestType;

	while (requestNum--) {
		file >> requestType;

		request* requestptr = nullptr;

		if (requestType == 'R') {
			char type;
			int RDAY, ID, TLOC, DUR;
			file >> type >> RDAY >> ID >> TLOC >> DUR;
			//cast the requestptr
			requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
		}
		else if (requestType == 'X') {
			int Xday;
			int id;
			file >> Xday >> id;
			requestptr = new Abort_Request(Xday, id);
		}
		//store in the request queue in Mars Station
		if (requestptr)
			MSTATION->getRequestsQueue().enqueue(requestptr);
	}
	file.close();

}


/*-----------------------------Omar Syed-----------------------------*/

int main() {
	/*-----------------------------Omar Syed-----------------------------*/

	//Data Structures Testing at least 10 object

	DATA_STRUCT_TESTING();

	//test file reading function
	int roverCount[3] = { 0,0,0 };
	int roverSpeed[3] = { 0 ,0,0 };
	int* checkupDurations = nullptr;
	int checkupNum = 0;
	LinkedQueue<request*> requestQueue;
	cout << "\n=== Testing File Reading ===" << endl;
	FILE_LOADING("input.txt", roverCount, roverSpeed, checkupDurations, checkupNum, requestQueue);
	while (!requestQueue.isEmpty()) {
		request* temp = nullptr;
		requestQueue.dequeue(temp);
		if (New_Request* n = dynamic_cast<New_Request*>(temp))
			cout << *n;
		else if (Abort_Request* a = dynamic_cast<Abort_Request*>(temp))
			cout << *a;

		delete temp;
	}

	/*-----------------------------Omar Syed-----------------------------*/
	return 0;
}
