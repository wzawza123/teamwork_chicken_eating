//
//  SingleModeRuntimeScence.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef SingleModeRuntimeScene_h
#define SingleModeRuntimeScene_h

//#pragma once
#include "cocos2d.h"
#include "Box2D.h"
#include "actor/hero.h"
#include "actor/enemy.h"
#include "gizmos/SimpleAudioEngine.h"
//#include "actor/actor.h"


USING_NS_CC;
//class actor;
class SingleModeRuntime : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    hero player;
    //HeroUI heroUI;
    
    void menuPauseCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    static void scheduleBlood(float delta);
    
    void groundMusicPlay();
    
    void setCneterPointOfView();
    
    void update(float dt);
    
    //UI更新
    //void scheduleUI(float dt);
    
    
    //暂停界面回调
    //void pauseByKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    
    CREATE_FUNC(SingleModeRuntime);
    
    b2World * world;
    
    TMXTiledMap *testMap;

protected:
    
    ProgressTimer* pHealth;
    ProgressTimer* pArmor;

    Label* pBullet1Message;
    Label* pBullet2Message;
    Label* pBullet3Message;
    Label* pBullet4Message;
    
    MenuItemImage* pauseItem;

    /*
    int sHealthPoint;
    int maxHealthPoint;
    int sArmorPoint;
    int maxArmorPoint;
    int pBullet1;
    int maxBullet1;
    int pBullet2;
    int maxBullet2;
    int pBullet3;
    int maxBullet3;
    int pBullet4;
    int maxBullet4;
    */
};


#endif /* SingleModeRuntimeScence_h */
