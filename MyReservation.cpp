/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyReservation.h"
#include "IDgenerator.h"

MyReservation::MyReservation(Customer *customer, Flight *flight, int baggage, Classes classes, IDgenerator *comp) :
        baggage(baggage), classes(classes), customer(customer), flight(flight) {
    this->id = comp->generate(OTHER);
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


string MyReservation::getID() {
    return this->id;
}

MyReservation::MyReservation(const string &id, Customer *customer, Flight *flight, int cases, Classes classes) : id(id),
                                                                                                                 customer(
                                                                                                                         customer),
                                                                                                                 flight(flight),
                                                                                                                 baggage(cases),
                                                                                                                 classes(classes) {

}

