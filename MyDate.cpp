/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/
#include "MyImplementation.h"

/**
 * Implimation of date
 * @param other the date
 * @return if date<other date
 */
bool Date::operator<(const Date &other) const {

    string thisDate = this->date.substr(0, 4);
    string otherDate = other.date.substr(0, 4);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }

    thisDate = this->date.substr(5, 2);
    otherDate = other.date.substr(5, 2);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }
    thisDate = this->date.substr(8, 2);
    otherDate = other.date.substr(8, 2);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }
    return false;
}

bool Date::operator>(const Date &d) const {
    return !((this < &d) || (this == &d));
}

bool Date::operator==(const Date &d) const {
    return (this->date == d.date);
}

/**
 * Ctor
 * @param date the string of the date
 */
Date::Date(string date) {
    if (date.length() != 10) {
        throw "Error in date";
    }
    //format: YYYY-MM-DD
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day > 31 || day < 1) {
        throw "Error in date";
    }

    this->date = date.substr(0, 4) + "-" + date.substr(5, 2) + "-" + date.substr(8, 2);
}