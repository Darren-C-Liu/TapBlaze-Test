/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <cocos/ui/UIButton.h>
#include "TapBlazeWheelScene.h"

USING_NS_CC;

Scene* TapBlazeWheel::createScene()
{
    return TapBlazeWheel::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TapBlazeWheelScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TapBlazeWheel::init()
{
    //////////////////////////////
    // Super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

    // App header
    auto label = Label::createWithTTF("Tap Blaze Wheel", FONT, 18);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add in prize wheel
    auto wheelSprite = DrawWheel(visibleSize, origin);
    int probabilities[8] = { SECTOR_ONE_PROB, SECTOR_TWO_PROB, SECTOR_THREE_PROB, SECTOR_FOUR_PROB,
                             SECTOR_FIVE_PROB, SECTOR_SIX_PROB, SECTOR_SEVEN_PROB, SECTOR_EIGHT_PROB };
    prizeWheel8 = new PrizeWheel(8, wheelSprite, probabilities);
    CreateSpinButton(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5));

    return true;
}

/**
 * Create the prize wheel and add it to the scene
 */
Sprite * TapBlazeWheel::DrawWheel(cocos2d::Size visibleSize, cocos2d::Vec2 visibleOrigin) {
    //Create the wheel
    auto wheelSprite = Sprite::create(WHEEL_SECTIONS_8);
    wheelSprite->setPosition(Vec2(visibleSize.width/2 + visibleOrigin.x, visibleSize.height/2 + visibleOrigin.y));
    wheelSprite->setScale(RESIZE_SCALE);

    //Create the border
    auto wheelBorderSprite = Sprite::create(WHEEL_BORDER);
    wheelBorderSprite->setPosition(Vec2(visibleSize.width/2 + visibleOrigin.x, visibleSize.height/2 + visibleOrigin.y));
    wheelBorderSprite->setScale(RESIZE_SCALE);

    //Create the arrow
    auto wheelArrowSprite = Sprite::create(WHEEL_ARROW);
    wheelArrowSprite->setPosition(Vec2(visibleSize.width/2 + visibleOrigin.x, visibleSize.height*0.68));

    auto wheelWidth = wheelSprite->getContentSize().width;
    auto wheelHeight = wheelSprite->getContentSize().height;

    //Create each prize
    auto life = CreatePrize(HEART_SPRITE,
                            HEART_ANGLE,
                            Vec2(wheelWidth * 0.625, wheelHeight * 0.8),
                            HEART_LABEL);

    auto brushThree = CreatePrize(BRUSH_SPRITE,
                                  BRUSH_3_ANGLE,
                                  Vec2(wheelWidth*0.75,wheelHeight*0.6),
                                  BRUSH_3_LABEL);

    auto gemsSmall = CreatePrize(GEM_SPRITE,
                                 GEMS_SMALL_ANGLE,
                                 Vec2(wheelWidth*0.8,wheelHeight*0.4),
                                 GEMS_SMALL_LABEL);

    auto hammerThree = CreatePrize(HAMMER_SPRITE,
                                   HAMMER_3_ANGLE,
                                   Vec2(wheelWidth * 0.6, wheelHeight * 0.25),
                                   HAMMER_3_LABEL);

    auto coins = CreatePrize(COIN_SPRITE,
                             COINS_ANGLE,
                             Vec2(wheelWidth * 0.4, wheelHeight * 0.25),
                             COINS_LABEL);

    auto brushOne = CreatePrize(BRUSH_SPRITE,
                                BRUSH_1_ANGLE,
                                Vec2(wheelWidth * 0.2, wheelHeight * 0.4),
                                BRUSH_1_LABEL);

    auto gemsLarge = CreatePrize(GEM_SPRITE,
                                 GEMS_LARGE_ANGLE,
                                 Vec2(wheelWidth * 0.2, wheelHeight * 0.625),
                                 GEMS_LARGE_LABEL);

    auto hammerOne = CreatePrize(HAMMER_SPRITE,
                                 HAMMER_1_ANGLE,
                                 Vec2(wheelWidth * 0.375, wheelHeight * 0.8),
                                 HAMMER_1_LABEL);

    //Add all prizes to the wheel
    wheelSprite->addChild(life);
    wheelSprite->addChild(brushThree);
    wheelSprite->addChild(gemsSmall);
    wheelSprite->addChild(hammerThree);
    wheelSprite->addChild(coins);
    wheelSprite->addChild(brushOne);
    wheelSprite->addChild(gemsLarge);
    wheelSprite->addChild(hammerOne);

    //Add everything to the scene
    this->addChild(wheelSprite);
    this->addChild(wheelBorderSprite);
    this->addChild(wheelArrowSprite);

    //Return the wheel sprite
    return wheelSprite;
}

/**
 * Create the sprite for a prize with a label
 * @param spriteName - Filename of the sprite
 * @param rotation - Number of degrees to rotate the sprite
 * @param position - Position of the prize in relation to the wheel
 * @param labelText - Text to display on the prize
 * @return The finished sprite
 */
Sprite* TapBlazeWheel::CreatePrize(std::string spriteName, float rotation, Vec2 position, std::string labelText) {
    auto sprite = Sprite::create(spriteName);
    sprite->setRotation(rotation);
    sprite->setPosition(position);
    auto label = Label::createWithTTF(labelText, FONT, FONT_SIZE);
    label->enableOutline(Color4B::BLACK, 1);
    label->setPosition(Vec2(sprite->getContentSize().width * 0.5, 0));
    sprite->addChild(label);

    return sprite;
}

/**
 * Add the spin button to the scene
 * @param position - Where to place the button
 */
void TapBlazeWheel::CreateSpinButton(cocos2d::Vec2 position){
    //Create button and label
    auto spinButton = cocos2d::ui::Button::create(SPIN_BUTTON);
    auto spinButtonLabel = Label::createWithTTF(SPIN_BUTTON_TEXT, FONT, SPIN_BUTTON_TEXT_SIZE);
    spinButtonLabel->enableOutline(Color4B::BLACK, 1);
    spinButton->setTitleLabel(spinButtonLabel);
    spinButton->setPosition(position);
    spinButton->setScale(RESIZE_SCALE);

    //Add listeners to button
    spinButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                ButtonPressed();
                break;
            default:
                break;
        }
    });

    //Add button to the scene
    this->addChild(spinButton);
}

/**
 * When the button is pressed, spin the wheel if it exists
 */
void TapBlazeWheel::ButtonPressed(){
    if(prizeWheel8 != nullptr) {
        prizeWheel8->SpinWheel();
    }
}