#include <iostream>
#include "ADT/ArrayStack.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"
#include "Request/Request.h"
#include "Request/New_Request.h"
#include "Request/Abort_Request.h"
#include "Rovers/Rover.h"
#include "Rovers/Digging_Rovers.h"
#include "Rovers/Normal_Rovers.h"
#include "Rovers/polar_Rovers.h"
#include <fstream>
using namespace std;

/*-----------------------------Omar Syed-----------------------------*/

void readData(string fileName, int* roverCounts, int* roverSpeed, int*& checkupDurations, int& checkupNum, LinkedQueue<REQUEST*>& requestQueue) {
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
	char request;
	while (requestNum--) {
		file >> request;
		REQUEST* requestptr = nullptr;
		if (request == 'R') {
			char type;
			int RDAY, ID, TLOC, DUR;
			file >> type >> RDAY >> ID >> TLOC >> DUR;
			//cast the requestptr
			requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
		}
		else if (request == 'X') {
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

/*-----------------------------Omar Syed-----------------------------*/

int main() {
	/*-----------------------------Omar Syed-----------------------------*/

	//Data Structures Testing at least 10 object



	//test file reading function
	int roverCount[3] = { 0,0,0 };
	int roverSpeed[3] = { 0 ,0,0 };
	int* checkupDurations = nullptr;
	int checkupNum = 0;
	LinkedQueue<REQUEST*> requestQueue;

	cout << "\n=== Testing File Reading ===" << endl;
	readData("input.txt", roverCount, roverSpeed, checkupDurations, checkupNum, requestQueue);


	/*-----------------------------Omar Syed-----------------------------*/
	while (!requestQueue.isEmpty()) {
		REQUEST* temp = nullptr;
		requestQueue.dequeue(temp);
		if (New_Request* n = dynamic_cast<New_Request*>(temp))
			cout << *n;
		else if (Abort_Request* a = dynamic_cast<Abort_Request*>(temp))
			cout << *a;

		delete temp;
	}
	return 0;
}
