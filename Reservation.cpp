//
// Created by okopel on 11/22/18.
//

#include "ex2.h"

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


string MyReservation::getID() {
    return this->id;
}

MyReservation::MyReservation(string id, string customer, string flight, int cases, Classes classes) {
//todo
}
