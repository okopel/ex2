//
// Created by okopel on 11/28/18.
//

#ifndef EX2_ALLID_H
#define EX2_ALLID_H

/**
 * Class that generate new ID for new CUST/RESERV etc
 */
class IDgenerator {
    int mangers;
    int navigators;
    int fly_attendant;
    int pilots;
    int other;

    /**
    * get the cur num of type.
    * @param type
    * @return
    */
    int getCount(Jobs type);

public:
    /**
     * CTOR
     * there is option to value in order to make it intersting id (at least 4 digit etc.
     * @param managers 0
     * @param navigators 0
     * @param fly_attendant 0
     * @param pilots 0
     * @param other 0
     */
    explicit IDgenerator(int managers = 0, int navigators = 0, int fly_attendant = 0, int pilots = 0, int other = 0);

    int getMangers() const;

    int getNavigators() const;

    int getFly_attendant() const;

    int getPilots() const;

    int getOther() const;

    void set(int managers = 0, int navigators = 0, int fly_attendant = 0, int pilots = 0, int other = 0);

    /**
     * generate ID
     * @param type
     * @return
     */
    string generate(Jobs type);

};

#endif //EX2_ALLID_H
