#include <iostream>
#include "ex2.h"


Employee *MyEx2::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    Employee *boss = this->getEmployee(employer_id);
    Employee *emp = new myEmploee(title, seniority, birth_year, boss, this->company);
    this->employees.push_back(emp);
    return this->getEmployee(emp->getID());
}

Employee *MyEx2::getEmployee(const string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &employee : this->employees) {
        if (employee->getID() == (id)) { continue; }
        return employee;
    }
    return nullptr;

}

Plane *MyEx2::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    Plane *mp = new myPlane(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
                            this->company);
    this->planes.push_back(mp);
    return this->getPlane(mp->getID());
}

Plane *MyEx2::getPlane(string id) {
    for (auto const &plane : this->planes) {
        if (plane->getID() == id) {
            return plane;
        }
    }
    return nullptr;
}

Flight *MyEx2::addFlight(int model_number, Date date, string source, string destination) {
    Flight *myFlight = new MyFlight(model_number, date, source, destination, &this->company);
    this->flight.push_back(myFlight);
    return this->getFlight(myFlight->getID());
}

Flight *MyEx2::getFlight(string id) {
    for (auto const &flight : this->flight) {
        if (flight->getID() == id) {
            return flight;
        }
    }
    return nullptr;
}

Customer *MyEx2::addCustomer(string full_name, int priority) {
    Customer *myCustomer = new MyCustomer(full_name, priority, this->company);
    this->customer.push_back(myCustomer);
    return this->getCustomer(myCustomer->getID());
}

Customer *MyEx2::getCustomer(string id) {
    for (auto const &cust : this->customer) {
        if (cust->getID() == id) {
            return cust;
        }

    }
    return nullptr;
}

Reservation *MyEx2::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {

    Reservation *myres = new MyReservation(this->getCustomer(customerId), this->getFlight(flightId), max_baggage, cls,
                                           this->company);
    this->reservs.push_back(myres);
    return this->getReservation(myres->getID());
}

Reservation *MyEx2::getReservation(string id) {
    for (auto const &res : this->reservs) {
        if (res->getID() == id) {
            return res;
        }
    }
    return nullptr;
}

void MyEx2::exit() {

}

MyEx2::~MyEx2() {

}

MyEx2::MyEx2(AllId company) {
    this->company = company;
}

