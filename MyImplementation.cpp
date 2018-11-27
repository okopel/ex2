#include <iostream>
#include "MyImplementation.h"
#include "MyTabels.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyReservation.h"
#include "MyFlight.h"
#include "MyPlane.h"

Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    this->loadFromFile(EMP);
    Employee *boss = this->getEmployee(employer_id);
    Employee *emp = new MyEmployee(title, seniority, birth_year, boss, this->company);
    this->employees.push_back(emp);
    return this->getEmployee(emp->getID());
}

Employee *MyImplementation::getEmployee(const string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &employee : this->employees) {
        if (employee->getID() == (id)) { continue; }
        return employee;
    }
    return nullptr;

}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    this->loadFromFile(PLAN);
    Plane *mp = new myPlane(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
                            this->company);
    this->planes.push_back(mp);
    return this->getPlane(mp->getID());
}

Plane *MyImplementation::getPlane(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &plane : this->planes) {
        if (plane->getID() == id) {
            return plane;
        }
    }
    return nullptr;
}

Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    this->loadFromFile(FLY);
    this->loadFromFile(EMP);
    if (!this->checkAvailiblePlanAndCrew(date, model_number)) {
        throw "There isn't free plan or free crew";
    }
    Flight *myFlight = new MyFlight(model_number, date, source, destination, this->company);
    this->flight.push_back(myFlight);
    //todo update employee list

    return myFlight;
}

Flight *MyImplementation::getFlight(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &flight : this->flight) {
        if (flight->getID() == id) {
            return flight;
        }
    }
    return nullptr;
}

Customer *MyImplementation::addCustomer(string full_name, int priority) {
    this->loadFromFile(CUS);

    Customer *myCustomer = new MyCustomer(full_name, priority, this->company);
    this->customer.push_back(myCustomer);
    return this->getCustomer(myCustomer->getID());
}

Customer *MyImplementation::getCustomer(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &cust : this->customer) {
        if (cust->getID() == id) {
            return cust;
        }
    }
    return nullptr;
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    this->loadFromFile(RES);
    this->loadFromFile(FLY);
    this->loadFromFile(CUS);
    Flight *fly = this->getFlight(flightId);
    if (fly == nullptr) {
        throw "there isnt that fly ID:" + flightId;
    }
    if (!this->checkForPlaceInFlightInClass(fly, cls)) {
        throw "There is not place in this fly";
    }
    Customer *cus = this->getCustomer(customerId);
    if (cus == nullptr) {
        throw "There is not customer:" + customerId;
    }
    Reservation *myres = new MyReservation(cus, fly, max_baggage, cls, this->company);
    this->reservs.push_back(myres);
    cus->getReservations().push_back(myres);//update cus res list.
    fly->getReservations().push_back(myres);//update fly res list.
    return myres;
}

Reservation *MyImplementation::getReservation(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &res : this->reservs) {
        if (res->getID() == id) {
            return res;
        }
    }
    return nullptr;
}

void MyImplementation::exit() {
    Table<Employee> *emp = new EmploeeTable(this->employees);
    emp->saveTable(EMP_FILE);
    Table<Plane> *plan = new PlanTable(this->planes);
    plan->saveTable(PLAN_FILE);
    Table<Reservation> *res = new ResTable(this->reservs);
    res->saveTable(RES_FILE);
    Table<Customer> *cust = new CusTable(this->customer);
    cust->saveTable(CUS_FILE);
    Table<Flight> *fly = new flightTable(this->flight);
    fly->saveTable(FLY_FILE);

}

MyImplementation::~MyImplementation() = default;

list<Employee *> &MyImplementation::getEemployees() {
    return this->employees;
}

list<Plane *> &MyImplementation::getPlanes() {
    return this->planes;
}

list<Flight *> &MyImplementation::getFlight() {
    return this->flight;
}

list<Customer *> &MyImplementation::getCustomer() {
    return this->customer;
}

list<Reservation *> &MyImplementation::getReservs() {
    return this->reservs;
}

MyImplementation::MyImplementation() {
    this->company = new AllId(0, 0, 0, 0, 0);
    this->hasloaded.insert(std::pair<LoadTableType, bool>(EMP, false));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(CUS, false));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(PLAN, false));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(FLY, false));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(RES, false));
}

bool MyImplementation::checkAvailiblePlanAndCrew(const Date &date, const int &model) {
    //check for free plan
    int res = (int) this->getResPerDatePerModel(date, model);
    int plan = this->numOfPlanesFromModel(model);
    //if there are 1 free plan at least to do this resev (not >= becouse we want 1 free plan).
    if (plan <= res) {
        return false;
    }
    //check for free crew
    if (!this->checkForCrew(model, date)) {
        return false;
    }
    return true;
}

