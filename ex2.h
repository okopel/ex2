/**************************
 * Ori kopel
 * 205533151
 * okopel@gmail.com
 * ex2
 * nov 2018
 **************************/

#ifndef EX2_EX2_H
#define EX2_EX2_H

#include <vector>
#include "interface.h"


class MyCustomer;

class MyFlight;

class myPlane;

class myID;

class AllId;

class myPlane : public Plane {
    int model;
    int maxFirstClass;
    int maxSecondClass;
    map<Jobs, int> neededCrew;
    string id;
public:
    myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> neededCrew, AllId company);

    string getID() override;

    int getModelNumber() override;

    map<Jobs, int> getCrewNeeded();

    int getMaxFirstClass() override;

    int getMaxEconomyClass() override;
};

class MyReservation : public Reservation {
    MyCustomer *customer;
    MyFlight *flight;
    int baggage;
    Classes classes;
    string id;
public:
    MyReservation(Customer *customer, Flight *flight, int cases, Classes classes, AllId comp);

    Customer *getCustomer() override;

    Flight *getFlight() override;

    Classes getClass() override;

    int getMaxBaggage() override;


    string getID() override;
};


class AllId {
    int mangers;
    int navigators;
    int fly_attendant;
    int pilots;
    int other;
public:
    AllId(int managers = 0, int navigators = 0, int fly_attendant = 0, int pilots = 0, int other = 0);

    string generate(Jobs type);

    int getCount(Jobs type);
};

class myEmploee : public Employee {
    Jobs type;
    string id;
    int seniority;
    int birthYead;
    myEmploee *employer;
public:
    myEmploee(Jobs type, int seniority, int birthYear, myEmploee *employee, AllId company);

    int getSeniority();

    int getBirthYear();

    Jobs getTitle();

    string getID();

    string toString();

    Employee *getEmployer() override;

    ostream &operator<<(ostream &os) {
        return os << this->toString();
    }
};

class MyCustomer : public Customer {
    string name;
    int priority;
    string id;
    list<Reservation *> reserv;
public:
    list<Reservation *> getReservations() override;

    string getID() override;

    int getPriority() override;

    string getFullName() override;

    MyCustomer(const string name, int priority, AllId company);
};

class MyFlight : public Flight {
    string id;
    int model;
    list<Reservation *> reser;
    list<Employee *> team;
    Date date;
    string from;
    string des;

public:
    MyFlight(int model, const Date &date, const string &from, const string &des);

    int getModelNumber() override;

    list<Reservation *> getReservations() override;

    list<Employee *> getAssignedCrew() override;

    Date getDate() override;

    string getSource() override;

    string getDestination() override;

    string getID() override;

};

class MyEx2 : Ex2 {
    AllId company;
    vector<myEmploee> employees;
    list <Plane> planes;
    list <Flight> flight;
    list <Customer> customer;
    list <Reservation> reservs;

public:
    MyEx2();

private:
    Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title);

    myEmploee *getEmployee(const string id);

    Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers);

    Plane *getPlane(string id);

    Flight *addFlight(int model_number, Date date, string source, string destination);

    Flight *getFlight(string id);

    Customer *addCustomer(string full_name, int priority);

    Customer *getCustomer(string id);

    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage);

    Reservation *getReservation(string id);
};

class Table {

};

class flightTable : public Table {

};

class ReservTable : public Table {

};

class EmploeeTable : public Table {

};

class PlaneTable : public Table {

};

#endif //EX2_EX2_H
