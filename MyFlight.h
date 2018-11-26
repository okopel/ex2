//
// Created by okopel on 11/27/18.
//

#ifndef EX2_MYFLIGHT_H
#define EX2_MYFLIGHT_H

#include "ex2.h"


class MyFlight : virtual public Flight {
    string id;
    int model;
    list<Reservation *> reser;
    list<Employee *> team;
    Date date;
    string from;
    string des;

public:
    explicit MyFlight(int model, const Date &date, const string &from, const string &des, AllId *company);

    explicit MyFlight(const string &id, int model, const string &date, const string &from, const string &des);

    int getModelNumber() override;

    list<Reservation *> getReservations() override;

    list<Employee *> getAssignedCrew() override;

    Date getDate() override;

    ~MyFlight() override;

    string getSource() override;

    string getDestination() override;

    string getID() override;

};

#endif //EX2_MYFLIGHT_H