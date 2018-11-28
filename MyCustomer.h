/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#ifndef EX2_MYCUSTOMER_H
#define EX2_MYCUSTOMER_H

#include "interface.h"
#include "IDgenerator.h"
#include "MyFlight.h"

/**
 * Class of my customer
 */
class MyCustomer : virtual public Customer {
    string name;
    int priority;
    string id;
    list<Reservation *> reserv;
public:
    MyCustomer(const string &name, int priority, IDgenerator *company);

    MyCustomer(const string &id, const string &name, int priority);

    list<Reservation *> getReservations() override;

    string getID() override;

    int getPriority() override;

    string getFullName() override;

    /**
     * add reserv to this custemer
     * @param res the res to be added
     */
    void addReserv(Reservation *res);

    ~MyCustomer() override = default;

};

#endif //EX2_MYCUSTOMER_H
