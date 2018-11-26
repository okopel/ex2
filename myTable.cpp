//
// Created by okopel on 11/25/18.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
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

Flight *flightTable::loadFromString(string s) {
    return nullptr; //todo
}

void flightTable::listToStringList() {

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


void EmploeeTable::listToStringList() {
    for (auto emp : this->list) {
        string empBosId = "NULL";
        if (emp->getEmployer() != NULL) {
            empBosId = emp->getEmployer()->getID();
        }
        string s = emp->getID() + " " + to_string(emp->getTitle()) + " "
                   + to_string(emp->getBirthYear()) + " " + empBosId + " " +
                   to_string(emp->getSeniority());

        slist.push_back(s);
    }
}


Employee *EmploeeTable::loadFromString(string s) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string ID = results.at(0);
    Jobs job = stringToJobs(results.at(1));
    int birth = stoi(results.at(2));
    string bossID = results.at(3);
    int senyority = stoi(results.at(4));
    Employee *boss = this->findBoss(bossID);
    Employee *emp = new myEmploee(ID, job, senyority, birth, boss);
    return emp;
}

Employee *EmploeeTable::findBoss(string s) {
    for (auto const &emp : this->list) {
        if (emp->getID() == s) {
            return emp;
        }
    }
    return nullptr;
}

template<typename T>
Jobs Table<T>::stringToJobs(string s) {
    if (s == "0")
        return MANAGER;
    if (s == "1")
        return NAVIGATOR;
    if (s == "2")
        return FLY_ATTENDANT;
    if (s == "3")
        return PILOT;
    return OTHER;
}

template<typename T>
void Table<T>::saveTable(string file) {
    this->listToStringList();
    ofstream myfile;
    myfile.open(file);
    if (!myfile.is_open()) {
        return;
    }
    for (string s:this->slist) {
        myfile << s + "\n";
    }
    myfile.close();
}

template<typename T>
void Table<T>::loadTable(string file) {
    string s = "1";
    ifstream myfile;
    myfile.open(file);
    if (!myfile.is_open()) {
        return;
    }
    while (s != "") {
        s = "";
        getline(myfile, s);
        if (s != "") {
            this->list.push_back(this->loadFromString(s));
        }
    }
    myfile.close();
}
