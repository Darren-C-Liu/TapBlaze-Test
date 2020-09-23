//
// Created by Darren Liu on 9/20/2020.
//

#include "PrizeWheel.h"
#include "Definitions.h"

USING_NS_CC;

/**
 * Prize Wheel Constructor
 * @param num - Number of sectors in the wheel
 * @param sprite - Sprite for the wheel with the prizes added
 * @param probabilities - Array with the drop rates of each prize
 */
PrizeWheel::PrizeWheel(int num, cocos2d::Sprite * sprite, int probabilities[])
{
    numSectors = num;
    wheelSprite = sprite;
    sectorProb = new int[num];

    for(int i = 0; i < num; i++){
        sectorProb[i] = probabilities[i];
    }
}

/**
 * Spin the Prize Wheel
 */
void PrizeWheel::SpinWheel() {
    wheelSprite->setRotation(0);

    auto spinAction = RotateBy::create(NUM_SPINS, NUM_SPINS * 360);

    auto sector = RandomSector();
    auto sectorAngle = 360 / numSectors;
    auto rotate = 360 - (sectorAngle * (sector - 1)) - (sectorAngle / 2);
    auto endAction = RotateBy::create(0.5, rotate);

    auto sequenceAction = Sequence::create(spinAction, endAction, NULL);
    wheelSprite->runAction(sequenceAction);

    TestRandomSector();
}


/**
 * Select a Random Sector
 * @return The randomly selected sector number
 */
int PrizeWheel::RandomSector() {
    int random = cocos2d::RandomHelper::random_int(1, 100);

    for(int i = 0; i < numSectors; i++){
        if(random <= sectorProb[i]){
            return i + 1;
        }
        else{
            random -= sectorProb[i];
        }
    }

    return numSectors;
}

/**
 * Unit Test for the RandomSector
 * Runs RandomSector 1000 times and prints the results for each sector
 */
void PrizeWheel::TestRandomSector() {
    int sector;
    int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for(int i = 0; i < 1000; i++){
        sector = RandomSector();
        count[sector - 1]++;
    }

    CCLOG("Sector 1 (Life 30 min): %i (~%i percent)", count[0], (int)(((double)count[0] / 1000) * 100));
    CCLOG("Sector 2 (Brush 3X): %i (~%i percent)", count[1], (int)(((double)count[1] / 1000) * 100));
    CCLOG("Sector 3 (Gems 35): %i (~%i percent)", count[2], (int)(((double)count[2] / 1000) * 100));
    CCLOG("Sector 4 (Hammer 3X): %i (~%i percent)", count[3], (int)(((double)count[3] / 1000) * 100));
    CCLOG("Sector 5 (Coins 750): %i (~%i percent)", count[4], (int)(((double)count[4] / 1000) * 100));
    CCLOG("Sector 6 (Brush 1X): %i (~%i percent)", count[5], (int)(((double)count[5] / 1000) * 100));
    CCLOG("Sector 7 (Gems 75): %i (~%i percent)", count[6], (int)(((double)count[6] / 1000) * 100));
    CCLOG("Sector 8 (Hammer 1X): %i (~%i percent)", count[7], (int)(((double)count[7] / 1000) * 100));
}