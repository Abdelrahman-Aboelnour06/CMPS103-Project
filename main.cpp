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
#include "UI.h"
using namespace std;

/*-----------------------------Omar Syed-----------------------------*/
void DATA_STRUCT_TESTING() {
	cout << "--Testing Queue--\n";
	cout << "--Creating a Queue to missions--\n";
	
	/*===================enqueue=========================*/
	LinkedQueue<Mission*> MISSION_QUEUE;
	cout << "--Testing isEmpty()--\n";
	MISSION_QUEUE.isEmpty() ? cout << "The MISSION_QUEUE is Empty\n" : cout << "MISSION_QUEUE is not empty\n";
	cout << "--Testing enqueue 12  missions--\n";
	Mission* Mptr=nullptr;
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
	cout << "The Front Element in queue is :\n ";
	cout << temp<<endl;
	/*===================Peek=========================*/

	/*===================Print=========================*/
	cout << "==Testing print()==\n";
	MISSION_QUEUE.print(MISSION_QUEUE.getCount());
	/*===================Print=========================*/
	cout << endl;
	/*===================Dequeue=========================*/
	cout << "--Testing Dequeue--\n";
	while (MISSION_QUEUE.dequeue(temp)) {
		cout << "Dequeued Element is  : ";
		cout << temp<<endl;
	}
	/*===================Dequeue=========================*/

	cout << "--Check IS Empty()--\n";
	MISSION_QUEUE.isEmpty() ? cout << "The MISSION_QUEUE is Empty\n" : cout << "MISSION_QUEUE is not empty\n";
	cout << "==Ending MISSION_QUEUE Testing==\n";

	

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
		DONE_MISSION_STACK.print(DONE_MISSION_STACK.getCount());
	/*===================Print Stack=========================*/

		/*===================Peek=========================*/
		cout << "==Testing Peek()==\n";
		DONE_MISSION_STACK.peek(Mptr);
		
		cout << Mptr<<endl;
		/*===================Peek=========================*/

		cout << "==Popping All Elements==\n";
		while (DONE_MISSION_STACK.pop(Mptr)) {
			cout << "==The Popped Element is : \n";
			cout << Mptr<<endl;
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
		MISSION_PRQUEUE.print(MISSION_PRQUEUE.getCount());
		cout << "==Testing Peek==\n";
		int c=1;
		MISSION_PRQUEUE.peek(temp, c);
		cout <<" Pri is : " << c <<" " << temp << endl;

		cout << "== Testing Dequeue == \n ";
		while (MISSION_PRQUEUE.dequeue(temp, c)) {
			cout << "Dequeued Element is : ";
			cout << temp << " Pri is : " << c << endl;
		}

		cout << "==Ending PriQUEUE testing==\n";
		delete temp;
	/*===================PriQueue=========================*/

}

int main() 
{

	Mars_Station* Mstation = new Mars_Station;

	
	UI ui;
	Mstation->FILE_LOADING("input_1000.txt");

	ui.selectMode();
	ui.silent_message();
	while (true)
	{
		
		ui.current_day_message(Mstation->get_current_day());

		Mstation->simulator();

		ui.displayDay(
			Mstation->get_current_day(),  
			Mstation->getRequestsQueue(),
			Mstation->getReadyDiggingMissions(),
			Mstation->getReadyPolarMissions(),  
			Mstation->getReadyNormalMissions(),
			Mstation->getAvailableNormalRovers(),
			Mstation->getAvailablePolarRovers(),
			Mstation->getAvailableDiggingRovers(),
			Mstation->getAvailableRescueRovers(),
			Mstation->getOutMissions(),
			Mstation->getExecMissions(),
			Mstation->getBackMissions(),
			Mstation->getAbortedMissions(),
			Mstation->getCheckupNormalRovers(),
			Mstation->getCheckupPolarRovers(),
			Mstation->getCheckupDiggingRovers(),
			Mstation->getCheckupRescueRovers(),
			Mstation->getDoneMissions()
		);

		
		if (Mstation->getRequestsQueue()->isEmpty() &&
			Mstation->getReadyNormalMissions()->isEmpty() &&
			Mstation->getReadyDiggingMissions()->isEmpty() &&
			Mstation->getReadyPolarMissions()->isEmpty() &&
			Mstation->getExecMissions()->isEmpty() &&
			Mstation->getBackMissions()->isEmpty() &&
			Mstation->getOutMissions()->isEmpty() &&
			Mstation->getCheckupDiggingRovers()->isEmpty() &&
			Mstation->getCheckupNormalRovers()->isEmpty() &&
			Mstation->getCheckupPolarRovers()->isEmpty()
			)
		{
			Mstation->generateOutputFile("output.txt");
			ui.end_message();
			break;
		}
	}

	delete Mstation;




	return 0;
}

/*-----------------------------Omar Syed-----------------------------*/