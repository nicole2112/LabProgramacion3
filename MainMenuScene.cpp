#include "MainMenuScene.h"
#include <cocos\base\ccTypes.cpp>
#include <cocos\ui\UIScale9Sprite.h>
#include "../proj.win32/MapScene.h"
#include <Puntuacion.h>

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

//Función que maneja lo que sucederá al presionar una tecla
void MainMenu::presionarTecla(EventKeyboard::KeyCode key, Event *event) {

    switch (key) { //Dependiendo de la tecla que se presione suceden distintos casos

        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //Si se presiona la flecha derecha, se llaman las funciones
                                                        //Callbacks respectivas
            if (menuItem1->getColor() == Color3B::GREEN) {
                mapaCloseCallback(this);
            } 
            else if (menuItem2->getColor() == Color3B::GREEN) {
                puntuacionCloseCallback(this);
            }
            else if (menuItem3->getColor() == Color3B::GREEN) {
                salirCloseCallback(this);
            }
            log("Right arrow pressed");
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW: //Con las teclas arriba y abajo solo se cambia la
                                                    //selección del menú
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
    }
    
}

//Inicializa los eventos del teclado
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

    auto bg = cocos2d::LayerColor::create(Color4B(158, 236, 219, 255));
    this->addChild(bg, -2);

    //1. Se asignan las variables para manejo de posiciones en la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto nube = Sprite::create("Images/nube.png");
    nube->setPosition(Vec2(origin.x + visibleSize.width / 2 + 150, origin.y + visibleSize.height / 2 + 100));
    this->addChild(nube, -1);

    auto nube2 = Sprite::create("Images/nube.png");
    nube2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 150, origin.y + visibleSize.height / 2 + 115));
    nube2->setFlippedX(true);
    this->addChild(nube2, -1);

    auto mountains = Sprite::create("Images/montañas.png");
    mountains->setPosition(Vec2(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height / 2 - 60));
    this->addChild(mountains, -1);

    //2. Colocando la imagen de fondo
    auto spriteFondo = Sprite::create("Images/castillo.png");
    spriteFondo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 8));
    this->addChild(spriteFondo, 0); //Añadir la imagen a la pantalla

    //======================
    //Colocar background

    bgItem1 = Sprite::create("images/BGitem.png");
    if (bgItem1 != nullptr) {
        bgItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 3));
        bgItem1->setVisible(true);
        this->addChild(bgItem1, 1);
    }

    bgItem2 = Sprite::create("images/BGitem.png");
    if (bgItem2 != nullptr) {
        bgItem2->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 2));
        bgItem2->setVisible(true);
        this->addChild(bgItem2, 1);
    }

    bgItem3 = Sprite::create("images/BGitem.png");
    if (bgItem3 != nullptr) {
        bgItem3->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 1));
        bgItem3->setVisible(true);
        this->addChild(bgItem3, 1);
    }
    
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

    menuItem1->setColor(Color3B::GREEN); //color inicial de la primera opción
    menuItem2->setColor(Color3B::BLACK);
    menuItem3->setColor(Color3B::BLACK);

    //4. Crear el menú que contiene cada ítem
    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //5. Agregar el label con el título
    auto label = Label::createWithTTF("FILOSOFANDO", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr) {
        label->setColor(Color3B::BLACK);
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

//Funciones Callback para cada opción del menú

void MainMenu::puntuacionCloseCallback(Ref* sender) {
    menuItem1->setColor(Color3B::BLACK);
    menuItem2->setColor(Color3B::RED);
    menuItem3->setColor(Color3B::BLACK);
    log("Abriendo Puntuacion");

    //Creando la escena de Puntuación
    auto scene = Puntuacion::createScene();

    //Sustituyendo la escena actual con la instanciada previamente, con efecto de transición
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MainMenu::mapaCloseCallback(Ref* sender) {
    menuItem1->setColor(Color3B::GREEN);
    menuItem2->setColor(Color3B::BLACK);
    menuItem3->setColor(Color3B::BLACK);
    log("Abriendo Mapa");

    //Creando la escena del Mapa
    auto scene = MapScene::createScene();

    //Sustituyendo la escena actual con la instanciada previamente, con efecto de transición
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}

void MainMenu::salirCloseCallback(Ref* pSender)
{
    menuItem1->setColor(Color3B::BLACK);
    menuItem2->setColor(Color3B::BLACK);
    menuItem3->setColor(Color3B::GREEN);
    //Cerrando la escena actual y finalizando el aplicativo
    Director::getInstance()->end();
}
