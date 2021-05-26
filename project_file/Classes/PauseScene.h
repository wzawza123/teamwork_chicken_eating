//
//  PauseScene.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef PauseScene_h
#define PauseScene_h

#include "cocos2d.h"
#include "Slider.h"

USING_NS_CC;

class Pause : public Scene
{
public:
    static Scene* createScene(RenderTexture* sqr);

    virtual bool init();
    
    void gameEndCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    Slider audioSlider;
    
    CREATE_FUNC(Pause);
};
#endif /* PauseScene_h */
