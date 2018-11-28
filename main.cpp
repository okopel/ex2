/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyImplementation.h"
#include "MyTabels.h"

int main() {

    Ex2 *my = new MyImplementation();  // This line must work!

    my->addEmployee(2, 1994, "", MANAGER);
    my->addEmployee(2, 1914, "", MANAGER);
    my->addEmployee(2, 1094, "", MANAGER);
    my->addEmployee(2, 1900, "", MANAGER);
    my->addEmployee(3, 1994, "", MANAGER);
    my->addEmployee(4, 1974, "", PILOT);
    my->addEmployee(5, 1850, "", FLY_ATTENDANT);
    my->addEmployee(7, 1950, "m-4", PILOT);
    my->addEmployee(1, 1840, "m-1", FLY_ATTENDANT);
    my->addEmployee(0, 1999, "m-4", NAVIGATOR);
    my->addEmployee(19, 2019, "m-1", NAVIGATOR);

    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 2));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew.insert(std::pair<Jobs, int>(PILOT, 1));
    map<Classes, int> classSeats;
    classSeats.insert(std::pair<Classes, int>(FIRST_CLASS, 102));
    classSeats.insert(std::pair<Classes, int>(SECOND_CLASS, 19));
    my->addPlane(123, crew, classSeats);
    my->addPlane(153, crew, classSeats);
    my->addPlane(3333, crew, classSeats);
    my->addPlane(993, crew, classSeats);
    my->addPlane(3363, crew, classSeats);
    my->addPlane(1113, crew, classSeats);

    my->addCustomer("ori kopel", 3);
    my->addCustomer("shlomo", 5);
    my->addCustomer("moshe", 6);
    my->addCustomer("dowi", 1);
    my->addCustomer("renana", 6);
    my->addCustomer("nushnushit", 6);

    my->addFlight(123, Date("2018-11-25"), "israel", "los angeles");
    my->addFlight(153, Date("2019-01-25"), "Poland", "greece");
    my->addFlight(3333, Date("2019-01-26"), "USA", "greece");
    my->addFlight(153, Date("2019-02-02"), "london", "israel");
    my->addFlight(993, Date("2019-01-13"), "Poland", "berlin");
    my->addFlight(1113, Date("2019-01-13"), "Poland", "berlin");
    my->addResevation("o-7", "o-13", FIRST_CLASS, 2);
    my->addResevation("o-8", "o-14", FIRST_CLASS, 2);
    my->addResevation("o-9", "o-15", SECOND_CLASS, 2);
    my->addResevation("o-10", "o-16", FIRST_CLASS, 2);

    my->exit();

    Ex2 *my2 = new MyImplementation();
    my2->addCustomer("kok", 99);
    my2->addEmployee(5, 2020, "", PILOT);
    my2->addPlane(23, crew, classSeats);
    my2->addResevation("o-7", "o-13", SECOND_CLASS, 1);
    my2->addFlight(3333, Date("2014-05-08"), "givaat shmuel A", "ze good yaaad");

    my2->exit();

}
