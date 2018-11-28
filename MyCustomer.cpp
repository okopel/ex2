/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyCustomer.h"

MyCustomer::MyCustomer(const string &name, int priority, IDgenerator *company) : name(name) {
    this->priority = priority;
    if (this->priority > 5) {
        this->priority = 5;
    } else if (this->priority < 1) {
        this->priority = 1;
    }
    this->id = company->generate(OTHER);
}

MyCustomer::MyCustomer(const string &id, const string &name, int priority) {
    this->id = id;
    this->name = name;
    this->priority = priority;
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

void MyCustomer::addReserv(Reservation *res) {
    this->reserv.push_back(res);
}






