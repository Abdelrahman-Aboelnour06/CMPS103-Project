#include <iostream>
#include "ADT/ArrayStack.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"
#include "Request/Requests.h"
#include "Request/New_Request.h"
#include "Rovers/Rover.h"
#include "Rovers/Digging_Rovers.h"
#include "Rovers/Normal_Rovers.h"
#include "Rovers/polar_Rovers.h"
#include "header.h"
#include <fstream>
using namespace std;

/*-----------------------------Omar Syed-----------------------------*/

void readData(string fileName,int*roverCounts,int*roverSpeed,int* &checkupDurations,int &checkupNum,LinkedQueue<Request*> &requestQueue) {
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
	while (requestNum--){
	file >> request;
	Request* requestptr = nullptr;
	if (request == 'R') {
		char type;
		int RDAY,ID,TLOC,DUR;
		file >>type >>RDAY >> ID >> TLOC >> DUR;
		//cast the requestptr
		requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
	}
	else if (request == 'X') {
		int Xday;
		int id;
		file >> Xday >> id;
	    requestptr = new Abort_Request(Xday,id);
	}
		//store in the request queue
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
	int roverSpeed[3] = { 0 ,0,0};
	int* checkupDurations = nullptr;
	int checkupNum = 0;
	LinkedQueue<Request*> requestQueue;

	cout << "\n=== Testing File Reading ===" << endl;
	readData("input.txt", roverCount, roverSpeed, checkupDurations, checkupNum, requestQueue);

	// TEST OUTPUTS DIRECTLY
	cout << "\n--- Rover Counts ---" << endl;
	for (int i = 0; i < 3; i++)
		cout << "Rover Count [" << i << "] = " << roverCount[i] << endl;

	cout << "\n--- Rover Speeds ---" << endl;
	for (int i = 0; i < 3; i++)
		cout << "Rover Speed [" << i << "] = " << roverSpeed[i] << endl;

	cout << "\n--- Checkup Durations ---" << endl;
	cout << "CheckupNum = " << checkupNum << endl;
	for (int i = 0; i < checkupNum; i++)
		cout << "Duration[" << i << "] = " << checkupDurations[i] << endl;

	cout << "\n--- Requests Queue ---" << endl;
	Request* temp;
	int count = 1;
	while (requestQueue.dequeue(temp)) {
		cout << "Request " << count++ << ": ";
		cout << temp;
		cout << endl;
		delete temp; // free memory
	}

	delete[] checkupDurations;

	cout << "\n=== File Reading Test Complete ===" << endl;

	/*-----------------------------Omar Syed-----------------------------*/
	return 0;
}
