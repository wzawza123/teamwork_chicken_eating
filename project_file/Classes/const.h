//
//  const.h
//  PUBG
//
//  Created by PC1 on 2021/5/23.
//

#ifndef const_h
#define const_h

#pragma once
#include <cocos2d.h>
using namespace cocos2d;
//class hero
//const float moveTime = 3.0f;
const int moveDistance = 3;
enum movingState { ms_standing, ms_up, ms_down, ms_left, ms_right };
const EventKeyboard::KeyCode directionKeyCode[5] = {
        EventKeyboard::KeyCode::KEY_0,
        EventKeyboard::KeyCode::KEY_W,
        EventKeyboard::KeyCode::KEY_S,
        EventKeyboard::KeyCode::KEY_A,
        EventKeyboard::KeyCode::KEY_D
};
//int BLOOD_BAR=1;
//int PLAYER_LIFE=100;
#endif /* const_h */
