//
// Created by Darren Liu on 9/20/2020.
//

#ifndef PROJ_ANDROID_PRIZEWHEEL_H
#define PROJ_ANDROID_PRIZEWHEEL_H

#include "Definitions.h"
#include "cocos2d.h"

using namespace cocos2d;

class PrizeWheel {
public:
    PrizeWheel(int num, Sprite * sprite, int probabilities[]);
    void SpinWheel();

private:
    int RandomSector();
    void TestRandomSector();
    int numSectors;
    Sprite *wheelSprite;
    int *sectorProb;

};


#endif //PROJ_ANDROID_PRIZEWHEEL8_H
