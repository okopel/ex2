//
// Created by okopel on 11/25/18.
//
#include <iostream>
#include "ex2.h"

flightTable::flightTable(std::list<Flight *> list) {
    this->list = list;
}

void flightTable::printTable() {
    cout << "this is Flight Table:" << endl;
    for (auto fly : this->list) {
        cout << "ID: " << fly->getID() << "\t\t Date:" << fly->getDate().getDate() << "\t\t Model: "
             << fly->getModelNumber() << " \t\t From:" << fly->getSource()
             << " \t\tTo:" << fly->getDestination() << endl;
    }
}

void flightTable::saveTable() {

}

void flightTable::loadTable() {

}


EmploeeTable::EmploeeTable(std::list<Employee *> list) {
    this->list = list;

}

void EmploeeTable::printTable() {
    cout << "this is Employee Table:" << endl;
    for (auto emp : this->list) {
        string empBosId = "";
        if (emp->getEmployer() != NULL) {
            empBosId = emp->getEmployer()->getID();
        }
        cout << "ID: " << emp->getID() << "\t\t Jobs:" << emp->getTitle() << "\t\t Birth: "
             << emp->getBirthYear() << " \t\t Employer ID:" << empBosId <<
             " \t\tSeniority:" << emp->getSeniority() << endl;
    }
}

void EmploeeTable::saveTable() {
    this->listToStringList();
    ofstream myfile;
    myfile.open(EMP_FILE);
    if (!myfile.is_open()) {
        return;
    }
    for (string s:this->slist) {
        myfile << s + "\n";
    }
    myfile.close();
}

void EmploeeTable::listToStringList() {
    for (auto emp : this->list) {
        string empBosId = "";
        if (emp->getEmployer() != NULL) {
            empBosId = emp->getEmployer()->getID();
        }
        string s = "@ID:" + emp->getID() + " @Jobs:" + to_string(emp->getTitle()) + " @Birth:"
                   + to_string(emp->getBirthYear()) + " @EmployerID:" + empBosId + " @Seniority:" +
                   to_string(emp->getSeniority()) + "~";

        slist.push_back(s);
    }
}

void EmploeeTable::loadTable() {

}
