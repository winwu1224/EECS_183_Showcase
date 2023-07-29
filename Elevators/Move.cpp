/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Aiden Harris, Winston Wu, Gino Sessa, Audra Halcomb#>
 * <#aidenhar, winwu, gsessa, halcomb#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    int ASCII_ZERO = 48;
    if (commandString == ""){
        isPass = true;
    }
    else {
        isPass = false;
    }

    if (commandString.length() == 3) {
        isPickup = true;
        elevatorId = commandString.at(1);
        elevatorId = elevatorId - ASCII_ZERO;
    }
    else {
        isPickup = false;
    }

    if (commandString.length() == 1){
        if (commandString == "q" || commandString == "Q"){
            isSave = false;
            isQuit = true;
        }
        else if (commandString == "S" || commandString == "s"){
            isSave = true;
            isQuit = false;
        }
    }
    else {
        isSave = false;
        isQuit = false;
    }

    if (commandString.length() == 4) {
        elevatorId = commandString.at(1);
        elevatorId = elevatorId - ASCII_ZERO;
        targetFloor = commandString.at(3);
        targetFloor = targetFloor - ASCII_ZERO;
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    // set to false then write every situation which it can be true
    bool isValid = false;
    // first true criterion: if the three are valid
    if (isSave || isQuit || isPass) {
        isValid = true;
    }
    // next true criterion: if elevator is not currently servicing
    else if (isPickup) {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS) {
            if (!elevators[elevatorId].isServicing()) {
                isValid = true;
            }
        }
    }
    // last true criterion: if the target floor is different from the current floor
    else if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && targetFloor >= 0 && targetFloor < NUM_FLOORS) {
        if (!elevators[elevatorId].isServicing() && targetFloor != elevators[elevatorId].getCurrentFloor()) {
            isValid = true;
        }
    }
    return isValid;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    int ASCII_ZERO = 48;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    for (int i = 0; i < pickupList.length(); i++) {
        peopleToPickup[i] = int(pickupList.at(i)) - ASCII_ZERO;
        numPeopleToPickup++;
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel());
    }

    int distance = 0;
    int maxDistance = 0;
    for (int j = 0; j < pickupList.length(); j++) {
        distance = abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[j]).getTargetFloor());
        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }
    for (int k = 0; k < pickupList.length(); k++) {
        if (maxDistance == abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[k]).getTargetFloor())) {
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[k]).getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
