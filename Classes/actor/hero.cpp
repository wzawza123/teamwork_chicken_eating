//
//  hero.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/25.
//

#include "hero.h"

int hero::heroCount = 0;

hero::hero(int x,int y)
{
    index = heroCount++;
    isJumping = false;
    canJump = true;
    currentMovingState = actorConsts::ms_standing;
    moveVec = Point(0, 0);
    //绑定键盘监听器
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    
    scheduleUpdate();
    sActorType = at_player;
    bindSprite(Sprite::create("hero.png"));
    bindPhysicalBody();
    delegateSprite->setContentSize(Size(40,40));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for hero===================== ");
    }
    delegateSprite->setPosition(Point(x,y));
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
    if (fabs(moveVec.x) > 1e-6)
    {
        if (moveVec.x < 0)
        {
            delegateSprite->runAction(ScaleTo::create(0.f, -1.0f, 1.0f));
        }
        else
        {
            delegateSprite->runAction(ScaleTo::create(0.f, 1.0f, 1.0f));
        }
    }

    log("location x:%d y:%d", delegateSprite->getPosition().x, delegateSprite->getPosition().y);
}


void hero::stopMoving()
{
    currentMovingState = actorConsts::ms_standing;
}
void hero::update(float dt)
{
    SetWeaponPosition();
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
        //log("pressed space");
        doJump();
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_R)//换子弹的实现
    {
        log("Add bullet to my weapon.");
        myMainWeapon->changeBulletamount(2);
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_E)//拾取物品
    {
        log("pick something");
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_F)//更换武器
    {
        log("Begin to change weapon");
        changeWeapon();
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
    float length = sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);
    if (fabs(length) > 1e-6)
    {
        moveVec.x /= length;
        moveVec.y /= length;
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
        int rotateDegree = moveVec.x > 0 ? 360 : -360;
        delegateSprite->runAction(RotateBy::create(jumpTime, rotateDegree));
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

bool hero::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    log("=========+++++++++++++++++++++++++++++++++++=========");

    if (nodeA->getTag() == tagConsts::tagBullet|| nodeB->getTag() == tagConsts::tagBullet)
    {
        this->sHealthPoint - 10;
    }
    if (nodeA->getTag() == tagConsts::tagBarrier || nodeB->getTag() == tagConsts::tagBarrier)
    {
        this->getPhysicsBody()->setVelocity(Vec2::ZERO);
    }
    return true;
}

void hero::setMainWeapon(Weapon* pNewWeapon)
{
    myMainWeapon = pNewWeapon;
    pNewWeapon->setState(true);
}

void hero::SetWeaponPosition()
{
    if (myMainWeapon != nullptr)
    {
        myMainWeapon->HeroPosition = this->getSpritePosition();
    }
    if (mySecondWeapon != nullptr)
    {
        mySecondWeapon->HeroPosition = this->getSpritePosition();
    }

}

Weapon* hero::getMyMainWeapon()
{
    return myMainWeapon;
}

Weapon* hero::pickWeapon(Weapon* pNewWeapon)
{
    if (pNewWeapon->getState() == false) //判断武器是否被持有，若未被持有则可以拾取
    {
        pNewWeapon->setState(true);
        if (myMainWeapon != nullptr && mySecondWeapon == nullptr)//主武器不为空,副武器为空
        {
            mySecondWeapon = myMainWeapon;
            mySecondWeapon->setVisible(false);
            myMainWeapon = pNewWeapon;
        }
        else if (myMainWeapon == nullptr)//主武器为空（相当于没有武器）
        {
            myMainWeapon = pNewWeapon;
        }
        else//主副武器都满了
        {
            auto temp = myMainWeapon;
            temp->setState(false);
            temp->setPosition(this->getPosition());
            myMainWeapon = pNewWeapon;
        }
    }
    return myMainWeapon;
}

void hero::changeWeapon()
{
    if (myMainWeapon != nullptr && mySecondWeapon != nullptr)
    {
        log("Change successfully!");
        auto temp = myMainWeapon;
        myMainWeapon = mySecondWeapon;
        mySecondWeapon = temp;
        myMainWeapon->setVisible(true);
        mySecondWeapon->setVisible(false);
    }
}

void hero::setSecondWeapon(Weapon* pNewWeapon)
{
    mySecondWeapon = pNewWeapon;
    mySecondWeapon->setVisible(false);
    mySecondWeapon->setState(true);
}