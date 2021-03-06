/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyFlight.h"
#include "IDgenerator.h"

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

MyFlight::MyFlight(int model, const Date &date, const string &from, const string &des, IDgenerator *company,
                   list<Employee *> list) : model(model),
                                            date(date),
                                            from(from),
                                            des(des) {
    this->id = company->generate(OTHER);
    this->team = list;
}

MyFlight::MyFlight(const string &id, int model, const string &date, const string &from, const string &des) : model(
        model),
                                                                                                             id(id),
                                                                                                             from(from),
                                                                                                             des(des),
                                                                                                             date(Date(
                                                                                                                     date)) {

}

void MyFlight::addReserv(Reservation *res) {
    this->reser.push_back(res);
}

void MyFlight::setTeam(list<Employee *> *team) {
    MyFlight::team = *team;
}

void MyFlight::setTeamBySchecule(Schedule *s) {
}

MyFlight::~MyFlight() = default;
