#include "MapScene.h"
#include "NivelUnoScene.h"
#include "NivelDosScene.h"
#include "NivelTresScene.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MapScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void MapScene::inicializarTeclado()
{
    // Crear el escuchador de eventos de teclado
    auto escuchador = EventListenerKeyboard::create();

    escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
    escuchador->onKeyReleased = CC_CALLBACK_2(MapScene::presionarTecla, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

void MapScene::presionarTecla(EventKeyboard::KeyCode key, Event* event) {
    switch (key) {
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (menuItem1->getColor() == Color3B::GREEN) {
            Play(this);
        }
        else if (menuItem2->getColor() == Color3B::GREEN) {
            NivelDos(this);
        }
        else if (menuItem3->getColor() == Color3B::GREEN) {
            NivelTres(this);
        }
        log("Right arrow pressed");
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (menuItem2->getColor() == Color3B::GREEN) {
            menuItem2->setColor(Color3B::BLACK);
            menuItem1->setColor(Color3B::GREEN);
        }
        else if (menuItem3->getColor() == Color3B::GREEN) {
            menuItem3->setColor(Color3B::BLACK);
            menuItem2->setColor(Color3B::GREEN);
        }
        log("Up arrow pressed");
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (menuItem1->getColor() == Color3B::GREEN) {
            menuItem1->setColor(Color3B::BLACK);
            menuItem2->setColor(Color3B::GREEN);
        }
        else if (menuItem2->getColor() == Color3B::GREEN) {
            menuItem2->setColor(Color3B::BLACK);
            menuItem3->setColor(Color3B::GREEN);
        }
        log("Down arrow pressed");
        break;
    case EventKeyboard::KeyCode::KEY_ESCAPE:
        regresarCloseCallback(this);
        log("Escape key pressed");
        break;
    }
}

bool MapScene::init()
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    log("Initializing map scene");

    auto bg = cocos2d::LayerColor::create(Color4B(51, 255, 238, 255));
    this->addChild(bg, -1);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Agregar imagen de mapa
    auto mapa = Sprite::create("images/mapa.png");
    if (mapa != nullptr) {
        mapa->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        this->addChild(mapa, 0);
    }

    //Niveles Leonardo Pazzetti
    menuItem1 = MenuItemFont::create("Play", CC_CALLBACK_1(MapScene::Play, this));
    menuItem2 = MenuItemFont::create("Nivel Dos", CC_CALLBACK_1(MapScene::NivelDos, this));
    menuItem3 = MenuItemFont::create("Nivel Tres", CC_CALLBACK_1(MapScene::NivelTres, this));

    menuItem1->setColor(Color3B::BLACK);
    menuItem2->setColor(Color3B::BLACK);
    menuItem3->setColor(Color3B::BLACK);


    menuItem1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menuItem2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menuItem3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1));

    auto mapad = Menu::create(menuItem1,menuItem2,menuItem3, NULL);
    mapad->setPosition(Point(0, 0));
    this->addChild(mapad,1);

  

   
    //Título
    auto label = Label::createWithTTF("Mapa", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr) {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
        label->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}

void MapScene::Play(cocos2d::Ref* pSender)
{
    CCLOG("Play");
    //create scene
    auto scene = NivelUnoScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void MapScene::NivelDos(cocos2d::Ref* pSender)
{
    CCLOG("Nivel Dos");
    //create scene
    auto scene = NivelDosScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void MapScene::NivelTres(cocos2d::Ref* pSender)
{
    CCLOG("Nivel Tres");
    //create scene
    auto scene = NivelTresScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}


void MapScene::regresarCloseCallback(Ref* pSender)
{
    log("Regresando al menú principal");
    //creando la escena
    auto scene = MainMenu::createScene();
    //Reemplazando la escena actual con la siguiente, se aplica un efecto de transición
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
