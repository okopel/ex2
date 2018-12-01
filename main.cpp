#include "interface.h"
#include "MyImplementation.h"

#include <iostream>
#include <fstream>

int session_number = 0;
const char *test_file = "testing.txt";

#ifndef TEST
#define TEST
const int titles_count = 5;
const Jobs titles_array[] = {MANAGER, PILOT, FLY_ATTENDANT, NAVIGATOR, OTHER};

#endif

const int classes_count = 2;
const Classes classes_array[] = {SECOND_CLASS, FIRST_CLASS};

int model1 = 1234;
int model2 = 4321;

int crew_map_1[] = {1, 0, 0, 1, 0};
int crew_map_2[] = {4, 1, 2, 0, 2};
int crew_map_3[] = {7, 1, 1, 1, 2};

int classes_map_1[] = {200, 20};
int classes_map_2[] = {3, 1};

void success(int counter) {
    printf("Session %d, test %d passed\n", session_number, counter);
}

void failure(int counter, const char *ext = "") {
    printf("Session %d, test %d failed %s\n", session_number, counter, ext);
}


map<Jobs, int> createCrewMap(int *arr) {
    map<Jobs, int> mp;
    for (int i = 0; i < titles_count; ++i) {
        mp.insert(pair<Jobs, int>(titles_array[i], arr[i]));
    }

    return mp;
}

map<Classes, int> createClassesMap(int *arr) {
    map<Classes, int> mp;
    for (int i = 0; i < classes_count; ++i) {
        mp.insert(pair<Classes, int>(classes_array[i], arr[i]));
    }
    return mp;
}

void empFactory(Ex2 *ex2, Jobs title, int num) {
    for (int i = 0; i < num; ++i) {
        ex2->addEmployee(5, 1950, "", title);
    }
}

void empFactory(Ex2 *ex2, map<Jobs, int> titles) {
    for (int i = 0; i < titles_count; ++i) {
        empFactory(ex2, titles_array[i], titles[titles_array[i]]);
    }
}

void resFactory(Ex2 *ex2, Classes cls, string flight_id, string cust_id, int num) {
    for (int i = 0; i < num; ++i) {
        ex2->addResevation(cust_id, flight_id, cls, 2);
    }

}

template<class T>
void *should_succeed(Ex2 *ex2, T func, int test_number) {
    void *result = NULL;
    try {
        result = func(ex2);
        success(test_number);
    }
    catch (...) {
        failure(test_number);
    }
    return result;
}

template<class T>
void should_succeed_bool(Ex2 *ex2, T func, int test_num) {
    try {
        if (func(ex2)) {
            success(test_num);
        }
        return;
    }
    catch (...) {
        failure(test_num, " - WRONG EXCEPTION");
    }
    failure(test_num, " - WRONG TEST");
}

template<class T>
void should_fail(Ex2 *ex2, T func, int test_number) {
    try {
        func(ex2);
        failure(test_number);
    }
    catch (...) {
        success(test_number);
    }
}


void simple_test1(Ex2 *ex2) {
    int counter = 0;
    // invalid priority
    should_fail(ex2, [](Ex2 *ex2) { ex2->addCustomer("John Hayha", 7); }, counter++);
    should_succeed(ex2, [](Ex2 *ex2) { return (void *) ex2->addCustomer("John Hayha", 4); }, counter++);
    // add employee - no employer
    Employee *emp = (Employee *) should_succeed(ex2, [](Ex2 *ex2) {
        return (void *) ex2->addEmployee(4, 6, "", titles_array[0]);
    }, counter++);
    ofstream file(test_file, ios_base::trunc);
    file << emp->getID() << endl;
    file.close();
    // add plane
    should_succeed(ex2, [](Ex2 *ex2) {
        return (void *) ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1));
    }, counter++);
}

