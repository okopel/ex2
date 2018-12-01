/******************************************************
Change log:
4.0
Submission date is postponed until Sunday, 2018-12-02
3.0
Added getter to Date class
Virtual destructor to ID class
*******************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <list>
#include <string>

using namespace std;


enum Jobs {
	MANAGER, NAVIGATOR, FLY_ATTENDANT, PILOT, OTHER
};
enum Classes {
	FIRST_CLASS, SECOND_CLASS
};


class ID {
public:
	virtual string getID() = 0;

	virtual ~ID() {}
};


class Employee;
class Plane;
class Flight;
class Customer;
class Reservation;
class Date;

class Employee : public ID {
public:
	virtual int getSeniority() = 0;

	virtual int getBirthYear() = 0;

	virtual Employee *getEmployer() = 0;
    virtual Jobs getTitle() = 0;

	virtual ~Employee() {}
};

class Plane : public ID {
public:
	virtual int getModelNumber() = 0;

	virtual map<Jobs, int> getCrewNeeded() = 0;

	virtual int getMaxFirstClass() = 0;

	virtual int getMaxEconomyClass() = 0;

	virtual ~Plane() {}
};

class Flight : public ID {
public:
	virtual int getModelNumber() = 0;

	virtual list<Reservation *> getReservations() = 0;

	virtual list<Employee *> getAssignedCrew() = 0;

	virtual Date getDate() = 0;

	virtual string getSource() = 0;

	virtual string getDestination() = 0;

	virtual ~Flight() {}
};


class Customer : public ID {
public:
	virtual string getFullName() = 0;

	virtual int getPriority() = 0;

	virtual list<Reservation *> getReservations() = 0;

	virtual ~Customer() {}
};


class Reservation : public ID {
public:
	virtual Customer *getCustomer() = 0;

	virtual Flight *getFlight() = 0;

	virtual Classes getClass() = 0;

	virtual int getMaxBaggage() = 0;

	virtual ~Reservation() {}
};


class Date {
    string date;
public:
	string getDate() const { return date; }
    Date(string date);    // format: YYYY-MM-DD
	bool operator<(const Date &d) const;

	bool operator>(const Date &d) const;

	bool operator==(const Date &d) const;
};


class Ex2 {
public:
	virtual Employee *addEmployee(
			int seniority,
			int birth_year,
			string employer_id,
			Jobs title) = 0;

	virtual Employee *getEmployee(string id) = 0;

	virtual Plane *addPlane(
			int model_number,
			map<Jobs, int> crew_needed,
			map<Classes, int> max_passangers) = 0;

	virtual Plane *getPlane(string id) = 0;

	virtual Flight *addFlight(
			int model_number,
			Date date,
			string source,
			string destination) = 0;

	virtual Flight *getFlight(string id) = 0;

	virtual Customer *addCustomer(
			string full_name,
			int priority) = 0;

	virtual Customer *getCustomer(string id) = 0;

	virtual Reservation *addResevation(
			string customerId,
			string flightId,
			Classes cls,
			int max_baggage) = 0;

	virtual Reservation *getReservation(string id) = 0;

	virtual void exit() = 0;

	virtual ~Ex2() {}
};

#endif