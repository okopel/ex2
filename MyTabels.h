//
// Created by okopel on 11/27/18.
//

#ifndef EX2_MYTABELS_H
#define EX2_MYTABELS_H

#include "ex2.h"

template<typename T>
class Table {
protected:
    std::list<string> slist;
    std::list<T *> list;
public:
    virtual void saveTable(const string &file);

    virtual void loadTable(const string &file, MyEx2 *lists);

    virtual void listToStringList();

    virtual string makeString(T *tmp) = 0;

    virtual T *loadFromString(const string &s, MyEx2 *lists) = 0;

    Jobs stringToJobs(const string &s) const;

};


class flightTable : public Table<Flight> {
public:
    explicit flightTable(std::list<Flight *> &list);

    Flight *loadFromString(const string &s, MyEx2 *lists) override;

    string makeString(Flight *tmp) override;

    void printTable();
};


class EmploeeTable : virtual public Table<Employee> {
public:
    explicit EmploeeTable(std::list<Employee *> &list);

    void printTable();

    string makeString(Employee *tmp) override;

    Employee *findBoss(const string &s);

    Employee *loadFromString(const string &s, MyEx2 *lists) override;
};

class PlanTable : virtual public Table<Plane> {
public:
    explicit PlanTable(std::list<Plane *> &list);

    string makeString(Plane *tmp) override;

    void printTable();

    Plane *loadFromString(const string &s, MyEx2 *lists) override;
};

class ResTable : virtual public Table<Reservation> {
public:
    explicit ResTable(std::list<Reservation *> &list);

    string makeString(Reservation *tmp) override;

    Reservation *loadFromString(const string &s, MyEx2 *lists) override;
};

#endif //EX2_MYTABELS_H
