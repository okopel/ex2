//
// Created by okopel on 11/25/18.
//
#include "ex2.h"


bool Date::operator<(const Date &d) const {

    string thisDate = this->date.substr(0, 4);
    string otherDate = d.date.substr(0, 4);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }

    thisDate = this->date.substr(5, 2);
    otherDate = d.date.substr(5, 2);
    if (thisDate < otherDate) {
        return true;
    } else if (thisDate < otherDate) {
        return false;
    }
    thisDate = this->date.substr(8, 2);
    otherDate = d.date.substr(8, 2);
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

Date::Date(string date) {
    this->date = date;
}