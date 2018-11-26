//
// Created by okopel on 11/26/18.
//

#include "ex2.h"

int main() {
    AllId company(0, 0, 0, 0, 0);
    MyEx2 my(company);
    my.addEmployee(2, 1994, "", MANAGER);
    my.addEmployee(4, 1974, "", PILOT);
    my.addEmployee(5, 1850, "", FLY_ATTENDANT);
    my.addEmployee(7, 1950, "", PILOT);
    my.addEmployee(1, 1840, "", FLY_ATTENDANT);
    my.addEmployee(0, 1999, "", NAVIGATOR);
    my.addEmployee(19, 2019, "", NAVIGATOR);

    my.addCustomer("ori kopel", 3);
    my.addCustomer("shlomo", 5);
    my.addCustomer("moshe", 6);
    my.addCustomer("dowi", 1);
    my.addCustomer("renana", 6);
    my.addCustomer("nushnushit", 6);

    my.addFlight(975, Date("2018-11-25"), "israel", "usa");
    my.addFlight(125, Date("2019-01-25"), "Poland", "greece");
    my.addFlight(99965, Date("2019-01-26"), "USA", "greece");
    my.addFlight(8865, Date("2019-02-02"), "london", "israel");
    my.addFlight(6005, Date("2019-01-13"), "Poland", "berlin");
    my.addFlight(6065, Date("2019-01-13"), "Poland", "berlin");
    my.addResevation("o-1", "o-3", FIRST_CLASS, 2);
    my.addResevation("o-2", "o-4", FIRST_CLASS, 2);
    my.addResevation("o-3", "o-1", SECOND_CLASS, 2);
    my.addResevation("o-4", "o-2", FIRST_CLASS, 2);
    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 100));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, 10));
    crew.insert(std::pair<Jobs, int>(PILOT, 1));
    map<Classes, int> clas;
    clas.insert(std::pair<Classes, int>(FIRST_CLASS, 12));
    clas.insert(std::pair<Classes, int>(SECOND_CLASS, 1));
    my.addPlane(123, crew, clas);
    my.addPlane(153, crew, clas);
    my.addPlane(3333, crew, clas);
    my.addPlane(993, crew, clas);
    my.addPlane(3363, crew, clas);
    my.addPlane(1113, crew, clas);


    flightTable t(my.getFlight());
    EmploeeTable e(my.getEemployees());
//    e.printTable();
    e.saveTable(EMP_FILE);
    e.loadTable(EMP_FILE);
    cout << "d";
    return 0;
}
