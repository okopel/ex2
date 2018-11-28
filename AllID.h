//
// Created by okopel on 11/28/18.
//

#ifndef EX2_ALLID_H
#define EX2_ALLID_H

class AllId {
    int mangers;
    int navigators;
    int fly_attendant;
    int pilots;
    int other;
public:
    explicit AllId(int managers = 0, int navigators = 0, int fly_attendant = 0, int pilots = 0, int other = 0);

    string generate(Jobs type);

    int getCount(Jobs type);
};

#endif //EX2_ALLID_H
