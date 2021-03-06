/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#ifndef EX2_MYFLIGHT_H
#define EX2_MYFLIGHT_H

#include "MyEmployee.h"

/**
 * impliment of flight.
 */
class MyFlight : virtual public Flight {
    string id;
    int model;
    list<Reservation *> reser;
    list<Employee *> team;
    Date date;
    string from;
    string des;


public:

    explicit MyFlight(int model, const Date &date, const string &from, const string &des, IDgenerator *company,
                      list<Employee *> list);

    explicit MyFlight(const string &id, int model, const string &date, const string &from,
                      const string &des);

    void setTeam(list<Employee *> *team);

    void setTeamBySchecule(Schedule *s);

    int getModelNumber() override;

    /**
     * add reserv to the flight
     * @param res the reservetaion
     */
    void addReserv(Reservation *res);

    list<Reservation *> getReservations() override;

    list<Employee *> getAssignedCrew() override;

    Date getDate() override;

    ~MyFlight() override;

    string getSource() override;

    string getDestination() override;

    string getID() override;

};

#endif //EX2_MYFLIGHT_H
