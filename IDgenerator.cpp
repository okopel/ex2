/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyImplementation.h"
#include "IDgenerator.h"

/**
 * generate new ID
 * @param type type of wanted ID
 * @return new ID
 */
string IDgenerator::generate(Jobs type) {
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

/**
 * inner func of generator
 * @param type
 * @return
 */
int IDgenerator::getCount(Jobs type) {
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

IDgenerator::IDgenerator(int managers, int navigators, int fly_attendant, int pilots, int other) {
    this->mangers = 0;
    this->navigators = 0;
    this->fly_attendant = 0;
    this->pilots = 0;
    this->other = 0;
}

void IDgenerator::set(int managers, int navigators, int fly_attendant, int pilots, int other) {
    this->mangers = managers;
    this->navigators = navigators;
    this->fly_attendant = fly_attendant;
    this->pilots = pilots;
    this->other = other;
}

int IDgenerator::getMangers() const {
    return mangers;
}

int IDgenerator::getNavigators() const {
    return navigators;
}

int IDgenerator::getFly_attendant() const {
    return fly_attendant;
}

int IDgenerator::getPilots() const {
    return pilots;
}

int IDgenerator::getOther() const {
    return other;
}
