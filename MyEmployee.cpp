//
// Created by okopel on 11/25/18.
//

#include "ex2.h"

myEmploee::myEmploee(Jobs type, int seniority, int birthYear, Employee *employer, AllId company) {
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