unsigned long MyImplementation::getResPerDatePerModel(const Date &date, const int &model) {
    list<Flight *> list;
    for (auto const &res : this->flight) {
        if ((res->getDate() == date) && (res->getModelNumber() == model)) {
            list.push_back(res);
        }
    }
    return list.size();
}


bool MyImplementation::checkForCrew(const int &model, const Date &date) {
    map<Jobs, int> needded;
    for (auto const &plan : this->planes) {
        if (plan->getModelNumber() == model) {
            needded = plan->getCrewNeeded();
            break;
        }
    }
    if (needded.empty()) {
        //there isnt model.
        return false;
    }
    map<Jobs, int> busy = this->busyAtDate(date);
    map<Jobs, int> existing = this->existing();

    if ((existing[MANAGER] - busy[MANAGER]) < needded[MANAGER]) {
        return false;
    }
    if ((existing[FLY_ATTENDANT] - busy[FLY_ATTENDANT]) < needded[FLY_ATTENDANT]) {
        return false;
    }
    if ((existing[NAVIGATOR] - busy[NAVIGATOR]) < needded[NAVIGATOR]) {
        return false;
    }
    if ((existing[OTHER] - busy[OTHER]) < needded[OTHER]) {
        return false;
    }
    if ((existing[PILOT] - busy[PILOT]) < needded[PILOT]) {
        return false;
    }
    return true;
}

Plane *MyImplementation::getPlaneByModel(const int &model) {
    for (auto const &plane : this->planes) {
        if (plane->getModelNumber() == model) {
            return plane;
        }
    }
    return nullptr;
}

map<Jobs, int> MyImplementation::busyAtDate(const Date &date) {
    map<Jobs, int> busy;
    for (auto const &fly : this->flight) {
        if (fly->getDate() == date) {
            map<Jobs, int> thisPlanCrew = this->getPlaneByModel(fly->getModelNumber())->getCrewNeeded();
            busy[MANAGER] += thisPlanCrew[MANAGER];
            busy[FLY_ATTENDANT] += thisPlanCrew[FLY_ATTENDANT];
            busy[NAVIGATOR] += thisPlanCrew[NAVIGATOR];
            busy[OTHER] += thisPlanCrew[OTHER];
            busy[PILOT] += thisPlanCrew[PILOT];
        }
    }
    return busy;
}

map<Jobs, int> MyImplementation::existing() {
    map<Jobs, int> exist;
    for (auto const &emp : this->employees) {
        exist[emp->getTitle()]++;//todo check if new title is adding
    }
    return exist;
}

bool MyImplementation::checkForPlaceInFlightInClass(Flight *fly, const Classes &cls) {
    int places = this->numOfSeatsFromModel(fly->getModelNumber(), cls);
    int numOfCatch = this->numOfCatch(fly, cls);
    return (places > numOfCatch);
}

int MyImplementation::numOfSeatsFromModel(const int &model, const Classes &cls) {
    if (cls == SECOND_CLASS) {
        return this->getPlaneByModel(model)->getMaxEconomyClass();
    } else {
        return this->getPlaneByModel(model)->getMaxFirstClass();
    }
}

int MyImplementation::numOfCatch(Flight *fly, const Classes &cls) {
    int counter = 0;
    for (auto const &res : fly->getReservations()) {
        if (res->getClass() == cls) {
            counter++;
        }
    }
    return counter;
}

int MyImplementation::numOfPlanesFromModel(const int &model) const {
    int counter = 0;
    for (auto const &plan : this->planes) {
        if (plan->getModelNumber() == model) {
            counter++;
        }
    }
    return counter;
}


void MyImplementation::loadFromFile(const LoadTableType &num) {
    //check if the value has already loaded.
    if (this->hasloaded.at(num)) {
        return;
    }
    string file;
    switch (num) {
        case EMP: {
            Table<Employee> *table = new EmploeeTable(this->employees);
            file = EMP_FILE;
            table->loadTable(file, this);
            break;
        }
        case CUS: {
            Table<Customer> *table2 = new CusTable(this->customer);
            file = CUS_FILE;
            table2->loadTable(file, this);
            break;
        }
        case PLAN: {
            Table<Plane> *table3 = new PlanTable(this->planes);
            file = PLAN_FILE;
            table3->loadTable(file, this);
            break;
        }
        case FLY: {
            Table<Flight> *table4 = new flightTable(this->flight);
            file = FLY_FILE;
            table4->loadTable(file, this);
            break;
        }
        case RES: {
            Table<Reservation> *table5 = new ResTable(this->reservs);
            file = RES_FILE;
            table5->loadTable(file, this);
            break;
        }
        default:
            throw "Error in loading type";
    }
    this->hasloaded.at(num) = true;

}


