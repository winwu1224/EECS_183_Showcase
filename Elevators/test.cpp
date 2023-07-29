/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

// declare your test functions here
void test_person();
void test_floor();
// void test_elevator();

void start_tests() {
    // call your test functions here
    test_person();
    //test_elevator();
    return;
}

// write test functions here
void test_person() {
    // testing non-default Person constuctor
    cout << "Testing Person::Person() - non-default constructor\n";
    Person inputString1("7f4t8a3");
    cout << "turn, expected: 7, actual: " << inputString1.getTurn() << endl;
    cout << "currentfloor, expected: 4, actual: " << inputString1.getCurrentFloor() << endl;
    cout << "targetFloor, expected: 8, actual: " << inputString1.getTargetFloor() << endl;
    cout << "angerLevel, expected: 3, actual: " << inputString1.getAngerLevel() << endl;

    // testing Person::tick() function

    // testing Person::print() function
    cout << "Testing Person::print()" << endl;
    Person p1("7f4t8a3");
    p1.print(cout);
    Person p2("44f3t9a2");
    p2.print(cout);
}
void test_floor(){
    cout << "Testing Floor::removePeople() " << endl;\
    Person p1;
    Person p2;
    Person p3;
    Person p4;
    Person p5;
    Person p6;
    Floor f1;

    f1.addPerson(p1, 1);
    f1.addPerson(p2, 1);
    f1.addPerson(p3, 1);
    f1.addPerson(p4, 1);
    f1.addPerson(p5, 1);
    f1.addPerson(p6, 1);
    int remove[3] = {1,2,3};
    f1.removePeople(remove, 3);


}
//void test_elevators() {
//    // testing Elevator::tick() function
//
//    // testing Elevator::serviceRequest() function
//}
