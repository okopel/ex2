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
#define FLY_FILE "Fly.txt"

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "interface.h"

enum LoadTableType {
    EMP, CUS, PLAN, FLY, RES
};

class MyImplementation;

class AllId;

class ResTable;

class EmploeeTable;

class FlightTable;

class MyCustomer;

class MyFlight;

class MyImplementation : virtual public Ex2 {
    AllId *company;
    list<Employee *> employees;
    list<Plane *> planes;
    list<Flight *> flight;
    list<Customer *> customer;
    list<Reservation *> reservs;
    map<LoadTableType, bool> hasloaded;
    list<MyCustomer *> myCusList;
    list<MyFlight *> myFlyList;

    list<Employee *> *arrangeWorkers(map<Jobs, int> crew, Date &date);

    bool isWorkerAvailible(const Employee *emp, const Date &date);

    void loadFromFile(const LoadTableType &num);

    bool checkForCrew(const int &model, const Date &date);

    bool checkAvailiblePlanAndCrew(const Date &date, const int &model);

    Plane *getPlaneByModel(const int &model);

    map<Jobs, int> existing();

    map<Jobs, int> busyAtDate(const Date &date);

    bool checkForPlaceInFlightInClass(Flight *fly, const Classes &cls);

    unsigned long getResPerDatePerModel(const Date &date, const int &model);

    int numOfPlanesFromModel(const int &model) const;

    int numOfSeatsFromModel(const int &model, const Classes &cls);

    int numOfCatch(Flight *fly, const Classes &cls);

public:
    explicit MyImplementation();

    list<Employee *> &getEemployees();

    list<Plane *> &getPlanes();

    list<Flight *> &getFlight();

    list<Customer *> &getCustomer();


    list<Reservation *> &getReservs();

    Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title) override;

    Employee *getEmployee(const string id) override;

    Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) override;

    Plane *getPlane(string id) override;

    Flight *addFlight(int model_number, Date date, string source, string destination) override;

    Flight *getFlight(string id) override;

    MyFlight *getMyFlight(string id);


    Customer *addCustomer(string full_name, int priority) override;

    Customer *getCustomer(string id) override;

    MyCustomer *getMyCustomer(string id);


    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage) override;

    Reservation *getReservation(string id) override;

    void exit() override;

    ~MyImplementation() override;
};

#endif //EX2_EX2_H
