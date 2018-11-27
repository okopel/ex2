//
// Created by okopel on 11/26/18.
//

#include "MyImplementation.h"
#include "MyTabels.h"

int main() {
    MyImplementation my;
    my.addEmployee(2, 1994, "", MANAGER);
    my.addEmployee(2, 1914, "", MANAGER);
    my.addEmployee(2, 1094, "", MANAGER);
    my.addEmployee(2, 1900, "", MANAGER);
    my.addEmployee(3, 1994, "", MANAGER);
    my.addEmployee(4, 1974, "", PILOT);
    my.addEmployee(5, 1850, "", FLY_ATTENDANT);
    my.addEmployee(7, 1950, "m-4", PILOT);
    my.addEmployee(1, 1840, "m-1", FLY_ATTENDANT);
    my.addEmployee(0, 1999, "m-4", NAVIGATOR);
    my.addEmployee(19, 2019, "m-1", NAVIGATOR);

    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 2));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew.insert(std::pair<Jobs, int>(PILOT, 1));
    map<Classes, int> clas;
    clas.insert(std::pair<Classes, int>(FIRST_CLASS, 102));
    clas.insert(std::pair<Classes, int>(SECOND_CLASS, 19));
    my.addPlane(123, crew, clas);
    my.addPlane(153, crew, clas);
    my.addPlane(3333, crew, clas);
    my.addPlane(993, crew, clas);
    my.addPlane(3363, crew, clas);
    my.addPlane(1113, crew, clas);

    my.addCustomer("ori kopel", 3);
    my.addCustomer("shlomo", 5);
    my.addCustomer("moshe", 6);
    my.addCustomer("dowi", 1);
    my.addCustomer("renana", 6);
    my.addCustomer("nushnushit", 6);

    my.addFlight(123, Date("2018-11-25"), "israel", "usa");
    my.addFlight(153, Date("2019-01-25"), "Poland", "greece");
    my.addFlight(3333, Date("2019-01-26"), "USA", "greece");
    my.addFlight(153, Date("2019-02-02"), "london", "israel");
    my.addFlight(993, Date("2019-01-13"), "Poland", "berlin");
    my.addFlight(1113, Date("2019-01-13"), "Poland", "berlin");
    my.addResevation("o-1", "o-13", FIRST_CLASS, 2);
    my.addResevation("o-2", "o-14", FIRST_CLASS, 2);
    my.addResevation("o-3", "o-15", SECOND_CLASS, 2);
    my.addResevation("o-4", "o-16", FIRST_CLASS, 2);


    flightTable t(my.getFlight());
    EmploeeTable e(my.getEemployees());
//    e.printTable();
    e.saveTable(EMP_FILE);
    e.loadTable(EMP_FILE, &my);
    cout << "Good Job!";
    return 0;
}
