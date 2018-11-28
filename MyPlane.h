/*****************
 * Ori Kopel
 * 205533151
 * ex2 - nov 2018
 ****************/


#ifndef EX2_MYPLANE_H
#define EX2_MYPLANE_H

#include "MyImplementation.h"

/**
 * impliment of plane
 */
class myPlane : virtual public Plane {
    int model;
    int maxFirstClass;
    int maxSecondClass;
    map<Jobs, int> neededCrew;
    string id;

    /**
     * arange crew on plan
     * @param map
     * @return
     */
    map<Jobs, int> &arrangeCrew(map<Jobs, int> &map);

public:
    myPlane(int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> &neededCrew, IDgenerator *company);

    myPlane(const string &id, int model, int maxFirstClass, int maxSecondClass, map<Jobs, int> &neededCrew);

    string getID() override;

    int getModelNumber() override;

    map<Jobs, int> getCrewNeeded() override;

    int getMaxFirstClass() override;

    int getMaxEconomyClass() override;

    ~myPlane() override;
};

#endif //EX2_MYPLANE_H
