//
//  PauseScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#include "PauseScene.h"
#include "SingleModeRuntimeScene.h"
#include "OnlineModeRuntimeScene.h"
#include "Slider.h"

USING_NS_CC;

//传入一个CCrenderTexture
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
Scene* Pause::createScene(RenderTexture* sqr)
{
    auto *background=Scene::create();
    auto *layer=Pause::create();
    background->addChild(layer,1);
    auto pauseColor=Color3B(169,169,169);
    //得到窗口的大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto *_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    _sqr->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    //sqr->setFlipY(true);    //翻转，因为UI坐标和OpenGL坐标不同
    _sqr->setColor(pauseColor); //深灰色
    background->addChild(_sqr);
    return background;
    //return Pause::create();
}




static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool Pause::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    auto pauseBoardImg = ui::Scale9Sprite::create("ui_pause_board.png");
    if(pauseBoardImg == nullptr)
    {
        problemLoading("'ui_pause_board.png'");
    }
    else
    {
        pauseBoardImg->setCapInsets(Rect(6, 6, 79, 61));
        pauseBoardImg->setContentSize(Size(300, 200));
        pauseBoardImg->setPosition(visibleSize.width / 2, visibleSize.height / 2);

        this->addChild(pauseBoardImg, 0);
    }

    /*auto pauseBackground = Sprite::create("PauseBackground.png");
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
    }*/
    
    auto labelGameName = Label::createWithTTF("Pause Menu", "fonts/Marker Felt.ttf", 45);
    if (labelGameName == nullptr)
    {
        problemLoading("'Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelGameName->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + 4*visibleSize.height/5 - labelGameName->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(labelGameName, 1);
    }
    
    //返回游戏按钮
    auto labelResume = Label::createWithTTF("Resume","fonts/Marker Felt.ttf", 40);
    auto labelResumeItem = MenuItemLabel::create(labelResume,CC_CALLBACK_1(Pause::menuCloseCallback, this));
    auto labelResumeMenu = Menu::create(labelResumeItem, NULL);
    labelResumeMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + 2*visibleSize.height/3 - labelGameName->getContentSize().height));
    this->addChild(labelResumeMenu,1);
    
    //退出游戏按钮
    auto labelQuit = Label::createWithTTF("Quit","fonts/Marker Felt.ttf", 40);
    auto labelQuitItem = MenuItemLabel::create(labelQuit,CC_CALLBACK_1(Pause::gameEndCallback, this));
    auto labelQuitMenu = Menu::create(labelQuitItem, NULL);
    labelQuitMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + 8*visibleSize.height/15 - labelGameName->getContentSize().height));
    this->addChild(labelQuitMenu,1);

    //音量滑轨
    //addChild(&audioSlider,1);
    
    return true;
}


void Pause::gameEndCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void Pause::menuCloseCallback(Ref* pSender)
{
    //返回当前游戏界面
    Director::getInstance()->resume();
    Director::getInstance()->popScene();
}
