#include "Puntuacion.h"
#include "MainMenuScene.h"
USING_NS_CC;


Scene* Puntuacion::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Puntuacion::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}







// on "init" you need to initialize your instance
bool Puntuacion::init()
{
    //////////////////////////////
    // 1. super init first
   

    if (!Scene::init())
    {
        return false;
    }
   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto menuItem1 = MenuItemFont::create("Go Back", CC_CALLBACK_1(Puntuacion::GoBack, this));

    menuItem1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) * 1));

    auto btnB = Menu::create(menuItem1, NULL);
    btnB->setPosition(Point(0, 0));
    this->addChild(btnB,1);
    //Eventos del teclado
    inicializarTeclado();

    //Imagen de fondo
    auto spriteFondo = Sprite::create("Images/puntuacion.jpeg");
    spriteFondo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(spriteFondo, 0); //Añadir la imagen a la pantalla

    return true;
}

void Puntuacion::GoBack(cocos2d::Ref* pSender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}


void Puntuacion::menuCloseCallback(Ref* pSender)
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

void Puntuacion::presionarTecla(EventKeyboard::KeyCode key, Event* event) {
    switch (key) {
    case EventKeyboard::KeyCode::KEY_ESCAPE:

        auto scene = MainMenu::createScene();
        Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));

        break;

    }
}

    void Puntuacion::inicializarTeclado() {
        // Crear el escuchador de eventos de teclado
        auto escuchador = EventListenerKeyboard::create();

        escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
        escuchador->onKeyReleased = CC_CALLBACK_2(Puntuacion::presionarTecla, this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
    }

