//
// Created by okopel on 11/22/18.
//
#include "ex2.h"

myPlane::myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> neededCrew, AllId company)
        : model(model),
          maxFirstClass(
                  maxFirstClass),
          maxSecondClass(
                  maxSecondClass), neededCrew(
                neededCrew) {
    this->id = company.generate(OTHER);
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