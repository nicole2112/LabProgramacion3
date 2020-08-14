//Leo Pazzetti
#include "NivelUnoScene.h"
#include "MapScene.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
#include <thread>
#include <iostream>
#include <string>
#include <cocos2d.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
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
    //Variables de tamaño y posición de ventana
    visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //Título
    auto titulo = Sprite::create("images/tituloRuleta.png");
    if (titulo != nullptr) {
        titulo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titulo->getContentSize().height + 20));
        this->addChild(titulo, 1);
    }

    //Instrucciones
    auto instrucciones = Label::createWithTTF("Gire la ruleta \ny conteste la pregunta.", "fonts/Marker Felt.ttf", 14);
    if (instrucciones != nullptr) {
        instrucciones->setColor(Color3B::WHITE);
        // position the label on the center of the screen
        instrucciones->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height / 2 + 60));

        // add the label as a child to this layer
        this->addChild(instrucciones, 1);
    }

    //Cuadro de categorías
    auto categorias = Sprite::create("Images/categorias.png");
    if (categorias != nullptr) {
        categorias->setPosition(Vec2(origin.x + visibleSize.width / 4 - 30, origin.y + visibleSize.height / 3));
        this->addChild(categorias, 1);
    }


    //Crear el botón para girar la ruleta y posicionarlo
    ui::Button* botonS = ui::Button::create("images/button1.png", "images/button2.png");
    botonS->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 5 + origin.y) - 20));

    //Menú ítem de regresar a mapa
    auto menuItem1 = MenuItemFont::create("GoBack", CC_CALLBACK_1(NivelUnoScene::GoBack, this));
    menuItem1->setPosition(Point(visibleSize.width / 5, (visibleSize.height / 5) - 25));
    auto mapa = Menu::create(menuItem1, NULL);
    mapa->setPosition(Point(0, 0));

    //Creación del sprite de la ruleta y posicionarla
    Ruleta = Sprite::create("images/ruleta.png");
    Ruleta->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + 5));

    //Añadir botones y ruleta a la escena
    this->addChild(Ruleta, 1);
    this->addChild(mapa, 1);
    this->addChild(botonS, 2);

    //Añadirle evento al botón que hace girar la ruleta 
    botonS->addTouchEventListener(CC_CALLBACK_2(NivelUnoScene::spinR, this));

    //Agregar la categoría actual
    actualCategory = Sprite::create("images/empty.png");
    if (actualCategory != nullptr) {
        actualCategory->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + 95));
        this->addChild(actualCategory, 1);
    }

    //Se crea el label donde sale la pregunta
    pregunta = Label::createWithTTF("", "fonts/Marker Felt.ttf", 18);
    if (pregunta != nullptr) {
        pregunta->setColor(Color3B::WHITE);
        // Pone el Label a la derecha de la pantalla
        pregunta->setPosition(Vec2(origin.x + (visibleSize.width / 2) + 175, origin.y + (visibleSize.height / 2) + 120));

        // Añade el child al layer
        this->addChild(pregunta, 1);
    }

    //Se crea el sprite de la puntuación obtenida
    puntosSprite = Sprite::create("images/empty.png");
    if (puntosSprite != nullptr) {
        puntosSprite->setPosition(Vec2(visibleSize.width / 2 + 170, (visibleSize.height / 2 - 40) - 20));
        this->addChild(puntosSprite, 1);
    }

    return true;
}

//Callback de regresar al mapa
void NivelUnoScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

//Callback para girar la ruleta
void NivelUnoScene::spinR(Ref* sender, ui::Widget::TouchEventType type)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto rotacion = RotateBy::create(2, 1800); //da 5 vueltas
    auto rotacion2 = RotateBy::create(2, 50);
    int r1 = 0;
    int r2 = 0;
    DelayTime* delayt;
    Sequence* sequence;
    delayt = DelayTime::create(4);

    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::BEGAN:
        log("boton pressed");

        r1 = (rand() % 2160) + 2000;
        log(r1);

        rotacion = RotateBy::create(2, r1);
        Ruleta->runAction(rotacion);

        r2 = (rand() % 359) + 1;
        cout << r2 << endl;

        rotacion2 = RotateBy::create(1, r2);
        log("Se roto");
        Ruleta->runAction(rotacion2);

        puntosSprite->setTexture("images/empty.png");

        break;

    case cocos2d::ui::Widget::TouchEventType::MOVED:
        log("touch moved ");
        break;

    case cocos2d::ui::Widget::TouchEventType::ENDED:

        log("Touch ended");


        selectCategory();

        break;

    case cocos2d::ui::Widget::TouchEventType::CANCELED:
        log("touch Canceled");
        break;

    default:
        break;
    }
}

