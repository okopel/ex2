/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#ifndef EX2_EX2_H
#define EX2_EX2_H
#define EMP_FILE "Employee.txt"
#define CUS_FILE "Custemer.txt"
#define PLAN_FILE "Plans.txt"
#define RES_FILE "Reservation.txt"
#define FLY_FILE "Fly.txt"
#define SET_FILE "Setting.txt"

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "interface.h"

/**
 * enum of filesType - table
 */
enum LoadTableType {
    EMP, CUS, PLAN, FLY, RES, SETTING
};

class MyImplementation;

class IDgenerator;

class ResTable;

class EmploeeTable;

class FlightTable;

class MyCustomer;

class MyFlight;

/**
 * class of the impimention of ex2
 */
class MyImplementation : virtual public Ex2 {
    /**
     * company id generator
     */
    IDgenerator *company;
    /**
     * list of employees of the company
     */
    list<Employee *> employees;
    /**
     * * list of planes of the company
     */
    list<Plane *> planes;
    /**
     * * list of flies of the company
     */
    list<MyFlight *> flight;
    /**
 * list of Reservation of the company
 */
    list<Reservation *> reservs;
    /**
     * map of "has load" to avoid double loading
     */
    map<LoadTableType, bool> hasloaded;
    /**
     * list of mycustomer to some update
     */
    list<MyCustomer *> myCusList;
    /**
     * list of myFloight to some update
     */
    list<MyFlight *> myFlyList;


    void loadSetting();

    void saveSetting();

    /**
    * check for availible worker
    * @param emp specific worker
    * @param date specific date
    * @return treu if availible
    */
    bool isWorkerAvailible(const Employee *emp, const Date &date);

    /**
     * load table from file
     * @param num type of loading
     */
    void loadFromFile(const LoadTableType &num);

    /**
     * check if there is crew for flight
     * @param model mode of flight (in order to get nedded crew
     * @param date date
     * @return true if there is availible crew
     */
    bool checkForCrew(const int &model, const Date &date);

    /**
     * check for availible plan
     * @param date of flight
     * @param model of plan of flight
     * @return true if we have free plan
     */
    bool checkAvailiblePlanAndCrew(const Date &date, const int &model);


    /**
     * @return the whole workers who exist BY type
     */
    map<Jobs, int> existing();

    /**
     * the workers who busy at dat
     * @param date cpesific date
     * @return map of busy worker
     */
    map<Jobs, int> busyAtDate(const Date &date);

    /**
     * check availble of place
     * @param fly the required fly
     * @param cls the wanted class (first or economy)
     * @return true if there is place.
     */
    bool checkForPlaceInFlightInClass(Flight *fly, const Classes &cls);

    /**
     * nom of reservetaion in class in speifit date
     * @param date date
     * @param model model
     * @return num of exist reserv to check availble seat.
     */
    unsigned long getResPerDatePerModel(const Date &date, const int &model);

    /**
     * @param model model
     * @return num of planes of this model
     */
    int numOfPlanesFromModel(const int &model) const;

    /**
     * num of free seats in the model
     * @param model model
     * @param cls waned class
     * @return num of free seats
     */
    int numOfSeatsFromModel(const int &model, const Classes &cls);

    /**
     * num of catch seats
     * @param fly specific fly
     * @param cls wanted class
     * @return num of catch
     */
    int numOfCatch(Flight *fly, const Classes &cls);

public:
    /**
     * C-TOR.
     */
    explicit MyImplementation();

    /**
     * get plan by model num
     * @param model num
     * @return plan of this model
     */
    Plane *getPlaneByModel(const int &model);

    /**
    * enter work to new flight
    * @param crew  needed crew
    * @param date date of flight
    * @return list of worker to the flight
    */
    list<Employee *> *arrangeWorkers(map<Jobs, int> crew, Date &date);

    list<Employee *> &getEemployees();

    list<Plane *> &getPlanes();

    list<MyFlight *> &getFlight();

    list<MyCustomer *> &getCustomer();

    list<Reservation *> &getReservs();

    Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title) override;

    Employee *getEmployee(const string id) override;

    Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) override;

    Plane *getPlane(string id) override;

    Flight *addFlight(int model_number, Date date, string source, string destination) override;

    Flight *getFlight(string id) override;

    /**
     * get myFlight
     * @param id  strind of id
     * @return myflight pointer
     */
    MyFlight *getMyFlight(string id);

    Customer *addMyCustomer(string id, string name, int pri);

    Customer *addCustomer(string full_name, int priority) override;

    Customer *getCustomer(string id) override;

    /**
     * get myCustomer
     * @param id wanted id
     * @return mycustomer
     */
    MyCustomer *getMyCustomer(string id);

    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage) override;

    Reservation *getReservation(string id) override;

    void exit() override;

    ~MyImplementation() override;
};

#endif //EX2_EX2_H
