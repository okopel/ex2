//
// Created by okopel on 11/22/18.
//

#include "MyFlight.h"

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

MyFlight::MyFlight(int model, const Date &date, const string &from, const string &des, AllId *company) : model(model),
                                                                                                         date(date),
                                                                                                         from(from),
                                                                                                         des(des) {
    this->id = company->generate(OTHER);
}

MyFlight::MyFlight(const string &id, int model, const string &date, const string &from, const string &des) : model(
        model),
                                                                                                             id(id),
                                                                                                             from(from),
                                                                                                             des(des),
                                                                                                             date(Date(
                                                                                                                     date)) {

}

MyFlight::~MyFlight() = default;
