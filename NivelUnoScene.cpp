//Leo Pazzetti
#include "NivelUnoScene.h"
#include "MapScene.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
#include <thread>
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
Scene* NivelUnoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = NivelUnoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NivelUnoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    ui::Button *botonS = ui::Button::create("images/button1.png", "images/button2.png");
    botonS->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 5 + origin.y) - 25));


   auto menuItem1 = MenuItemFont::create("GoBack", CC_CALLBACK_1(NivelUnoScene::GoBack, this));

   menuItem1->setPosition(Point(visibleSize.width / 5, (visibleSize.height / 5) -25));

   auto mapa = Menu::create(menuItem1, NULL);
   mapa->setPosition(Point(0, 0));
   Ruleta = Sprite::create("images/wheel.png");
   Ruleta->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + 50));
   this->addChild(Ruleta);
   this->addChild(mapa);
   this->addChild(botonS);
   botonS->addTouchEventListener( CC_CALLBACK_2( NivelUnoScene::spinR, this ) );

     
    return true;
}

void NivelUnoScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}


void NivelUnoScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void NivelUnoScene::spinR(Ref* sender, ui::Widget::TouchEventType type) 
{
    auto rotacion = RotateBy::create(2, 1800);
    auto rotacion2 = RotateBy::create(2, 50);
    int r1 = 0;

    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::BEGAN:
        log("boton pressed");
        break;
    case cocos2d::ui::Widget::TouchEventType::MOVED:
        log("touch moved ");
        break;
    case cocos2d::ui::Widget::TouchEventType::ENDED:  
        log("Touch ended");
        r1 = (rand() % 2160) + 2000;
        cout << r1 << endl;
        rotacion = RotateBy::create(2, r1);
        Ruleta->runAction(rotacion);
        r1 = (rand() % 359) + 1;
        cout << r1 << endl;
        rotacion2 = RotateBy::create(1, r1);
        log("Se roto");
        log(r1);  
        Ruleta->runAction(rotacion2);
        break;
    case cocos2d::ui::Widget::TouchEventType::CANCELED:
        log("touch Canceled");
        break;
    default:
        break;
    }
}
