//
// Created by okopel on 12/1/18.
//

#ifndef EX2_SCHEDULE_H
#define EX2_SCHEDULE_H


//
// Created by okopel on 12/1/18.
//

#include <fstream>
#include "interface.h"

#define  SCHED_FILE "DB_Schedule.txt"

class Schedule {
    map<string, std::list<string>> schedule;

public:
    void addToMap(string flyId, list<Employee *> *empId);

    bool empty();

    void addToMap(string flyId, string empId);

    list <string> getEmpOfFly(string flyId);

    string get();

    void save();

    void load();
};


#endif //EX2_SCHEDULE_H
