#include "MainMenuScene.h"
#include <cocos\base\ccTypes.cpp>
#include <cocos\ui\UIScale9Sprite.h>
#include "../proj.win32/MapScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void MainMenu::presionarTecla(EventKeyboard::KeyCode key, Event *event) {
    switch (key) {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (menuItem1->getColor() == Color3B::ORANGE) {
                mapaCloseCallback(this);
            } 
            else if (menuItem2->getColor() == Color3B::ORANGE) {
                puntuacionCloseCallback(this);
            }
            else if (menuItem3->getColor() == Color3B::ORANGE) {
                salirCloseCallback(this);
            }
            log("Right arrow pressed");
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            if (menuItem2->getColor() == Color3B::ORANGE) {
                menuItem2->setColor(Color3B::WHITE);
                menuItem1->setColor(Color3B::ORANGE);
            }
            else if (menuItem3->getColor() == Color3B::ORANGE) {
                menuItem3->setColor(Color3B::WHITE);
                menuItem2->setColor(Color3B::ORANGE);
            }
            log("Up arrow pressed");
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            if (menuItem1->getColor() == Color3B::ORANGE) {
                menuItem1->setColor(Color3B::WHITE);
                menuItem2->setColor(Color3B::ORANGE);
            }
            else if (menuItem2->getColor() == Color3B::ORANGE) {
                menuItem2->setColor(Color3B::WHITE);
                menuItem3->setColor(Color3B::ORANGE);
            }
            log("Down arrow pressed");
            break;
    }
    
}

void MainMenu::inicializarTeclado() {
    // Crear el escuchador de eventos de teclado
    auto escuchador = EventListenerKeyboard::create();

    escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
    escuchador->onKeyReleased = CC_CALLBACK_2(MainMenu::presionarTecla, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


    log("Initializing scene");

    //1. Se asignan las variables para manejo de posiciones en la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //2. Colocando la imagen de fondo
    auto spriteFondo = Sprite::create("Images/background.jpg");
    spriteFondo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(spriteFondo, 0); //Añadir la imagen a la pantalla

    //3. Crear cada menú ítem 
    menuItem1 = MenuItemFont::create("MAPA", CC_CALLBACK_1(MainMenu::mapaCloseCallback, this));
    menuItem1->setFontSizeObj(22);

    menuItem2 = MenuItemFont::create("PUNTUACION", CC_CALLBACK_1(MainMenu::puntuacionCloseCallback, this));
    menuItem2->setFontSizeObj(22);

    menuItem3 = MenuItemFont::create("SALIR", CC_CALLBACK_1(MainMenu::salirCloseCallback, this));
    menuItem3->setFontSizeObj(22);

    //Estableciendo las posiciones de cada ítem
    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menuItem2->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menuItem3->setPosition(Vec2(origin.x +visibleSize.width / 2, (visibleSize.height / 4) * 1));

    menuItem1->setColor(Color3B::ORANGE); //color inicial de la primera opción

    //4. Crear el menú que contiene cada ítem
    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //5. Agregar el label con el título
    auto label = Label::createWithTTF("PRIMER JUEGO", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr) {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //Eventos del teclado
    inicializarTeclado();

    return true;
}


void MainMenu::puntuacionCloseCallback(Ref* sender) {
    log("Abriendo Puntuacion");
    auto scene = Puntuacion::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
    
}

void MainMenu::mapaCloseCallback(Ref* sender) {
    log("Abriendo Mapa");
    //create scene
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void MainMenu::salirCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
