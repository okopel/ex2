#include <iostream>
#include "ex2.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    AllId company(0, 0, 0, 0, 0);
    MyEx2 my(company);
    my.addEmployee(2, 1994, "", MANAGER);
    my.addEmployee(4, 1974, "", PILOT);
    my.addCustomer("ori kopel", 3);
    my.addCustomer("shlomo", 5);
    my.addFlight(975, Date("2018-11-25"), "israel", "usa");
    my.addFlight(6665, Date("2019-01-25"), "Poland", "greece");
    my.addResevation("c-1", "??", FIRST_CLASS, 2);
    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 100));
    map<Classes, int> clas;
    clas.insert(std::pair<Classes, int>(FIRST_CLASS, 12));
    my.addPlane(123, crew, clas);
    flightTable t(my.getFlight());
    t.printTable();

    return 0;
}


myEmploee::myEmploee(Jobs type, int seniority, int birthYear, myEmploee *employer, AllId company) {
    this->type = type;
    this->seniority = seniority;
    this->birthYead = birthYear;
    this->employer = employer;
    this->id = company.generate(type);
}

int myEmploee::getSeniority() {
    return this->seniority;
}

int myEmploee::getBirthYear() {
    return this->birthYead;
}

Employee *myEmploee::getEmployer() {
    return this->employer;
}

string myEmploee::getID() {
    return this->id;
}

Jobs myEmploee::getTitle() {
    return this->type;
}

string myEmploee::toString() {
    string s = this->getID();

    return s;
}


string AllId::generate(Jobs type) {
    return "" + to_string(type) + "-" + to_string(this->getCount(type));
}

int AllId::getCount(Jobs type) {
    switch (type) {
        case MANAGER:
            this->mangers++;
            return this->mangers;
        case NAVIGATOR:
            this->navigators++;
            return this->navigators;

        case FLY_ATTENDANT:
            this->fly_attendant++;
            return this->fly_attendant;

        case PILOT:
            this->pilots++;
            return this->pilots;

        case OTHER:
            this->other++;
            return this->other;

        default:
            return -1;
    }
}

AllId::AllId(int managers, int navigators, int fly_attendant, int pilots, int other) {
    this->mangers = 0;
    this->navigators = 0;
    this->fly_attendant = 0;
    this->pilots = 0;
    this->other = 0;
}


Date::Date(string date) {
    this->date = date;
}

bool Date::operator<(const Date &d) const {

    string thisDate = this->date.substr(0, 4);
    string otherDate = d.date.substr(0, 4);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }

    thisDate = this->date.substr(5, 2);
    otherDate = d.date.substr(5, 2);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }
    thisDate = this->date.substr(8, 2);
    otherDate = d.date.substr(8, 2);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }
    return false;
}

bool Date::operator>(const Date &d) const {
    return !((this < &d) || (this == &d));
}

bool Date::operator==(const Date &d) const {
    return (this->date == d.date);


}

MyReservation::MyReservation(Customer *customer, Flight *flight, int baggage, Classes classes, AllId comp) :
        baggage(baggage), classes(classes), customer(customer), flight(flight) {

    this->id = comp.generate(OTHER);
}

Customer *MyReservation::getCustomer() {
    return this->customer;
}

Flight *MyReservation::getFlight() {
    return this->flight;
}

Classes MyReservation::getClass() {
    return this->classes;
}

int MyReservation::getMaxBaggage() {
    return this->baggage;
}

MyCustomer::MyCustomer(const string name, int priority, AllId company) {
    this->name = name;
    this->priority = priority;
    if (this->priority > 5) {
        this->priority = 5;
    } else if (this->priority < 1) {
        this->priority = 1;
    }
    this->id = company.generate(OTHER);
}

int MyCustomer::getPriority() {
    return this->priority;
}

string MyCustomer::getFullName() {
    return this->name;
}


list<Reservation *> MyCustomer::getReservations() {
    return this->reserv;
}

string MyCustomer::getID() {
    return this->id;
}

string MyReservation::getID() {
    return this->id;
}

string MyFlight::getID() {
    return this->id;
}

