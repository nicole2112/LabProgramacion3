#ifndef __NIVELTRES_SCENE_H__
#define __NIVELTRES_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class NivelTresScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(NivelTresScene);

    cocos2d::Sprite* mySprite;

    void GoBack(Ref* pSender);
    void KantScene(Ref* sender, ui::Widget::TouchEventType type);
    void DescartesScene(Ref* sender, ui::Widget::TouchEventType type);

};

#endif // __NIVELTRES_SCENE_H__
