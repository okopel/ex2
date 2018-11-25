//
// Created by okopel on 11/25/18.
//
#include <iostream>
#include "ex2.h"

flightTable::flightTable(std::list<Flight *> list) {
    this->list = list;
}

void flightTable::printTable() {

    for (auto fly : this->list) {
        cout << "ID: " << fly->getID() << "\t\t Model: " << fly->getModelNumber() << " \t\t From:" << fly->getSource()
             << " \t\tTo:" << fly->getDestination() << endl;

    }

}

void flightTable::saveTable() {

}

void flightTable::loadTable() {

}