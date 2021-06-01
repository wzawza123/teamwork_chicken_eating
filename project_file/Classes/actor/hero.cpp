//
//  hero.cpp
//  PUBG
//
//  Created by wza 2021-5-26
//

#include "hero.h"
hero::hero()
{
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    scheduleUpdate();
    bindSprite(Sprite::create("player.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    delegateSprite->setPosition(Point(100, 200));
}
void hero::setMovingState(int state)
{
    currentMovingState = state;
}
void hero::moveUpdate(float delta)
{
    log("called move update");
    log("currentMovingState:%d", currentMovingState);
    if (!canMove)
    {
        return;
    }
    calculateMoveVec();
    Point currentPosition = delegateSprite->getPosition();
    Point movePosition = currentPosition;
    MoveBy* move_up = MoveBy::create(delta, Point(0, actorConsts::moveDistance));
    /*switch (currentMovingState)
    {
        case actorConsts::ms_up:
            movePosition.y += actorConsts::moveDistance;
            break;
        case actorConsts::ms_down:
            movePosition.y -= actorConsts::moveDistance;
            break;
        case actorConsts::ms_left:
            movePosition.x -= actorConsts::moveDistance;
            break;
        case actorConsts::ms_right:
            movePosition.x += actorConsts::moveDistance;
            break;
        default:
            break;
    }*/
    log("x:%d y:%d", currentPosition.x, currentPosition.y);
    //delegateSprite->setPosition(movePosition);
    MoveBy* move = MoveBy::create(delta, moveVec*actorConsts::moveDistance);
    delegateSprite->runAction(move);
}
void hero::processJump()
{
}
int hero::getMovingState()const
{
    return currentMovingState;
}
void hero::stopMoving()
{
    currentMovingState = actorConsts::ms_standing;
}
void hero::update(float dt)
{
    moveUpdate(dt);    //»ÀŒÔŒª÷√µƒ∏¸–¬
}
void hero::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    log("key %d up", keycode);
    /*if (currentMovingState == actorConsts::ms_standing)
    {
        return;
    }
    if (keycode == actorConsts::directionKeyCode[currentMovingState])
    {
        stopMoving();
    }*/
	for (int i = 1; i <= 4; ++i)
	{
		if (keycode == actorConsts::directionKeyCode[i])
		{
			pressedKey[i] = false;
		}
	}
}
void hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    float moveTime = 0.01f;
    cocos2d::MoveBy* moveUp = cocos2d::MoveBy::create(moveTime, Point(0, actorConsts::moveDistance));
    cocos2d::MoveBy* moveDown = cocos2d::MoveBy::create(moveTime, Point(0, -actorConsts::moveDistance));
    cocos2d::MoveBy* moveLeft = cocos2d::MoveBy::create(moveTime, Point(-actorConsts::moveDistance, 0));
    cocos2d::MoveBy* moveRight = cocos2d::MoveBy::create(moveTime, Point(actorConsts::moveDistance, 0));
    log("key %d down", keycode);
    /*switch (keycode)
    {
        
        case EventKeyboard::KeyCode::KEY_W:
            setMovingState(actorConsts::ms_up);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            setMovingState(actorConsts::ms_down);
            break;
        case EventKeyboard::KeyCode::KEY_A:
            setMovingState(actorConsts::ms_left);
            break;
        case EventKeyboard::KeyCode::KEY_D:
            setMovingState(actorConsts::ms_right);
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            processJump();
            break;
        default:
            break;
    }*/
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        
    }
    else
    {
        
        for (int i = 1; i <= 4; ++i)
        {
            if (keycode == actorConsts::directionKeyCode[i])
            {
                pressedKey[i] = true;
            }
        }
    }
    //player.moveUpdate();
}
void hero::calculateMoveVec()
{
    moveVec = Point(0, 0);
    for (int i = 1; i <= 4; ++i)
    {
        if (pressedKey[i])
        {
            moveVec += actorConsts::moveVec[i];
        }
    }
}