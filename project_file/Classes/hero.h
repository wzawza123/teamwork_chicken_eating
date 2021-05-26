//
//  hero.h
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#ifndef hero_h
#define hero_h

#pragma once
#include<cocos2d.h>
#include "const.h"
using namespace cocos2d;
class hero :public cocos2d::Node
{
public:
    hero();
    
    int getMovingState()const;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
    void bindSprite(cocos2d::Sprite* sprite);
    int currentMovingState;
    cocos2d::Sprite* delegateSprite;
    void setMovingState(int state);
    void moveUpdate();
    void stopMoving();
    void update(float delta) override;
};

#endif /* hero_h */
