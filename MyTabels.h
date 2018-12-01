/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#ifndef EX2_MYTABELS_H
#define EX2_MYTABELS_H

#include "MyImplementation.h"
#include "Schedule.h"

/**
 * class of tables in order to save and load from files to our DB
 * @tparam T the wanted table(employee or custemer etc.
 */
template<typename T>
class Table {
protected:
    /**
     * list of string(after casting)
     */
    std::list<string> slist;
    /**
     * list of T (before casting)
     */
    std::list<T *> list;

    /**
     * replace space to underline on order to save name in one word
     * @param text the text
     * @return text with underscore
     */
    string space2underscore(string text);

    /**
     * recovery the spaces
     * @param text text
     * @return with spaces
     */
    string underscore2space(string text);

public:
    virtual std::list<T *> &getTlist();

    /**
     * save table in file
     * @param file file name
     */
    virtual void saveTable(const string &file);

    /**
     * D-tor
     */
    virtual ~Table();

    /**
     * load table from file
     * @param file the file name
     * @param lists the DB
     */
    virtual bool loadTable(const string &file, MyImplementation *lists);

    /**
     * make our list as string
     */
    virtual void listToStringList();

    /**
     * make one T as string
     * @param tmp the T
     * @return string of the date
     */
    virtual string makeString(T *tmp) = 0;

    /**
     * parser to T
     * @param s the string
     * @param lists the DB
     * @return T
     */
    virtual T *loadFromString(const string &s, MyImplementation *lists) = 0;

    /**
     * castong from string to JOB
     * @param s the string
     * @return the job
     */
    Jobs stringToJobs(const string &s) const;

};


class FlightTable : public Table<MyFlight> {
public:
    explicit FlightTable(std::list<MyFlight *> &list);

    MyFlight *loadFromString(const string &s, MyImplementation *lists) override;

    std::list<Employee *> *stringToEmp(std::list<string> l, MyImplementation *lists);

    string makeString(MyFlight *tmp) override;

    void printTable();
};


class EmployeeTable : virtual public Table<Employee> {
public:
    explicit EmployeeTable(std::list<Employee *> &list);

    void printTable();

    string makeString(Employee *tmp) override;

    Employee *findBoss(const string &s);

    ~EmployeeTable() override;

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

class CusTable : virtual public Table<MyCustomer> {


public:

    explicit CusTable(std::list<MyCustomer *> &list);

    string makeString(MyCustomer *tmp) override;

    MyCustomer *loadFromString(const string &s, MyImplementation *lists) override;

};

#endif //EX2_MYTABELS_H
