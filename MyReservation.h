/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#ifndef EX2_MYRESERVATION_H
#define EX2_MYRESERVATION_H

#include "MyImplementation.h"

/**
 * implement of reserrvetation
 */
class MyReservation : virtual public Reservation {
    Customer *customer;
    Flight *flight;
    int baggage;
    Classes classes;
    string id;
public:
    explicit MyReservation(Customer *customer, Flight *flight, int cases, Classes classes, IDgenerator *comp);

    explicit MyReservation(const string &id, Customer *customer, Flight *flight, int cases, Classes classes);

    Customer *getCustomer() override;

    Flight *getFlight() override;

    Classes getClass() override;

    int getMaxBaggage() override;

    string getID() override;
};

#endif //EX2_MYRESERVATION_H
