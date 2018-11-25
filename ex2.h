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
#include <string>
#include <cstring>
#include <cstdio>
#include <stdlib.h>


class MyCustomer;

class MyFlight;

class myPlane;

class myID;

class AllId;

class MyDate;

class MyDate : public Date {
    string date;
public:
    string getDate() override;

    MyDate(string &date);

    MyDate(string date);

    bool operator<(const Date &d) const override;

    bool operator>(const Date &d) const override;

    bool operator==(const Date &d) const override;
};

class myPlane : virtual public Plane {
    int model;
    int maxFirstClass;
    int maxSecondClass;
    map<Jobs, int> neededCrew;
    string id;
public:
    myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> neededCrew, AllId company);

    string getID() override;

    int getModelNumber() override;

    map<Jobs, int> getCrewNeeded() override;

    int getMaxFirstClass() override;

    int getMaxEconomyClass() override;

    ~myPlane() override;
};

class MyReservation : virtual public Reservation {
    Customer *customer;
    Flight *flight;
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
    explicit AllId(int managers = 0, int navigators = 0, int fly_attendant = 0, int pilots = 0, int other = 0);

    string generate(Jobs type);

    int getCount(Jobs type);
};

class myEmploee : virtual public Employee {
    Jobs type;
    string id;
    int seniority;
    int birthYead;
    myEmploee *employer;
public:
    myEmploee(Jobs type, int seniority, int birthYear, myEmploee *employee, AllId company);

    int getSeniority() override;

    int getBirthYear() override;

    Jobs getTitle() override;

    string getID() override;

    string toString();

    Employee *getEmployer() override;

    ostream &operator<<(ostream &os) {
        return os << this->toString();
    }
};

class MyCustomer : virtual public Customer {
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

class MyFlight : virtual public Flight {
    string id;
    int model;
    list<Reservation *> reser;
    list<Employee *> team;
    Date date;
    string from;
    string des;

public:
    MyFlight(int model, const Date &date, const string &from, const string &des, AllId *company);

    int getModelNumber() override;

    list<Reservation *> getReservations() override;

    list<Employee *> getAssignedCrew() override;

    Date getDate() override;

    ~MyFlight() override;

    string getSource() override;

    string getDestination() override;

    string getID() override;

};

class MyEx2 : virtual public Ex2 {
    AllId company;
    vector<myEmploee> employees;
    list<Plane *> planes;
    list<Flight *> flight;
    list<Customer *> customer;
    list<Reservation *> reservs;

public:
    MyEx2(AllId company);


    vector<myEmploee> getEemployees() {
        return this->employees;
    }

    list<Plane *> getPlanes() {
        return this->planes;
    }

    list<Flight *> getFlight() {
        return this->flight;
    }

    list<Customer *> getCustomer() {
        return this->customer;
    }

    list<Reservation *> getReservs() {
        return this->reservs;
    };


    Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title) override;

    myEmploee *getEmployee(const string id) override;

    Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) override;

    Plane *getPlane(string id) override;

    Flight *addFlight(int model_number, Date date, string source, string destination) override;

    Flight *getFlight(string id) override;

    Customer *addCustomer(string full_name, int priority) override;

    Customer *getCustomer(string id) override;

    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage) override;

    Reservation *getReservation(string id) override;

    void exit() override;

    ~MyEx2() override;
};

class Table {

public:
    virtual void saveTable() = 0;

    virtual void loadTable() = 0;

    virtual void printTable() = 0;

};

class flightTable : virtual public Table {
    std::list<Flight *> list;
public:
    explicit flightTable(std::list<Flight *> list);

    void saveTable() override;

    void loadTable() override;

    void printTable() override;
};

class ReservTable : public Table {

};

class EmploeeTable : public Table {

};

class PlaneTable : public Table {

};

#endif //EX2_EX2_H
