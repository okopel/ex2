//
// Created by okopel on 11/25/18.
//

#include "ex2.h"


string AllId::generate(Jobs type) {
    string c;
    switch (type) {
        case MANAGER:
            c = 'm';
            break;
        case NAVIGATOR:
            c = 'n';
            break;
        case OTHER:
            c = 'o';
            break;
        case PILOT:
            c = 'p';
            break;
        case FLY_ATTENDANT:
            c = 'f';
            break;
        default:
            c = 'E';
    }
    return "" + c + "-" + to_string(this->getCount(type));
}

int AllId::getCount(Jobs type) {
    switch (type) {
        case MANAGER:
            this->mangers++;
            return this->mangers;
        case NAVIGATOR:
            this->navigators++;
            return this->navigators;

        case FLY_ATTENDANT:
            this->fly_attendant++;
            return this->fly_attendant;

        case PILOT:
            this->pilots++;
            return this->pilots;

        case OTHER:
            this->other++;
            return this->other;

        default:
            return -1;
    }
}

AllId::AllId(int managers, int navigators, int fly_attendant, int pilots, int other) {
    this->mangers = 0;
    this->navigators = 0;
    this->fly_attendant = 0;
    this->pilots = 0;
    this->other = 0;
}