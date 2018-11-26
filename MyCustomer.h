//
// Created by okopel on 11/27/18.
//

#ifndef EX2_MYCUSTOMER_H
#define EX2_MYCUSTOMER_H

#include "ex2.h"

class MyCustomer : virtual public Customer {
    string name;
    int priority;
    string id;
    list<Reservation *> reserv;
public:
    MyCustomer(const string &name, int priority, AllId *company);

    list<Reservation *> getReservations() override;

    ~MyCustomer() override = default;

    string getID() override;

    int getPriority() override;

    string getFullName() override;


};

#endif //EX2_MYCUSTOMER_H
