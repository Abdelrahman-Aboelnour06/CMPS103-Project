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

void readData(string fileName,int*roverCounts,int*roverSpeed,int* checkupDurations,int &checkupNum,LinkedQueue<Request*> requestQueue) {
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
		file >> type;
		int RDAY,ID,TLOC,DUR;
		file >> RDAY >> ID >> TLOC >> DUR;
		//cast the requestptr
		requestptr = new New_Request(ID, RDAY, TLOC, DUR, type);
		requestQueue.enqueue(requestptr);
	}
	else if (request == 'X') {
		int Xday;
		int id;
		file >> Xday >> id;

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

	/*int roverCount[3];
	int roverSpeed[3];
	int* checkupDurations;
	int chekupNum=0;
	LinkedQueue<Request*>requestQueue;
	readData("input.txt", roverCount, roverSpeed, checkupDurations, chekupNum, requestQueue);*/

	/*-----------------------------Omar Syed-----------------------------*/
	return 0;
}
