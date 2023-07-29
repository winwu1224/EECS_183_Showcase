/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core


string getAIMoveString(const BuildingState& buildingState) {
    string moveString = "";
    if (buildingState.elevators[0].isServicing && 
        buildingState.elevators[1].isServicing && 
        buildingState.elevators[2].isServicing) {
        return "";
    }

    // if need elevator to pick up people
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        int curFloor = buildingState.elevators[i].currentFloor;
        if (!buildingState.elevators[i].isServicing && buildingState.floors[curFloor].numPeople > 0) {
            char elevatorToPickUp = '0' + i;
            moveString = 'e';
            moveString += elevatorToPickUp;
            moveString += 'p';
            return moveString;
        }
    }

    // if need to send an elevator somewhere
    // loop below for finding sum of anger for each floor?
    int floorAnger[NUM_FLOORS];
    int floorMaxAnger = 0;
    int openElevator = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        for (int j = 0; j < buildingState.floors[i].numPeople; j++) {
            floorAnger[i] += buildingState.floors[i].people[j].angerLevel;
        }
    }
    
    // floorMaxAnger is equal to 0 rn bc nothing has modified it from initialization until now
    for (int i = 0; i < NUM_FLOORS; i++) {
        if (floorAnger[i] > floorMaxAnger) {
            floorMaxAnger = floorAnger[i];
        }
    }
    // code to not have elevators follow each other
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (!buildingState.elevators[i].isServicing) {
            openElevator = i;
            break;
        }
    }

    // if sending elevator do code below?
    char elevIndex = '0' + openElevator;
    char floorIndex = '0' + floorMaxAnger;
    moveString = 'e' + elevIndex + 'f' + floorMaxAnger;
    return moveString;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    string returnString = "";
    int pickupFloor = buildingState.elevators[move.getElevatorId()].currentFloor;
    int upCount = 0;
    int downCount = 0;
    
    // checks how many people want to go up and down
    for (int i = 0; i < buildingState.floors[pickupFloor].numPeople; i++) {
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() > pickupFloor) {
            upCount++;
        }
        else if (floorToPickup.getPersonByIndex(i).getTargetFloor() < pickupFloor) {
            downCount++;
        }
    }
    
    // gets all indicies that want to go up
    if (upCount > downCount) {
        for (int j = 0; j < buildingState.floors[pickupFloor].numPeople; j++) {
            if (floorToPickup.getPersonByIndex(j).getTargetFloor() > pickupFloor) {
                returnString += char(j + 48);
            }
        }
    }
    // gets all indicies that want to go down
    else if (upCount < downCount) {
        for (int k = 0; k < buildingState.floors[pickupFloor].numPeople; k++) {
            if (floorToPickup.getPersonByIndex(k).getTargetFloor() < pickupFloor) {
                returnString += char(k + 48);
            }
        }
    }
    // if tie of number up and down requests, picks direction of angriest person
    else {
        int angriestPerson = 0;
        // finds index of angriest person
        for (int i = 1; i < buildingState.floors[pickupFloor].numPeople; i++) {
            if (floorToPickup.getPersonByIndex(i).getAngerLevel() > floorToPickup.getPersonByIndex(angriestPerson).getAngerLevel()) {
                angriestPerson = i;
            }
        }
        // if angriest person wants to go up, gets all indicies with that request
        if (floorToPickup.getPersonByIndex(angriestPerson).getTargetFloor() > pickupFloor) {
            for (int j = 0; j < buildingState.floors[pickupFloor].numPeople; j++) {
                if (floorToPickup.getPersonByIndex(j).getTargetFloor() > pickupFloor) {
                    returnString += char(j + 48);
                }
            }
        }
        // if angriest person wants to go down, gets all indicies with that request
        else {
            for (int k = 0; k < buildingState.floors[pickupFloor].numPeople; k++) {
                if (floorToPickup.getPersonByIndex(k).getTargetFloor() < pickupFloor) {
                    returnString += char(k + 48);
                }
            }
        }
    }

    return returnString;
}
