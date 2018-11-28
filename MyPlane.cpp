/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/

#include "MyPlane.h"
#include "IDgenerator.h"

myPlane::myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> &neededCrew, IDgenerator *company)
        : model(model),
          maxFirstClass(
                  maxFirstClass),
          maxSecondClass(
                  maxSecondClass) {
    this->neededCrew = this->arrangeCrew(neededCrew);
    this->id = company->generate(OTHER);
}

myPlane::~myPlane() = default;

int myPlane::getModelNumber() {
    return this->model;
}

map<Jobs, int> myPlane::getCrewNeeded() {
    return this->neededCrew;
}

int myPlane::getMaxFirstClass() {
    return this->maxFirstClass;
}

int myPlane::getMaxEconomyClass() {
    return this->maxSecondClass;
}

string myPlane::getID() {
    return this->id;
}

myPlane::myPlane(const string &id, int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> &neededCrew) : id(
        id),
                                                                                                                   model(model),
                                                                                                                   maxFirstClass(
                                                                                                                           maxFirstClass),
                                                                                                                   maxSecondClass(
                                                                                                                           maxSecondClass),
                                                                                                                   neededCrew(
                                                                                                                           neededCrew) {


}

map<Jobs, int> &myPlane::arrangeCrew(map<Jobs, int> &map) {
    if (map.count(FLY_ATTENDANT) == 0) {
        map.insert(std::pair<Jobs, int>(FLY_ATTENDANT, 0));
    }
    if (map.count(MANAGER) == 0) {
        map.insert(std::pair<Jobs, int>(MANAGER, 0));
    }
    if (map.count(NAVIGATOR) == 0) {
        map.insert(std::pair<Jobs, int>(NAVIGATOR, 0));
    }
    if (map.count(PILOT) == 0) {
        map.insert(std::pair<Jobs, int>(PILOT, 0));
    }
    if (map.count(OTHER) == 0) {
        map.insert(std::pair<Jobs, int>(OTHER, 0));
    }
    return map;

}
