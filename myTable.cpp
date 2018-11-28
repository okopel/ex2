//
// Created by okopel on 11/25/18.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "MyTabels.h"
#include "MyFlight.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyReservation.h"
#include "MyCustomer.h"

FlightTable::FlightTable(std::list<MyFlight *> &list) {
    this->list = list;

}

void FlightTable::printTable() {
    cout << "this is Flight Table:" << endl;
    for (auto fly : this->list) {
        cout << "ID: " << fly->getID() << "\t\t Date:" << fly->getDate().getDate() << "\t\t Model: "
             << fly->getModelNumber() << " \t\t From:" << fly->getSource()
             << " \t\tTo:" << fly->getDestination() << endl;
    }
}

MyFlight *FlightTable::loadFromString(const string &s, MyImplementation *lists) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string id = results.at(0);
    int model = stoi(results.at(1));
    string date = results.at(2);
    string from = this->underscore2space(results.at(3));
    string to = this->underscore2space(results.at(4));
    MyFlight *tmp = new MyFlight(id, model, date, from, to);
    //lists->getFlight().push_back(tmp);
    return tmp;
}

string FlightTable::makeString(MyFlight *tmp) {
    string s =
            tmp->getID() + " " + to_string(tmp->getModelNumber()) + " " + tmp->getDate().getDate() + " " +
            this->space2underscore(tmp->getSource()) + " " +
            this->space2underscore(tmp->getDestination());
    return s;
}


EmploeeTable::EmploeeTable(std::list<Employee *> &list) {
    this->list = list;
}

void EmploeeTable::printTable() {
    cout << "this is Employee Table:" << endl;
    for (auto emp : this->list) {
        string empBosId = "NULL";
        if (emp->getEmployer() != nullptr) {
            empBosId = emp->getEmployer()->getID();
        }
        cout << "ID: " << emp->getID() << "\t\t Jobs:" << emp->getTitle() << "\t\t Birth: "
             << emp->getBirthYear() << " \t\t Employer ID:" << empBosId <<
             " \t\tSeniority:" << emp->getSeniority() << endl;
    }
}

string EmploeeTable::makeString(Employee *tmp) {
    string empBosId = "NULL";
    if (tmp->getEmployer() != nullptr) {
        empBosId = tmp->getEmployer()->getID();
    }
    string s = tmp->getID() + " " + to_string(tmp->getTitle()) + " "
               + to_string(tmp->getBirthYear()) + " " + empBosId + " " +
               to_string(tmp->getSeniority());
    return s;
}


Employee *EmploeeTable::loadFromString(const string &s, MyImplementation *lists) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string ID = results.at(0);
    Jobs job = stringToJobs(results.at(1));
    int birth = stoi(results.at(2));
    string bossID = results.at(3);
    int senyority = stoi(results.at(4));
    Employee *boss = this->findBoss(bossID);
    Employee *emp = new MyEmployee(ID, job, senyority, birth, boss);
    lists->getEemployees().push_back(emp);
    return emp;
}

Employee *EmploeeTable::findBoss(const string &s) {
    for (auto const &emp : this->list) {
        if (emp->getID() == s) {
            return emp;
        }
    }
    return nullptr;
}

EmploeeTable::~EmploeeTable() = default;

