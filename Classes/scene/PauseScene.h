//
//  PauseScene.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef PauseScene_h
#define PauseScene_h

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "cocos-ext.h" 

USING_NS_CC;

class Pause : public Scene
{
public:
    static Scene* createScene(RenderTexture* sqr);

    virtual bool init();
    
    void gameEndCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    //Lable * label; //显示滑块数值的Label
     
    //void valueChanged(Ref* sender, Control::EventType controlEvent); //当值改变时触发的控件事件

    
    CREATE_FUNC(Pause);
};
#endif /* PauseScene_h */
