//
// Created by okopel on 11/25/18.
//
#include "MyImplementation.h"


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
    //format: YYYY-MM-DD
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day > 31 || day < 1) {
        cout << "Error in date!" << endl;
        return;
    }

    this->date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
}