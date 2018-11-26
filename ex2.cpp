#include <iostream>
#include "ex2.h"

int main() {
    AllId company(0, 0, 0, 0, 0);
    MyEx2 my(company);
    my.addEmployee(2, 1994, "", MANAGER);
    my.addEmployee(4, 1974, "", PILOT);
    my.addEmployee(4, 1850, "", FLY_ATTENDANT);

    my.addCustomer("ori kopel", 3);
    my.addCustomer("shlomo", 5);
    my.addCustomer("moshe", 6);

    my.addFlight(975, Date("2018-11-25"), "israel", "usa");
    my.addFlight(125, Date("2019-01-25"), "Poland", "greece");
    my.addFlight(99965, Date("2019-01-26"), "USA", "greece");
    my.addFlight(8865, Date("2019-02-02"), "london", "israel");
    my.addFlight(6005, Date("2019-01-13"), "Poland", "berlin");
    my.addResevation("o-1", "o-3", FIRST_CLASS, 2);
    my.addResevation("o-2", "o-4", FIRST_CLASS, 2);
    my.addResevation("o-3", "o-1", FIRST_CLASS, 2);
    my.addResevation("o-4", "o-2", FIRST_CLASS, 2);
    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 100));
    map<Classes, int> clas;
    clas.insert(std::pair<Classes, int>(FIRST_CLASS, 12));
    clas.insert(std::pair<Classes, int>(SECOND_CLASS, 1));
    my.addPlane(123, crew, clas);
    my.addPlane(153, crew, clas);
    my.addPlane(3333, crew, clas);


    flightTable t(my.getFlight());


    EmploeeTable e(my.getEemployees());
//    e.printTable();
    e.saveTable();
    e.loadTable();
    cout << "d";
    return 0;
}


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



