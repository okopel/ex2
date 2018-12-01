#include <iterator>
#include <vector>
#include <sstream>
#include "Schedule.h"

void Schedule::addToMap(string flyId, list<Employee *> *list1) {
    std::list<string> *list2;
    if (this->schedule.count(flyId) != 0) {
        list2 = &this->schedule.at(flyId);
    } else {
        list2 = new std::list<string>;
    }
    for (auto tmp : *list1) {
        list2->push_back(tmp->getID());
    }
    this->schedule.erase(flyId);
    this->schedule.insert(std::pair<string, std::list<string>>(flyId, *list2));
    delete list2;
}

list<string> Schedule::getEmpOfFly(string flyId) {
    return this->schedule.at(flyId);
}

void Schedule::addToMap(string flyId, string empId) {
    std::list<string> list;
    if (this->schedule.count(flyId) != 0) {
        list = this->schedule.at(flyId);
    }

    list.push_back(empId);
    this->schedule.erase(flyId);
    this->schedule.insert(std::pair<string, std::list<string>>(flyId, list));
}

string Schedule::get() {
    if (this->schedule.empty()) {
        return "";
    }
    auto m = this->schedule.begin();

    string flyId = m->first;
    list<string> l = m->second;
    string s = "";
    for (auto tmp : l) {
        s += (flyId + " " + tmp + "\n");
    }
    this->schedule.erase(flyId);
    return s;

}

bool Schedule::empty() {
    return (this->schedule.empty());
}

void Schedule::save() {
    ofstream myfile;
    myfile.open(SCHED_FILE);
    if (!myfile.is_open()) {
        throw "Error in saving";
    }
    string s = this->get();
    while (!s.empty()) {
        myfile << s;
        s = this->get();
    }
    myfile.close();
}

void Schedule::load() {
    string s = "1";
    ifstream myfile;
    myfile.open(SCHED_FILE);
    if (!myfile.is_open()) {
        return;
    }
    while (!s.empty()) {
        s = "";
        getline(myfile, s);
        if (!s.empty()) {
            std::istringstream iss(s);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                             std::istream_iterator<std::string>());
            string flyid = results.at(0);
            string empId = results.at(1);
            this->addToMap(flyid, empId);
        }
    }
    myfile.close();


}
