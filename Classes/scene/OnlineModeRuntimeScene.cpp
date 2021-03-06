//
//  OnlineModeRuntimeScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#include "HelloWorldScene.h"
#include "OnlineModeRuntimeScene.h"

USING_NS_CC;

Scene* OnlineModeRuntime::createScene()
{
    return OnlineModeRuntime::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool OnlineModeRuntime::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值

    auto labelGameName = Label::createWithTTF("online", "Marker Felt.ttf", 45);
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
    

    return true;
}


void OnlineModeRuntime::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


void OnlineModeRuntime::menuPauseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(OnlineModeRuntime::createScene());
}
