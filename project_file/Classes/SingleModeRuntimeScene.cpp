//
//  SingleModeRunTimeScence.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#include "HelloWorldScene.h"
#include "SingleModeRuntimeScene.h"
#include "PauseScene.h"
#include "const.h"

USING_NS_CC;

Scene* SingleModeRuntime::createScene()
{

    auto scene = Scene::createWithPhysics();
    auto layer = SingleModeRuntime::create();
    scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool SingleModeRuntime::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    //地图
    TMXTiledMap *testMap = TMXTiledMap::create("textMap.tmx");
    this->addChild(testMap);
   
    addChild(&ene);
    addChild(&player);
    //监听键盘
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //创建一个事件监听器监听键盘事件
    keyListener->onKeyPressed = CC_CALLBACK_2(hero::onKeyPressed, &player);
    //键盘被按下时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(hero::onKeyReleased,&player);
    //键盘按键被弹回时响应
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    //设置更新函数
    scheduleUpdate();
    
    /*
    auto pauseBackground = Sprite::create("PauseBackground.png");
    if (pauseBackground == nullptr)
    {
        problemLoading("'PauseBackground.png'");
    }
    else
    {
        pauseBackground->setScale(0.5);
        //pauseBackground->setAnchorPoint(Vec2(visibleSize.width/2,visibleSize.height/2));
        // position the sprin the center of the screen
        pauseBackground->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(pauseBackground, 0);
    }
    */
    
  
    
    auto labelGameName = Label::createWithTTF("single", "fonts/Marker Felt.ttf", 45);
    if (labelGameName == nullptr)
    {
        problemLoading("'Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelGameName->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - labelGameName->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(labelGameName, 1);
    }
    
    //暂停按钮
    auto pauseItem = MenuItemImage::create("pausebutton.png",
                                           "pausebutton.png",
                                           CC_CALLBACK_1(SingleModeRuntime::menuPauseCallback, this));

    if (pauseItem == nullptr ||
        pauseItem->getContentSize().width <= 0 ||
        pauseItem->getContentSize().height <= 0)
    {
        problemLoading("'pausebutton.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width-pauseItem->getContentSize().width/2;
        float y = origin.y + visibleSize.height-pauseItem->getContentSize().height/2;
        pauseItem->setPosition(Vec2(x,y));
    }
    auto pauseButtonMenu = Menu::create(pauseItem, NULL);
    pauseButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(pauseButtonMenu, 1);

   

    
    return true;
}


void SingleModeRuntime::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


void SingleModeRuntime::menuPauseCallback(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
        //遍历当前类的所有子节点信息，画入renderTexture中。
        //这里类似截图。
    //auto *curScene=Director::getRunningScene();
    renderTexture->begin();
    this->visit();
    renderTexture->end();
      //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
    Director::getInstance()->pushScene(Pause::createScene(renderTexture)); //这里实际是通过CCRenderTexture保存当前界面（相当于截屏），然后传递给暂停界面，当成背景精灵
}


void SingleModeRuntime::initPhysical()
{
    Size sizeOfMap = Director::getInstance()->getWinSize();
    //设置重力
    b2Vec2 gravity;
    gravity.Set(0.0f,-10.0f );
    //创建世界
    world=new b2World(gravity);
    
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    
    b2Body* groundBody=world->CreateBody(&groundBodyDef);
    
    //底部的边界
    b2EdgeShape groundBox;//形状
    groundBox.Set(b2Vec2(0,0) ,   b2Vec2 (sizeOfMap.width/32.0 , 0));
    groundBody->CreateFixture(&groundBox,0);
    
    //上部的边界
    groundBox.Set(b2Vec2(0,sizeOfMap.height/32.0) ,   b2Vec2 (sizeOfMap.width/32.0 , sizeOfMap.height/32.0));
    groundBody->CreateFixture(&groundBox,0);
    
    //左部的边界
    groundBox.Set(b2Vec2(0,0) ,   b2Vec2 (0 ,sizeOfMap.height/32.0));
    groundBody->CreateFixture(&groundBox,0);
    
    //右部的边界
    groundBox.Set(b2Vec2(sizeOfMap.width/32.0,0) ,   b2Vec2 (sizeOfMap.width/32.0 ,sizeOfMap.height/32.0));
    groundBody->CreateFixture(&groundBox,0);
}