int MyFlight::getModelNumber() {
    return this->model;
}

list<Reservation *> MyFlight::getReservations() {
    return this->reser;
}

list<Employee *> MyFlight::getAssignedCrew() {
    return this->team;
}

Date MyFlight::getDate() {
    return this->date;
}

string MyFlight::getSource() {
    return this->from;
}

string MyFlight::getDestination() {
    return this->des;
}

MyFlight::MyFlight(int model, const Date &date, const string &from, const string &des) : model(model), date(date),
                                                                                         from(from), des(des) {

}


Employee *MyEx2::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {

    myEmploee *boss = this->getEmployee(employer_id);
    myEmploee emp(title, seniority, birth_year, boss, this->company);
    this->employees.push_back(emp);
    return this->getEmployee(emp.getID());

}

myEmploee *MyEx2::getEmployee(const string id) {
    if (id == "") {
        return nullptr;
    }
    for (auto &employee : this->employees) {
        if (employee.getID() == (id)) { continue; }
        return &employee;
    }
    return nullptr;

}

Plane *MyEx2::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    Plane *mp = new myPlane(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
                            this->company);
//    myPlane mp(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
//               this->company);
    this->planes.push_back(mp);
    return this->getPlane(mp->getID());
}

Plane *MyEx2::getPlane(string id) {
    for (auto &plane : this->planes) {
        if (plane->getID().compare(id) == 0) { continue; }
        return plane;
    }
    return nullptr;
}

Flight *MyEx2::addFlight(int model_number, Date date, string source, string destination) {
    MyFlight myFlight(model_number, date, source, destination);
    this->flight.push_back(&myFlight);
    return this->getFlight(myFlight.getID());
}

Flight *MyEx2::getFlight(string id) {
    for (auto &flight : this->flight) {
        if (flight->getID().compare(id) == 0) { continue; }
        return flight;
    }
    return nullptr;
}

Customer *MyEx2::addCustomer(string full_name, int priority) {
    Customer *myCustomer = new MyCustomer(full_name, priority, this->company);
    this->customer.push_back(myCustomer);
    return this->getCustomer(myCustomer->getID());
}

Customer *MyEx2::getCustomer(string id) {
    for (auto &cust : this->customer) {
        if (cust->getID().compare(id) == 0) { continue; }
        return cust;
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
    for (auto &res : this->reservs) {
        if (res->getID().compare(id) == 0) { continue; }
        return res;
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

myPlane::myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> neededCrew, AllId company)
        : model(model),
          maxFirstClass(
                  maxFirstClass),
          maxSecondClass(
                  maxSecondClass), neededCrew(
                neededCrew) {
    this->id = company.generate(OTHER);
}

int myPlane::getModelNumber() {
    return this->model;
}

map<Jobs, int> myPlane::getCrewNeeded() {
    return this->neededCrew;
}

int myPlane::getMaxFirstClass() {
    return this->maxFirstClass;
}

int myPlane::getMaxEconomyClass() {
    return this->maxSecondClass;
}

string myPlane::getID() {
    return this->id;
}

MyDate::MyDate(string date) : Date(date) {
    this->date = date;
}

bool MyDate::operator<(const Date &d) const {
    return Date::operator<(d);
}

bool MyDate::operator>(const Date &d) const {
    return Date::operator>(d);
}

bool MyDate::operator==(const Date &d) const {
    return Date::operator==(d);
}

string MyDate::getDate() {
    return this->date;
}

flightTable::flightTable(std::list<Flight *> list) {
    this->list = list;
}

void flightTable::printTable() {

    printf("%s \t %s \t%s \t%s \t%s \t", "ID", "Model", "date", "From", "to");
    for (auto fly : this->list) {
        auto id = fly->getID() + "";
        string des = fly->getDestination() + "";
        string from = fly->getSource() + "";
        printf("%s \t %d \t %s \t %s \t", &id, fly->getModelNumber()/*, fly.getDate()*/, &from, &des);

    }

}

void flightTable::saveTable() {

}

void flightTable::loadTable() {

}
