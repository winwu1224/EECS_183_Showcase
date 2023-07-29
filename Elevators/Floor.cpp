/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Aiden Harris, Winston Wu, Gino Sessa, Audra Halcomb#>
 * <#aidenhar, winwu, gsessa, halcomb#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include <algorithm>
using namespace std;

int Floor::tick(int currentTime) {
    int numExploded = 0;
	int remove[MAX_PEOPLE_PER_FLOOR];
	for (int i = 0; i < numPeople; i++) {
		if (people[i].tick(currentTime)) {
			remove[numExploded] = i;
			numExploded++;
		}
	}
	removePeople(remove, numExploded);
	return numExploded;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople + 1 <= MAX_PEOPLE_PER_FLOOR){
		people[numPeople] = newPerson;
		numPeople++;
		if (request > 0){
			hasUpRequest = true;
		}
		else if (request < 0){
			hasDownRequest = true;
		}
	}
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    sort(indicesToRemove, indicesToRemove + numPeopleToRemove);
    // run through all the people on the floor
    for (int i = numPeopleToRemove - 1; i >= 0; i--) {
        // create the instance where a specific person is to be removed
        // the reason for creating this instance is to eventually force it to end the later for loop
        int indexToRemove = indicesToRemove[i];
        //remove instance and shift array appropriately
        for (int j = indexToRemove; j < numPeople - 1; j++) {
                people[j] = people[j + 1];
        }
        numPeople--;
    }
    resetRequests();
    return;
}

void Floor::resetRequests() {
    hasUpRequest = false;
	hasDownRequest = false;
	for (int i = 0; i < numPeople; i++) {
		if (people[i].getCurrentFloor() > people[i].getTargetFloor()) {
			hasDownRequest = true;
		}
		else if (people[i].getCurrentFloor() < people[i].getTargetFloor()) {
			hasUpRequest = true;
		}
	}
	return;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
