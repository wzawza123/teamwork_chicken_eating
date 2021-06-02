//
//  hero.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#include "hero.h"

/*
hero::hero()
{
    canMove = true;
    isInvincible = false;
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    scheduleUpdate();
    bindSprite(Sprite::create("sprite.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    
    //设置hero的物理模型
        delegateSprite->setPosition(Point(100, 200));
        PhysicsBody* heroPhysicsBody = PhysicsBody::createBox(Size(this->getContentSize()));
        heroPhysicsBody->setDynamic(true);
        heroPhysicsBody->setCategoryBitmask(1);
        heroPhysicsBody->setCollisionBitmask(1);
        heroPhysicsBody->setContactTestBitmask(1);
        
        this->delegateSprite->setPhysicsBody(heroPhysicsBody);
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


void hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    switch (keycode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            delegateSprite->getPhysicsBody()->setVelocity(Vec2(0,100));
            break;
        case EventKeyboard::KeyCode::KEY_S:
            delegateSprite->getPhysicsBody()->setVelocity(Vec2(0,-100));
            break;
        case EventKeyboard::KeyCode::KEY_A:
            delegateSprite->getPhysicsBody()->setVelocity(Vec2(-100,0));
            break;
        case EventKeyboard::KeyCode::KEY_D:
            delegateSprite->getPhysicsBody()->setVelocity(Vec2(100,0));
            break;
        default:
            break;
    }
}



void hero::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    log("key %d up", keycode);
    delegateSprite->getPhysicsBody()->setVelocity(Vec2(0,0));
}

    //player.moveUpdate();

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
}*/

hero::hero()
{
    isJumping = false;
    canJump = true;
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    
    scheduleUpdate();
    sActorType = at_null;
    bindSprite(Sprite::create("hero.png"));
    bindPhysicalBody();
    delegateSprite->setContentSize(Size(40,40));
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
    //log("called move update");
    //log("currentMovingState:%d", currentMovingState);
    if (!canMove)
    {
        return;
    }
    calculateMoveVec();
    Point currentPosition = delegateSprite->getPosition();
    Point movePosition = currentPosition;
    MoveBy* move_up = MoveBy::create(delta, Point(0, actorConsts::moveDistance));
    //log("x:%d y:%d", currentPosition.x, currentPosition.y);
    //MoveBy* move = MoveBy::create(delta, moveVec*actorConsts::moveDistance);
    //delegateSprite->runAction(move);
    //unitizeVec(&moveVec);
    //log("v:%f,%f", moveVec.x, moveVec.y);
    delegateSprite->getPhysicsBody()->setVelocity(moveVec * moveDistance * moveSpeedRatio);
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
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        log("pressed space");
        doJump();
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
void hero::doJump()
{
    if (!isJumping&&canJump)
    {
        isJumping = true;
        isInvincible = true;
        canJump = false;
        moveSpeedRatio *= jumpMoveSpeedRatio;
        delegateSprite->setScale(jumpScale);
        scheduleOnce(CC_SCHEDULE_SELECTOR(hero::stopJump), jumpTime);
    }
}
void hero::stopJump(float dt)
{
    log("stop jumping");
    isJumping = false;
    isInvincible = false;
    moveSpeedRatio /= jumpMoveSpeedRatio;
    log("%f", moveSpeedRatio);
    delegateSprite->setScale(1);
    scheduleOnce(CC_SCHEDULE_SELECTOR(hero::jumpRecover), jumpCD);
}
void hero::jumpRecover(float dt)
{
    canJump = true;
}