template<typename T>
Jobs Table<T>::stringToJobs(const string &s) const {
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
void Table<T>::saveTable(const string &file) {
    this->listToStringList();
    ofstream myfile;
    myfile.open(file);
    if (!myfile.is_open()) {
        throw "Error in saving";
    }
    for (const string &s:this->slist) {
        myfile << s + "\n";
    }
    myfile.close();
}

template<typename T>
void Table<T>::loadTable(const string &file, MyImplementation *lists) {
    string s = "1";
    ifstream myfile;
    myfile.open(file);
    if (!myfile.is_open()) {
        return;
    }
    while (!s.empty()) {
        s = "";
        getline(myfile, s);
        if (!s.empty()) {
            this->list.push_back(this->loadFromString(s, lists));
        }
    }
    myfile.close();
}

template<typename T>
void Table<T>::listToStringList() {
    for (auto tmp : this->list) {
        string s = this->makeString(tmp);
        this->slist.push_back(s);
    }
}

template<typename T>
Table<T>::~Table() {
    for (auto tmp : this->list) {
        delete tmp;
    }

};

string PlanTable::makeString(Plane *tmp) {
    string s = tmp->getID() + " " + to_string(tmp->getModelNumber()) + " " + to_string(tmp->getMaxFirstClass()) + " " +
               to_string(tmp->getMaxEconomyClass()) +
               " " + to_string(tmp->getCrewNeeded().at(MANAGER)) + " " + to_string(tmp->getCrewNeeded().at(NAVIGATOR)) +
               " " + to_string(tmp->getCrewNeeded().at(FLY_ATTENDANT)) + " " +
               to_string(tmp->getCrewNeeded().at(PILOT)) +
               " " + to_string(tmp->getCrewNeeded().at(OTHER));
    return s;
}

Plane *PlanTable::loadFromString(const string &s, MyImplementation *lists) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string id = results.at(0);
    int model = stoi(results.at(1));
    int fClass = stoi(results.at(2));
    int sClass = stoi(results.at(3));
    Jobs manager = this->stringToJobs(results.at(4));
    Jobs navigator = this->stringToJobs(results.at(5));
    Jobs flyAtten = this->stringToJobs(results.at(6));
    Jobs pilot = this->stringToJobs(results.at(7));
    Jobs other = this->stringToJobs(results.at(8));

    map<Jobs, int> crew;

    crew.insert(std::pair<Jobs, int>(MANAGER, manager));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, navigator));
    crew.insert(std::pair<Jobs, int>(FLY_ATTENDANT, flyAtten));
    crew.insert(std::pair<Jobs, int>(PILOT, pilot));
    crew.insert(std::pair<Jobs, int>(OTHER, other));

    Plane *tmp = new myPlane(id, model, fClass, sClass, crew);
    lists->getPlanes().push_back(tmp);
    return tmp;
}


PlanTable::PlanTable(std::list<Plane *> &list) {
    this->list = list;
}

ResTable::ResTable(std::list<Reservation *> &list) {
    this->list = list;
}

Reservation *ResTable::loadFromString(const string &s, MyImplementation *lists) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string id = results.at(0);
    string cust = results.at(1);
    string flyId = results.at(2);
    int cases = stoi(results.at(3));
    Classes c;
    string classNum = results.at(4);
    if (classNum == "0") {
        c = FIRST_CLASS;
    } else {
        c = SECOND_CLASS;
    }

    Reservation *tmp = new MyReservation(id, lists->getCustomer(cust), lists->getFlight(flyId), cases, c);
    //lists->addResevation(id, flyId, c, cases);//todo
    //lists->getReservs().push_back(tmp);
    return tmp;
}

string ResTable::makeString(Reservation *tmp) {
    string s = tmp->getID() + " " + tmp->getCustomer()->getID() + " " + tmp->getFlight()->getID() + " " +
               to_string(tmp->getMaxBaggage()) + " " + to_string(tmp->getClass());
    return s;
}

ResTable::~ResTable() = default;


CusTable::CusTable(std::list<Customer *> &list) {
    this->list = list;
}

string CusTable::makeString(Customer *tmp) {
    string s = tmp->getID() + " " + this->space2underscore(tmp->getFullName()) + " " +
               to_string(tmp->getPriority());
    return s;
}

Customer *CusTable::loadFromString(const string &s, MyImplementation *lists) {
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    string id = results.at(0);
    string name = this->underscore2space(results.at(1));
    int priority = stoi(results.at(2));
    Customer *tmp = new MyCustomer(id, name, priority);
    //lists->getCustomer().push_back(tmp);
    lists->addMyCustomer(id, name, priority);
    return tmp;
}

template<typename T>
string Table<T>::space2underscore(string text) {
    for (char &it : text) {
        if (it == ' ') {
            it = '_';
        }
    }
    return text;
}

template<typename T>
string Table<T>::underscore2space(string text) {
    for (char &it : text) {
        if (it == '_') {
            it = ' ';
        }
    }
    return text;
}

template<typename T>
list<T *> &Table<T>::getTlist() {
    return this->list;
}
