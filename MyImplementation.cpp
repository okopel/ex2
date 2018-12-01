/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
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
    return emp;
}

Employee *MyImplementation::getEmployee(const string id) {
    this->loadFromFile(EMP);
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &employee : this->employees) {
        if (employee->getID() == id) {
            return employee;
        }
    }
    return nullptr;

}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    this->loadFromFile(PLAN);
    Plane *mp = new myPlane(model_number, max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS), crew_needed,
                            this->company);
    this->planes.push_back(mp);
    return mp;
}

Plane *MyImplementation::getPlane(string id) {
    this->loadFromFile(PLAN);
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
    this->loadFromFile(PLAN);
    this->loadFromFile(EMP);
    this->loadFromFile(FLY);
    if (!this->checkAvailiblePlanAndCrew(date, model_number)) {
        throw "There isn't free plan or free crew";
    }
    list<Employee *> *l = this->arrangeWorkers(this->getPlaneByModel(model_number)->getCrewNeeded(), date);
    MyFlight *mf = new MyFlight(model_number, date, source, destination, this->company, *l);
    Flight *myFlight = mf;
    this->schedule->addToMap(mf->getID(), l);
    mf->setTeam(l);

    delete l;

    this->flight.push_back(mf);
    return myFlight;
}

Flight *MyImplementation::getFlight(string id) {
    //we need plans, fliight and employee to build flight.
    this->loadFromFile(PLAN);
    this->loadFromFile(EMP);
    this->loadFromFile(FLY);

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
    if (priority > 5 || priority < 0) {
        throw "error in priority";
    }
    this->loadFromFile(CUS);
    MyCustomer *myCusto = new MyCustomer(full_name, priority, this->company);
    Customer *y = myCusto;
    this->myCusList.push_back(myCusto);
    return y;

}

Customer *MyImplementation::getCustomer(string id) {
    this->loadFromFile(CUS);
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &cust : this->myCusList) {
        if (cust->getID() == id) {
            return cust;
        }
    }
    return nullptr;
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    this->loadFromFile(CUS);
    this->loadFromFile(PLAN);
    this->loadFromFile(FLY);
    this->loadFromFile(RES);
    Flight *fly = this->getMyFlight(flightId);
    if (fly == nullptr) {
        throw "there isn't that fly ID:" + flightId;
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
    MyCustomer *myCus = this->getMyCustomer(customerId);
    myCus->addReserv(myres);
    MyFlight *mf = this->getMyFlight(flightId);
    mf->addReserv(myres);
    return myres;
}

Reservation *MyImplementation::getReservation(string id) {
    this->loadFromFile(CUS);
    this->loadFromFile(PLAN);
    this->loadFromFile(FLY);
    this->loadFromFile(RES);
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
    if (!this->employees.empty()) {
        Table<Employee> *emp = new EmployeeTable(this->employees);
        emp->saveTable(EMP_FILE);
        delete emp;
    }
    if (!this->planes.empty()) {
        Table<Plane> *plan = new PlanTable(this->planes);
        plan->saveTable(PLAN_FILE);
        delete plan;
    }
    if (!this->reservs.empty()) {
        Table<Reservation> *res = new ResTable(this->reservs);
        res->saveTable(RES_FILE);
        delete res;
    }
    if (!this->myCusList.empty()) {
        Table<MyCustomer> *cust = new CusTable(this->myCusList);
        cust->saveTable(CUS_FILE);
        delete cust;
    }
    if (!this->flight.empty()) {
        Table<MyFlight> *fly = new FlightTable(this->flight);
        fly->saveTable(FLY_FILE);
        this->schedule->save();

        delete fly;
    }

    this->saveSetting();
}


list<Employee *> &MyImplementation::getEemployees() {
    return this->employees;
}

list<Plane *> &MyImplementation::getPlanes() {
    return this->planes;
}

list<MyFlight *> &MyImplementation::getFlight() {
    return this->flight;
}

list<MyCustomer *> &MyImplementation::getCustomer() {
    return this->myCusList;
}

list<Reservation *> &MyImplementation::getReservs() {
    return this->reservs;
}

