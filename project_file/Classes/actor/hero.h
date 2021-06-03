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
#include "actor/actor.h"
//#include "general/general.h"
using namespace cocos2d;

class hero :public actor
{
public:
    static int heroCount;
    int index;
    bool isJumping;
    bool canJump;
    hero(int x=200,int y=300);
    Vec2 getMovingState()const;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
    
    int currentMovingState;
    Vec2 moveVec;
    Vec2 lastVec;   //保存上个时刻的速度，供翻身使用
    bool pressedKey[5] = { 0 };
    void moveUpdate(float delta);
    void stopMoving();
    void update(float delta) override;
    void calculateMoveVec();
    void doJump();
    void stopJump(float dt);
    void jumpRecover(float dt);
};


#endif /* hero_h */
