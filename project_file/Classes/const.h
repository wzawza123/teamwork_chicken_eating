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
namespace actorConsts
{
	enum actorType
	{
		at_null, at_player,at_enemy
	};
	const int sizeOfContext[2][2] = { {0,0},{48,48} }; //width height
	const int moveDistance = 100;
	const Point moveVec[5] = { Point(0,0),Point(0,1),Point(0,-1),Point(-1,0),Point(1,0) };
	enum movingState {ms_standing, ms_up, ms_down, ms_left, ms_right };
	const EventKeyboard::KeyCode directionKeyCode[5] = {
			EventKeyboard::KeyCode::KEY_0,
			EventKeyboard::KeyCode::KEY_W,
			EventKeyboard::KeyCode::KEY_S,
			EventKeyboard::KeyCode::KEY_A,
			EventKeyboard::KeyCode::KEY_D
	};
}
//int BLOOD_BAR=1;
//int PLAYER_LIFE=100;
#endif /* const_h */
