//
// Created by okopel on 11/27/18.
//

#ifndef EX2_MYCUSTOMER_H
#define EX2_MYCUSTOMER_H

#include "interface.h"
#include "AllID.h"
#include "MyFlight.h"

class MyCustomer : virtual public Customer {
    string name;
    int priority;
    string id;
    list<Reservation *> reserv;
public:
    MyCustomer(const string &name, int priority, AllId *company);

    MyCustomer(const string &id, const string &name, int priority);

    list<Reservation *> getReservations() override;

    string getID() override;

    int getPriority() override;

    string getFullName() override;

    void addReserv(Reservation *res);

    ~MyCustomer() override = default;


};

#endif //EX2_MYCUSTOMER_H
