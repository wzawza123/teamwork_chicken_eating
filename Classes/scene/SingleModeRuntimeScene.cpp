//
//  SingleModeRunTimeScence.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#define PTM_RATIO 32.0f

#include "HelloWorldScene.h"
#include "SingleModeRuntimeScene.h"
#include "PauseScene.h"
#include "const.h"
#include <CCVector.h>

using namespace tagConsts;

USING_NS_CC;
SingleModeRuntime::SingleModeRuntime()
{
    /*监听鼠标的操作*/
    auto Listener = EventListenerMouse::create();
    Listener->onMouseDown = CC_CALLBACK_1(SingleModeRuntime::onMouseDown, this);
    Listener->onMouseMove = CC_CALLBACK_1(SingleModeRuntime::onMouseMove, this);
    Listener->onMouseUp = CC_CALLBACK_1(SingleModeRuntime::onMouseUp, this);
    Listener->onMouseDown = CC_CALLBACK_1(SingleModeRuntime::onMouseDown, this);
    Listener->onMouseScroll = CC_CALLBACK_1(SingleModeRuntime::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SingleModeRuntime::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Scene* SingleModeRuntime::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = SingleModeRuntime::create();
    scene->addChild(layer,1,10);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
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
    
    //地
    testMap = TMXTiledMap::create("textMap.tmx");
    this->addChild(testMap,0,0);
   
    //战歌起
    groundMusicPlay();
    
    auto groupwall = testMap->getObjectGroup("wall");
    ValueVector objectsWall = groupwall->getObjects();
    
    
    for (auto wall : objectsWall)
    {
        ValueMap& dict = wall.asValueMap();
        
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        float rotate = dict["rotation"].asFloat();

        PhysicsBody* tmpPhysicsBody = PhysicsBody::createBox(Size(width, height));
        tmpPhysicsBody->setDynamic(false);
        tmpPhysicsBody->setCategoryBitmask(1);
        tmpPhysicsBody->setCollisionBitmask(1);
        tmpPhysicsBody->setContactTestBitmask(1);
        
        Sprite* tmpSprite = Sprite::create();
        tmpSprite->setPosition(Vec2(x, y));
        tmpSprite->setAnchorPoint(Vec2::ZERO);
        tmpSprite->setContentSize(Size(width, height));
        tmpSprite->setPhysicsBody(tmpPhysicsBody);
        
        addChild(tmpSprite,1,5);
    }

    
    
    
    PhysicsBody* heroPhysicsBody = PhysicsBody::createBox(Size(player.getContentSize()));
    heroPhysicsBody->setDynamic(true);
    heroPhysicsBody->setCategoryBitmask(1);
    heroPhysicsBody->setCollisionBitmask(1);
    heroPhysicsBody->setContactTestBitmask(1);
    
    player.delegateSprite->setPhysicsBody(heroPhysicsBody);
    
    addChild(&player,1,tagConsts::tagHero);
    addChild(&gun);
    /*给角色添加武器（到时候改为拾取武器）*/
    (&player)->setMainWeapon(&gun);


    //监听键盘
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //创建一个事件监听器监听键盘事件
    keyListener->onKeyPressed = CC_CALLBACK_2(hero::onKeyPressed, &player);
    //键盘被按下时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(hero::onKeyReleased,&player);
    //键盘按键被弹回时响应
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    
    
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


    heroUI = HeroUI::create();
    this->addChild(heroUI);
    
    //暂停按钮
    pauseItem = MenuItemImage::create("pausebutton.png",
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

    // 视角相机
        p = Camera::createOrthographic(visibleSize.width, visibleSize.height, 0, 1);
    p->setCameraFlag(CameraFlag::USER2);
    p->setPosition3D(Vec3(0, 0, 0));
    this->setCameraMask((unsigned short)CameraFlag::USER2);
    //player.setCameraMask((unsigned short) CameraFlag::DEFAULT);
    //testMap->setCameraMask((unsigned short) CameraFlag::DEFAULT);
    (&gun)->setCameraMask((unsigned short)CameraFlag::USER2);
    heroUI->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    pauseItem->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    pauseButtonMenu->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    //labelGameName->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    this->addChild(p, 1);

   //设置更新函数
    scheduleUpdate();
    
    return true;
}


void SingleModeRuntime::groundMusicPlay()
{
    auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
    engine->playBackgroundMusic("金﨑猛 - フォドラの暁風.mp3",true);
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


void SingleModeRuntime::setCneterPointOfView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
//因为这里是要通过传入的点p来显示设定CCLayer的位置，p为英雄坐标，当做显示中心点。
//TileMap的size肯定大于WinSize（分辨率），不然有黑边，而且也不用移动地图了。
//因此p的x、y的值肯定要大于等于屏幕中心的值
    int x = MAX(player.delegateSprite->getPosition().x, visibleSize.width / 2);
    int y = MAX(player.delegateSprite->getPosition().y, visibleSize.height / 2);

    //同理，p的x、y要小于等于TileMap的size的宽高减去WinSize的中心值,不然也会出现黑边
    x = MIN(x, testMap->getMapSize().width * testMap->getTileSize().width - visibleSize.width / 2);
    y = MIN(y, testMap->getMapSize().height * testMap->getTileSize().height - visibleSize.height / 2);
    Point actualPosition = Vec2(x, y);
    auto pos = p->getPosition3D();
    Point winCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    Point viewPosition = actualPosition - winCenter;
    pos.x = viewPosition.x;
    pos.y = viewPosition.y;
    p->setPosition3D(pos);
}

 
void SingleModeRuntime::update(float dt)
{
    setCneterPointOfView();
    ((&player)->getMyMainWeapon()->getMouseImage())->setPosition(convertToNodeSpace((&player)->MousePosition));
    //((&player)->getMyMainWeapon()->getMouseImage())->setCameraMask((unsigned short)CameraFlag::DEFAULT);
}
 



bool SingleModeRuntime::onMouseDown(Event* pEvent)
{
    /*获取子弹发射方向*/
    auto X = (&player)->MousePosition.x - convertToWorldSpace((&gun)->getWeaponPosition()).x;
    auto Y = (&player)->MousePosition.y - convertToWorldSpace((&gun)->getWeaponPosition()).y;
    auto length = hypot(X, Y);
    auto XCoefficient = X / length;
    auto YCoefficient = Y / length;
    log("=============================================================");
    /*每次点击添加一个新子弹*/
    Bullet* newBullet;
    newBullet = (&gun)->shootBullet(Vec2(2000 * XCoefficient, 2000 * YCoefficient));
    newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
    addChild(newBullet, 1, tagConsts::tagBullet);
    return true;
}

void SingleModeRuntime::onMouseUp(Event* pEvent)
{

}

void SingleModeRuntime::onMouseMove(Event* pEvent)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
//因为这里是要通过传入的点p来显示设定CCLayer的位置，p为英雄坐标，当做显示中心点。
//TileMap的size肯定大于WinSize（分辨率），不然有黑边，而且也不用移动地图了。
//因此p的x、y的值肯定要大于等于屏幕中心的值
    int x = MAX(player.delegateSprite->getPosition().x, visibleSize.width / 2);
    int y = MAX(player.delegateSprite->getPosition().y, visibleSize.height / 2);

    //同理，p的x、y要小于等于TileMap的size的宽高减去WinSize的中心值,不然也会出现黑边
    x = MIN(x, testMap->getMapSize().width * testMap->getTileSize().width - visibleSize.width / 2);
    y = MIN(y, testMap->getMapSize().height * testMap->getTileSize().height - visibleSize.height / 2);
    Point actualPosition = Vec2(x, y);
    auto pos = p->getPosition3D();
    Point winCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    Point viewPosition = actualPosition - winCenter;
    pos.x = viewPosition.x;
    pos.y = viewPosition.y;

    EventMouse* e = (EventMouse*)pEvent;
    (&player)->MousePosition = Point(e->getCursorX()+viewPosition.x, e->getCursorY()+viewPosition.y);
    /*对于鼠标瞄准镜图像的一些说明：
    *当鼠标移动时，利用该函数获取鼠标坐标（以英雄为参考点），
    *并将瞄准镜图像贴在屏幕中，update函数中反复调用*/

    /*设置鼠标不可见*/
    Director::getInstance()->getOpenGLView()->setCursorVisible(false);

}

void SingleModeRuntime::onMouseScroll(Event* pEvent)
{

}



