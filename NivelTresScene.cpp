//Leo Pazzetti
#include "NivelTresScene.h"
#include "MapScene.h"
#include "KantScene.h"
#include "DescartesScene.h"
#include"ui/CocosGUI.h"
#include <cocos2d.h>

USING_NS_CC;
using namespace ui;
using namespace std;

Scene* NivelTresScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = NivelTresScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NivelTresScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bg = cocos2d::LayerColor::create(Color4B(158, 236, 219, 255));
    this->addChild(bg, -3);

    auto grass = Sprite::create("Images/grass.png");
    grass->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100));
    this->addChild(grass, -2);

    auto universidad = Sprite::create("Images/universidad.png");
    universidad->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 45) );
    this->addChild(universidad, -1);

    //Botón de Kant
    ui::Button* botonKant = ui::Button::create("Images/botonKantNormal.png", "Images/botonKantSelected.png");
    botonKant->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + (visibleSize.height / 2)));

    botonKant->addTouchEventListener(CC_CALLBACK_2(NivelTresScene::KantScene, this));

    this->addChild(botonKant, 1);

    //Botón de Descartes
    ui::Button* botonDescartes = ui::Button::create("Images/botonDescartesNormal.png", "Images/botonDescartesSelected.png");
    botonDescartes->setPosition(Vec2(origin.x + visibleSize.width / 2 + 110, origin.y + (visibleSize.height / 2)));

    botonDescartes->addTouchEventListener(CC_CALLBACK_2(NivelTresScene::DescartesScene, this));

    this->addChild(botonDescartes, 1);


    auto menuItem1 = MenuItemFont::create("Regresar", CC_CALLBACK_1(NivelTresScene::GoBack, this));

    menuItem1->setPosition(Point(origin.x + visibleSize.width / 2 - 180, origin.y + (visibleSize.height / 2) + 120));
    menuItem1->setColor(Color3B::BLACK);
    menuItem1->setFontSizeObj(14);

    auto mapa = Menu::create(menuItem1, NULL);
    mapa->setPosition(Point(0, 0));
    this->addChild(mapa, 1);

    //Título
    Sprite* titulo = Sprite::create("Images/tituloNivel3Escena.jpg");
    if (titulo != nullptr) {
        titulo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titulo->getContentSize().height + 20));
        this->addChild(titulo, 1);
    }


    return true;
}

void NivelTresScene::DescartesScene(Ref* sender, ui::Widget::TouchEventType type) {
    auto scene = DescartesScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void NivelTresScene::KantScene(Ref* sender, ui::Widget::TouchEventType type) {
    auto scene = KantScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void NivelTresScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}


void NivelTresScene::menuCloseCallback(Ref* pSender)
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