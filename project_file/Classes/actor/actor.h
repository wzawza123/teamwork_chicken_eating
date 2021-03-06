//
//  actor.h
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#ifndef actor_h
#define actor_h
#include<cocos2d.h>
#include "const.h"
//#include "scene/SingleModeRuntimeScene.h"    include进来会导致hero类报错

//class SingleModeRuntime;
using namespace cocos2d;
using namespace actorConsts;
class actor:public Node
{
private:
public:


    
    Sprite* delegateSprite;
    actor();
    static int getHealthPoint();
    static int getDefencePoint();
    bool doDamage(int attackPoint);
    Vec2 getSpritePosition();
    //Animate* actor::walkingAnimation();
protected:
    bool canMove;
    bool isInvincible;
    bool isWalking=false;
    float moveSpeedRatio;
    static int sHealthPoint;
    static int sDefencePoint;
    int sActorType;
    void bindSprite(Sprite* sprite);
    bool bindPhysicalBody();
    Animate* actor::createAnimation(const char* animationName, const char* actorName);
};
#endif