MyImplementation::MyImplementation() {
    /**
     * inition of id generator
     */
    this->company = new IDgenerator(0, 0, 0, 0, 0);
    this->schedule = new Schedule();
    bool b = this->loadSetting();
    //b is true if there are files to load.
    this->hasloaded.insert(std::pair<LoadTableType, bool>(EMP, !b));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(CUS, !b));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(PLAN, !b));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(FLY, !b));
    this->hasloaded.insert(std::pair<LoadTableType, bool>(RES, !b));
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
    return existing[PILOT] - busy[PILOT] >= needded[PILOT];
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
        exist[emp->getTitle()]++;
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
    switch (num) {
        case EMP: {
            EmployeeTable table(this->employees);
            if (table.loadTable(EMP_FILE, this)) {
                this->employees = table.getTlist();
            }

            break;
        }
        case CUS: {
            CusTable table2(this->myCusList);
            table2.loadTable(CUS_FILE, this);
            this->myCusList = table2.getTlist();
            break;
        }
        case PLAN: {
            PlanTable table3(this->planes);
            table3.loadTable(PLAN_FILE, this);
            this->planes = table3.getTlist();
            break;
        }
        case FLY: {
            this->schedule->load();
            FlightTable table4(this->flight);
            table4.loadTable(FLY_FILE, this);
            this->flight = table4.getTlist();
            break;
        }
        case RES: {
            ResTable table5(this->reservs);
            table5.loadTable(RES_FILE, this);
            this->reservs = table5.getTlist();
            break;
        }
        default:
            throw "Error in loading type";
    }
    this->hasloaded.at(num) = true;
}

bool MyImplementation::isWorkerAvailible(const Employee *emp, const Date &date) {
    for (auto const &fly : this->flight) {
        if (fly->getDate() == date) {
            for (auto const &tmp: fly->getAssignedCrew()) {
                if (tmp == emp) {
                    return false;
                }
            }
        }
    }
    return true;
}

list<Employee *> *MyImplementation::arrangeWorkers(map<Jobs, int> crew, Date date) {
    list<Employee *> *list = new ::list<Employee *>();
    for (auto *emp : this->employees) {
        if (crew[emp->getTitle()] > 0) {
            if (this->isWorkerAvailible(emp, date)) {
                list->push_back(emp);

                crew[emp->getTitle()]--;

            }
        }
    }
    return list;
}

MyCustomer *MyImplementation::getMyCustomer(string id) {
    if (id.empty()) {
        return nullptr;
    }
    for (auto const &cust : this->myCusList) {
        if (cust->getID() == id) {
            return cust;
        }
    }
    return nullptr;
}

MyFlight *MyImplementation::getMyFlight(string id) {
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

Customer *MyImplementation::addMyCustomer(string id, string name, int pri) {
    MyCustomer *myCusto = new MyCustomer(id, name, pri);
    Customer *y = myCusto;
    this->myCusList.push_back(myCusto);
    return y;
}

bool MyImplementation::loadSetting() {
    string s;
    ifstream myfile;
    myfile.open(SET_FILE);
    if (!myfile.is_open()) {
        return false;
    }
    getline(myfile, s);
    std::istringstream iss(s);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    this->company->set(stoi(results.at(0)), stoi(results.at(1)), stoi(results.at(2)), stoi(results.at(3)),
                       stoi(results.at(4)));

    myfile.close();
    return true;


}

void MyImplementation::saveSetting() {
    ofstream myfile;
    myfile.open(SET_FILE);
    if (!myfile.is_open()) {
        throw "Error in saving";
    }
    myfile << to_string(this->company->getMangers()) + " " + to_string(this->company->getNavigators()) + " " +
              to_string(this->company->getFly_attendant()) +
              " " + to_string(this->company->getPilots()) + " " + to_string(this->company->getOther());

    myfile.close();
}

MyImplementation::~MyImplementation() {
    delete this->company;
    delete this->schedule;
    for (auto *x:this->flight) {
        delete x;
    }
    for (auto *x:this->myCusList) {
        delete x;
    }
    for (auto *x:this->employees) {
        delete x;
    }
    for (auto *x:this->planes) {
        delete x;
    }
    for (auto *x:this->reservs) {
        delete x;
    }

}

void MyImplementation::addToSche(string flyId, string empId) {
    this->schedule->addToMap(flyId, empId);
}

Schedule *MyImplementation::getSchedule() {
    return this->schedule;
}


