#include <iostream>
#include "MyImplementation.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyCustomer.h"
#include "MyReservation.h"

Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    Employee *boss = this->getEmployee(employer_id);
    Employee *emp = new MyEmployee(title, seniority, birth_year, boss, this->company);
    this->employees.push_back(emp);
    return this->getEmployee(emp->getID());
}

Employee *MyImplementation::getEmployee(const string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &employee : this->employees) {
        if (employee->getID() == (id)) { continue; }
        return employee;
    }
    return nullptr;

}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    Plane *mp = new myPlane(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
                            this->company);
    this->planes.push_back(mp);
    return this->getPlane(mp->getID());
}

Plane *MyImplementation::getPlane(string id) {
    for (auto const &plane : this->planes) {
        if (plane->getID() == id) {
            return plane;
        }
    }
    return nullptr;
}

Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    if (!this->checkAvailiblePlanAndCrew(date, model_number)) {
        cout << "There isnt free plan or free crew" << endl;
        return nullptr;
    }
    Flight *myFlight = new MyFlight(model_number, date, source, destination, this->company);
    this->flight.push_back(myFlight);
    return this->getFlight(myFlight->getID());
}

Flight *MyImplementation::getFlight(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &flight : this->flight) {
        if (flight->getID() == id) {
            return flight;
        }
    }
    return nullptr;
}

Customer *MyImplementation::addCustomer(string full_name, int priority) {
    Customer *myCustomer = new MyCustomer(full_name, priority, this->company);
    this->customer.push_back(myCustomer);
    return this->getCustomer(myCustomer->getID());
}

Customer *MyImplementation::getCustomer(string id) {
    for (auto const &cust : this->customer) {
        if (cust->getID() == id) {
            return cust;
        }
    }
    return nullptr;
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    Reservation *myres = new MyReservation(this->getCustomer(customerId), this->getFlight(flightId), max_baggage, cls,
                                           this->company);
    this->reservs.push_back(myres);
    return this->getReservation(myres->getID());
}

Reservation *MyImplementation::getReservation(string id) {
    for (auto const &res : this->reservs) {
        if (res->getID() == id) {
            return res;
        }
    }
    return nullptr;
}

void MyImplementation::exit() {
}

MyImplementation::~MyImplementation() = default;

list<Employee *> &MyImplementation::getEemployees() {
    return this->employees;
}

list<Plane *> &MyImplementation::getPlanes() {
    return this->planes;
}

list<Flight *> &MyImplementation::getFlight() {
    return this->flight;
}

list<Customer *> &MyImplementation::getCustomer() {
    return this->customer;
}

list<Reservation *> &MyImplementation::getReservs() {
    return this->reservs;
}

MyImplementation::MyImplementation() {
    this->company = new AllId(0, 0, 0, 0, 0);
}

bool MyImplementation::checkAvailiblePlanAndCrew(Date date, int model) {
    //check for free plan
    int res = this->getResPerDatePerModel(date, model);
    int plan = this->numOfPlanesFromModel(model);
    //if there are 1 free plan at least to do this resev (not >= becouse we want 1 free plan).
    if (plan <= res) {
        return false;
    }
    //check for free crew //todo
    if (!this->checkForCrew(model, date)) {
        return false;
    }
    return true;
}

unsigned long MyImplementation::getResPerDatePerModel(Date date, int model) {
    list<Flight *> list;
    for (auto const &res : this->flight) {
        if ((res->getDate() == date) && (res->getModelNumber() == model)) {
            list.push_back(res);
        }
    }
    return list.size();
}

int MyImplementation::numOfPlanesFromModel(const int model) const {
    int counter = 0;
    for (auto const &plan : this->planes) {
        if (plan->getModelNumber() == model) {
            counter++;
        }
    }
    return counter;
}

bool MyImplementation::checkForCrew(int model, Date date) {
    map<Jobs, int> nedded;
    for (auto const &plan : this->planes) {
        if (plan->getModelNumber() == model) {
            nedded = plan->getCrewNeeded();
            break;
        }
    }
    if (nedded.empty()) {
        //there isnt model.
        return false;
    }
    map<Jobs, int> busy = this->busyAtDate(date);
    map<Jobs, int> existing = this->existing();

    if ((existing[MANAGER] - busy[MANAGER]) < nedded[MANAGER]) {
        return false;
    }
    if ((existing[FLY_ATTENDANT] - busy[FLY_ATTENDANT]) < nedded[FLY_ATTENDANT]) {
        return false;
    }
    if ((existing[NAVIGATOR] - busy[NAVIGATOR]) < nedded[NAVIGATOR]) {
        return false;
    }
    if ((existing[OTHER] - busy[OTHER]) < nedded[OTHER]) {
        return false;
    }
    if ((existing[PILOT] - busy[PILOT]) < nedded[PILOT]) {
        return false;
    }
    return true;
}

Plane *MyImplementation::getPlaneByModel(int model) {
    for (auto const &plane : this->planes) {
        if (plane->getModelNumber() == model) {
            return plane;
        }
    }
    return nullptr;
}

map<Jobs, int> MyImplementation::busyAtDate(Date date) {
    map<Jobs, int> busy;
    for (auto const &fly : this->flight) {
        if (fly->getDate() == date) {
            map<Jobs, int> thisPlanCrew = this->getPlaneByModel(fly->getModelNumber())->getCrewNeeded();
            busy[MANAGER] += thisPlanCrew[MANAGER];
            busy[FLY_ATTENDANT] += thisPlanCrew[FLY_ATTENDANT];
            busy[NAVIGATOR] += thisPlanCrew[NAVIGATOR];
            busy[OTHER] += thisPlanCrew[OTHER];
            busy[PILOT] += thisPlanCrew[PILOT];
        }
    }
    return busy;
}

map<Jobs, int> MyImplementation::existing() {
    map<Jobs, int> exist;
    for (auto const &emp : this->employees) {
        exist[emp->getTitle()]++;//todo check if new title is adding
    }
    return exist;
}


