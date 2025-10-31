#include <iostream>
#include "ADT/ArrayStack.h"
#include "ADT/LinkedQueue.h"
#include "ADT/priQueue.h"
#include "header.h"
#include <fstream>

using namespace std;

/*-----------------------------Omar Syed-----------------------------*/

void readData(string fileName,int*roverCounts,int*roverSpeed,int* checkupDurations,int checkupNum,LinkedQueue<request*> requestQueue) {
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

	int checkupNum;
	file >> checkupNum;
	int* checkupDurations = new int[checkupNum];
	i = 0;
	while (i < checkupNum)
	{
		file >> checkupDurations[i];
		i++;

	}
	int requestNum;
	file >> requestNum;
	char request;
	while (file.eof() == false){
	file >> request;
	if (request == 'R') {
		char type;
		file >> type;
		int RDAY,ID,TLOC,DUR;
		file >> RDAY >> ID >> TLOC >> DUR;
	}
	else if (request == 'X') {
		int Xday;
		int id;
		file >> Xday >> id;

	}
		//store in the request queue
	}
	file.close();

}

/*-----------------------------Omar Syed-----------------------------*/

int main() {
	//test file reading function

	return 0;
}
