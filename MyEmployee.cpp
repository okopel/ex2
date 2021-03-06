/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyEmployee.h"
#include "IDgenerator.h"

MyEmployee::MyEmployee(Jobs type, int seniority, int birthYear, Employee *employer, IDgenerator *company) {
    this->type = type;
    this->seniority = seniority;
    this->birthYead = birthYear;
    this->employer = employer;
    this->id = company->generate(type);
}

int MyEmployee::getSeniority() {
    return this->seniority;
}

int MyEmployee::getBirthYear() {
    return this->birthYead;
}

Employee *MyEmployee::getEmployer() {
    return this->employer;
}

string MyEmployee::getID() {
    return this->id;
}

Jobs MyEmployee::getTitle() {
    return this->type;
}

string MyEmployee::toString() {
    string s = this->getID();

    return s;
}

MyEmployee::MyEmployee(const string &ID, Jobs type, int seniority, int birthYear, Employee *employer) {
    this->id = ID;
    this->type = type;
    this->seniority = seniority;
    this->birthYead = birthYear;
    this->employer = employer;
}

