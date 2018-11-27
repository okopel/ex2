//
// Created by okopel on 11/27/18.
//

#ifndef EX2_MYTABELS_H
#define EX2_MYTABELS_H

#include "MyImplementation.h"

template<typename T>
class Table {
protected:
    std::list<string> slist;
    std::list<T *> list;
public:
    virtual void saveTable(const string &file);

    virtual ~Table();

    virtual void loadTable(const string &file, MyImplementation *lists);

    virtual void listToStringList();

    virtual string makeString(T *tmp) = 0;

    virtual T *loadFromString(const string &s, MyImplementation *lists) = 0;

    Jobs stringToJobs(const string &s) const;

};


class FlightTable : public Table<Flight> {
public:
    explicit FlightTable(std::list<Flight *> &list);

    Flight *loadFromString(const string &s, MyImplementation *lists) override;

    string makeString(Flight *tmp) override;

    void printTable();
};


class EmploeeTable : virtual public Table<Employee> {
public:
    explicit EmploeeTable(std::list<Employee *> &list);

    void printTable();

    string makeString(Employee *tmp) override;

    Employee *findBoss(const string &s);

    ~EmploeeTable() override;

    Employee *loadFromString(const string &s, MyImplementation *lists) override;
};

class PlanTable : virtual public Table<Plane> {
public:
    explicit PlanTable(std::list<Plane *> &list);

    string makeString(Plane *tmp) override;

    Plane *loadFromString(const string &s, MyImplementation *lists) override;
};

class ResTable : virtual public Table<Reservation> {
public:
    explicit ResTable(std::list<Reservation *> &list);

    string makeString(Reservation *tmp) override;

    ~ResTable() override;

    Reservation *loadFromString(const string &s, MyImplementation *lists) override;
};

class CusTable : virtual public Table<Customer> {

    string space2underscore(string text);

    string underscore2space(string text);

public:

    explicit CusTable(std::list<Customer *> &list);

    string makeString(Customer *tmp) override;

    Customer *loadFromString(const string &s, MyImplementation *lists) override;

};

#endif //EX2_MYTABELS_H
