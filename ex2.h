/**************************
 * Ori kopel
 * 205533151
 * okopel@gmail.com
 * ex2
 * nov 2018
 **************************/

#ifndef EX2_EX2_H
#define EX2_EX2_H
#define EMP_FILE "Employee.txt"
#define CUS_FILE "Custemer.txt"
#define PLAN_FILE "Plans.txt"
#define RES_FILE "Reservation.txt"


#include "interface.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

class MyCustomer;

class MyFlight;

class MyReservation;

class myPlane;

class MyEx2;

class myID;

class AllId;

class MyDate;

class ResTable;

class EmploeeTable;

class PlaneTable;


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
    Employee *employer;
public:
    myEmploee(Jobs type, int seniority, int birthYear, Employee *employee, AllId company);

    myEmploee(string ID, Jobs type, int seniority, int birthYear, Employee *employee);

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
    list<Employee *> employees;
    list<Plane *> planes;
    list<Flight *> flight;
    list<Customer *> customer;
    list<Reservation *> reservs;

public:
    explicit MyEx2(AllId company);


    list<Employee *> getEemployees() {
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

    Employee *getEmployee(const string id) override;

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

template<typename T>

class Table {
protected:
    std::list<string> slist;
    std::list<T *> list;
public:
    virtual void saveTable(const string file);

    virtual void loadTable(const string file);

    virtual void listToStringList();

    virtual string makeString(T *tmp) = 0;

    virtual T *loadFromString(string s) = 0;

    //virtual void printTable() = 0;

    Jobs stringToJobs(string s);

};


class flightTable : public Table<Flight> {
public:
    explicit flightTable(std::list<Flight *> list);

    Flight *loadFromString(string s) override;

    string makeString(Flight *tmp) override;

    void printTable();
};


class EmploeeTable : virtual public Table<Employee> {
public:
    explicit EmploeeTable(std::list<Employee *> list);

    void printTable();

    string makeString(Employee *tmp) override;

    Employee *findBoss(string s);

    Employee *loadFromString(string s) override;
};

class PlanTable : virtual public Table<Plane> {
public:
    explicit PlanTable(std::list<Plane *> list);

    string makeString(Plane *tmp) override;

    void printTable();

    Plane *loadFromString(string s) override;
};

class ResTable : virtual public Table<Reservation> {
public:
    explicit ResTable(std::list<Reservation *> list);

    string makeString(Reservation *tmp) override;

    Reservation *loadFromString(string s) override;
};

#endif //EX2_EX2_H