void simple_test2(Ex2 *ex2) {
    string id;
    ifstream file(test_file, ios_base::in);
    file >> id;
    file.close();

    int counter = 0;
    Employee *emp = (Employee *) should_succeed(ex2, [id](Ex2 *ex2) {
        return (void *) ex2->addEmployee(4, 6, id, titles_array[3]);
    }, counter++);
    should_succeed_bool(ex2, [id, emp](Ex2 *ex2) {
        return emp->getEmployer()->getID() == id;
    }, counter++);

}

void test3(Ex2 *ex2) {

    int counter = 0;
    Flight *flight = (Flight *) should_succeed(ex2, [](Ex2 *ex2) {
        return (void *) ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN");
    }, counter++);
    ofstream file(test_file, ios_base::out | ios_base::trunc);

    file << flight->getID() << endl;

    int verifier = 0;

    auto assigned_c = flight->getAssignedCrew();

    for (auto it = assigned_c.begin(); it != assigned_c.end(); ++it, ++verifier) {
        if (verifier > 2) {
            failure(counter++);
        }
        file << (*it)->getID() << endl;
    }

    file.close();
}

void test4(Ex2 *ex2) {
    int counter = 0;
    string ids[3];
    ifstream file(test_file, ios_base::in);
    for (int i = 0; i < 3; ++i) file >> ids[i];
    file.close();

    Flight *flight = (Flight *) should_succeed(ex2, [ids](Ex2 *ex2) { return (void *) ex2->getFlight(ids[0]); },
                                               counter++);
    list<Employee *> crew = flight->getAssignedCrew();
    if (crew.size() != 2) {
        failure(counter++);
    } else {
        string ids2[2];
        auto itr = crew.begin();
        ids2[0] = (*itr++)->getID();
        ids2[1] = (*itr)->getID();

        bool check1 = (ids2[0] == ids[1]) && (ids2[1] == ids[2]);
        bool check2 = (ids2[0] == ids[2]) && (ids2[1] == ids[1]);
        if (check1 || check2) {
            success(counter++);
        } else {
            failure(counter++);
        }

    }

    should_fail(ex2, [](Ex2 *ex2) { return (void *) ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); },
                counter++);
    should_succeed(ex2, [](Ex2 *ex2) { return (void *) ex2->addFlight(model1, Date("2019-10-11"), "ARL", "VAN"); },
                   counter++);
}

void test5(Ex2 *ex2) {
    int counter = 0;
    should_succeed(ex2, [](Ex2 *ex2) {
        empFactory(ex2, createCrewMap(crew_map_1));
        return nullptr;
    }, counter++);
    should_fail(ex2, [](Ex2 *ex2) { return (void *) ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); },
                counter++);
    // NOTE THAT I SENT model1+1, so the plane is of wrong model!!
    should_succeed(ex2, [](Ex2 *ex2) {
        return (void *) ex2->addPlane(model1 + 1, createCrewMap(crew_map_1), createClassesMap(classes_map_1));
    }, counter++);
    should_fail(ex2, [](Ex2 *ex2) { return (void *) ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); },
                counter++);

    should_succeed(ex2, [](Ex2 *ex2) {
        return (void *) ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1));
    }, counter++);
    should_succeed(ex2, [](Ex2 *ex2) { return (void *) ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); },
                   counter++);
}


void (*tests[])(Ex2 *) = {simple_test1, simple_test2, test3, test4, test5};

const int tests_number = 5;

class Tester {
    int session_number;
public:
    void operator()(int session_number) {
        Ex2 *ex2 = new MyImplementation();
        tests[session_number](ex2);
        ex2->exit();
        delete ex2;
    }
};


int main(int argc, char *argv[]) {
#ifdef DELETE_FIRST
    // Make sure to delete all of your database files before
    // you start my tests! You don't want old data to interfere
#endif
    Tester t;
    for (int i = 0; i < tests_number; ++i) {
        session_number = i;
        t(i);
    }

    return 0;


}