//Función que selecciona la categoría en base al ángulo de la rueda
void NivelUnoScene::selectCategory() {
    vueltas = Ruleta->getRotation() / 360;
    this->angle = Ruleta->getRotation() - (360 * vueltas);


    if (angle >= 90 && angle < 180) {
        actualCategory->setTexture("Images/arte.png");

        arte();

        log("Arte");
    }
    else if (angle < 90 && angle >= 0) {
        actualCategory->setTexture("Images/ciencia.png");

        ciencia();

        log("Ciencia");
    }
    else if (angle >= 180 && angle < 270) {
        actualCategory->setTexture("Images/politica.png");

        politica();

        log("Politica");
    }
    else if (angle >= 270 && angle < 360) {
        actualCategory->setTexture("Images/historia.png");

        historia();

        log("Historia");
    }

}

//Funciones de cada categoria

//ARTE
void NivelUnoScene::arte() 
{ 

    //Agrega los botones de opcion
    ui::Button* opcion1 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion1->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 90) - 20));
    opcion1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion1);

    ui::Button* opcion2 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion2->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 50) - 20));
    opcion2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            }
        });
    this->addChild(opcion2, 2);

    ui::Button* opcion3 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion3->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 10) - 20));
    opcion3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSpriteBad();
                break;
            }
        });
    this->addChild(opcion3, 2);

    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[3][4];//Prototipo: 3 preguntas, 3 respuestas por pregunta
    Questions[0][0] = "Pregunta 1";
    Questions[1][0] = "Pregunta 2";
    Questions[2][0] = "Pregunta 3";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            Questions[i][j] = "Opcion " + j;
        }
    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    int random = (rand() % 3);
    pregunta->setString("Arte\n" + Questions[random][0]);

}

//CIENCIA
void NivelUnoScene::ciencia() 
{
    //Agrega los botones de opcion
    ui::Button* opcion1 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion1->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 90) - 20));
    opcion1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion1, 2);

    ui::Button* opcion2 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion2->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 50) - 20));
    opcion2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion2, 2);

    ui::Button* opcion3 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion3->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 10) - 20));
    opcion3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSpriteBad();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion3, 2);
    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[3][4];//Prototipo: 3 preguntas, 3 respuestas por pregunta
    Questions[0][0] = "Pregunta 1";
    Questions[1][0] = "Pregunta 2";
    Questions[2][0] = "Pregunta 3";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            Questions[i][j] = "Opcion " + j;
        }
    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    int random = (rand() % 3);
    pregunta->setString("Ciencia\n" + Questions[random][0]);
}

//POLÍTICA
void NivelUnoScene::politica() 
{
    //Agrega los botones de opcion
    ui::Button* opcion1 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion1->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 90) - 20));
    opcion1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion1, 2);

    ui::Button* opcion2 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion2->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 50) - 20));
    opcion2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion2, 2);

    ui::Button* opcion3 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion3->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 10) - 20));
    opcion3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSpriteBad();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion3, 2);

    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[3][4];//Prototipo: 3 preguntas, 3 respuestas por pregunta
    Questions[0][0] = "Pregunta 1";
    Questions[1][0] = "Pregunta 2";
    Questions[2][0] = "Pregunta 3";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            Questions[i][j] = "Opcion " + j;
        }
    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    int random = (rand() % 3);
    pregunta->setString("Politica\n" + Questions[random][0]);
}

//HISTORIA
void NivelUnoScene::historia()
{
    //Agrega los botones de opcion
    ui::Button* opcion1 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion1->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 90) - 20));
    opcion1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion1, 2);

    ui::Button* opcion2 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion2->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 50) - 20));
    opcion2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion2, 2);

    ui::Button* opcion3 = ui::Button::create("images/CloseNormal.png", "images/CloseSelected.png");
    opcion3->setPosition(Vec2(visibleSize.width / 2 + 175, (visibleSize.height / 2 + 10) - 20));
    opcion3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addSprite();
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    this->addChild(opcion3, 2);

    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[3][4];//Prototipo: 3 preguntas, 3 respuestas por pregunta
    Questions[0][0] = "Pregunta 1";
    Questions[1][0] = "Pregunta 2";
    Questions[2][0] = "Pregunta 3";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            Questions[i][j] = "Opcion " + j;
        }
    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    int random = (rand() % 3);
    pregunta->setString("Historia\n" + Questions[random][0]);
}

//Ambos metodos agregan los sprites de los puntajes

void NivelUnoScene::addSprite()
{
    puntosSprite->setTexture("images/+100puntos.png");
}

void NivelUnoScene::addSpriteBad()
{
    puntosSprite->setTexture("images/-50puntos.png");
}
