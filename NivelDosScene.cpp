//Leo Pazzetti
#include "NivelDosScene.h"
#include "MapScene.h"
#include <string>
#include <iostream>
#include <cocos\editor-support\cocostudio\SimpleAudioEngine.h>
USING_NS_CC;
using namespace std;


Scene* NivelDosScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = NivelDosScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NivelDosScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto stage = Sprite::create("Images/estadio.jpg");
    stage->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(stage, -1);

    auto hume = Sprite::create("Images/bandoHume.png");
    hume->setPosition(Vec2(origin.x + visibleSize.width / 2 - 170, origin.y + visibleSize.height / 2 - 70));
    this->addChild(hume, 0);

    auto descartes = Sprite::create("Images/bandoDescartes.png");
    descartes->setPosition(Vec2(origin.x + visibleSize.width / 2 + 170, origin.y + visibleSize.height / 2 - 70));
    this->addChild(descartes, 0);

    auto lbEmpiristas = Label::createWithTTF("Empiristas", "fonts/arial.ttf", 10);
    lbEmpiristas->setColor(Color3B::BLACK);
    lbEmpiristas->setPosition(Vec2(origin.x + visibleSize.width / 2 - 210, origin.y + visibleSize.height - lbEmpiristas->getContentSize().height));
    this->addChild(lbEmpiristas, 0);

    auto lbRacionalistas = Label::createWithTTF("Racionalistas", "fonts/arial.ttf", 10);
    lbRacionalistas->setColor(Color3B::BLACK);
    lbRacionalistas->setPosition(Vec2(origin.x + visibleSize.width / 2 + 200, origin.y + visibleSize.height - lbRacionalistas->getContentSize().height));
    this->addChild(lbRacionalistas, 0);

    auto teclasJugador1 = Sprite::create("Images/teclasjugador1.PNG");
    if (teclasJugador1 != nullptr) {
        teclasJugador1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 210, origin.y + visibleSize.height / 2 - 95));
        this->addChild(teclasJugador1, 1);
    }

    auto teclasJugador2 = Sprite::create("Images/teclasJugador2.png");
    if (teclasJugador2 != nullptr) {
        teclasJugador2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 130, origin.y + visibleSize.height / 2 - 95));
        this->addChild(teclasJugador2, 1);
    }

    //Título
    auto titulo = Sprite::create("Images/tituloEpistemefighter.jpg");
    if (titulo != nullptr) {
        titulo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titulo->getContentSize().height + 20));
        this->addChild(titulo, 0);
    }

    //Iniciar label para preguntas con instrucciones breves
    lbPregunta = Label::createWithTTF("Objetivo: Ganar la batalla entre empiristas y racionalistas \ncontestando correcta y velozmente cada pregunta. \nPresione Enter para iniciar.",
        "fonts/arial.ttf", 12);
    lbPregunta->setColor(Color3B::BLACK);
    lbPregunta->setAlignment(TextHAlignment::CENTER);
    lbPregunta->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 90));
    this->addChild(lbPregunta, 2);

    //Inicializar opciones de respuestas
    item1 = Label::createWithTTF(" ", "fonts/arial.ttf", 12);
    item1->setColor(Color3B::BLACK);
    item1->setAlignment(TextHAlignment::LEFT);
    item1->setAnchorPoint(Vec2(0, 0));
    this->addChild(item1, 2);

    item2 = Label::createWithTTF(" ", "fonts/arial.ttf", 12);
    item2->setColor(Color3B::BLACK);
    item2->setAlignment(TextHAlignment::LEFT);
    item2->setAnchorPoint(Vec2(0, 0));
    this->addChild(item2, 2);

    item3 = Label::createWithTTF(" ", "fonts/arial.ttf", 12);
    item3->setColor(Color3B::BLACK);
    item3->setAlignment(TextHAlignment::LEFT);
    item3->setAnchorPoint(Vec2(0, 0));
    this->addChild(item3, 2);

    item4 = Label::createWithTTF(" ", "fonts/arial.ttf", 12);
    item4->setColor(Color3B::BLACK);
    item4->setAlignment(TextHAlignment::LEFT);
    item4->setAnchorPoint(Vec2(0, 0));
    this->addChild(item4, 2);

    bgItemA = Sprite::create("images/bgA.png");
    if (bgItemA != nullptr) {
        //bgItemA->setAnchorPoint(Vec2(0, 0));
        bgItemA->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height / 2 + 6));
        bgItemA->setVisible(false);
        this->addChild(bgItemA, 1);
    }

    bgItemB = Sprite::create("images/bgB.png");
    if (bgItemB != nullptr) {
        bgItemB->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height / 2 - 34));
        bgItemB->setVisible(false);
        this->addChild(bgItemB, 1);
    }

    bgItemC = Sprite::create("images/bgC.png");
    if (bgItemC != nullptr) {
        bgItemC->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height / 2 - 74));
        bgItemC->setVisible(false);
        this->addChild(bgItemC, 1);
    }

    bgItemD = Sprite::create("images/bgD.png");
    if (bgItemD != nullptr) {
        bgItemD->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height / 2 - 114));
        bgItemD->setVisible(false);
        this->addChild(bgItemD, 1);
    }

    this->vidaP1 = 5;
    this->vidaP2 = 5;

    //Label para las vidas del player1
    p1Vidas = Label::createWithTTF("Vidas P1: " + to_string(vidaP1), "fonts/arial.ttf", 15);
    if (p1Vidas != nullptr) {
        p1Vidas->setColor(Color3B::WHITE);
        // Pone el Label a la derecha de la pantalla
        p1Vidas->setPosition(Vec2(origin.x + (visibleSize.width / 2) - 170, origin.y + 170));

        // Añade el child al layer
        this->addChild(p1Vidas, 1);
    }
    //Label para las vidas del player2
    p2Vidas = Label::createWithTTF("Vidas P2: " + to_string(vidaP2), "fonts/arial.ttf", 15);
    if (p2Vidas != nullptr) {
        p2Vidas->setColor(Color3B::WHITE);
        // Pone el Label a la derecha de la pantalla
        p2Vidas->setPosition(Vec2(origin.x + (visibleSize.width / 2) + 170, origin.y + 170));

        // Añade el child al layer
        this->addChild(p2Vidas, 1);
    }

    //inicializar eventos del teclado
    inicializarTeclado();

    //===================
    //Se inicializan la prioridad y las respuestas de los jugadores
    respuestaP1 = true;
    respuestaP2 = true;
    prioridad = 0;
    int correcta = 0;
    int R1 = 0;
    int R2 = 0;


    return true;
}

//Inicializa los eventos del teclado
void NivelDosScene::inicializarTeclado() {
    // Crear el escuchador de eventos de teclado
    auto escuchador = EventListenerKeyboard::create();

    escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
    escuchador->onKeyReleased = CC_CALLBACK_2(NivelDosScene::presionarTecla, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

//Función que maneja lo que sucederá al presionar una tecla
void NivelDosScene::presionarTecla(EventKeyboard::KeyCode key, Event* event) {

    switch (key) { //Dependiendo de la tecla que se presione suceden distintos casos

    case EventKeyboard::KeyCode::KEY_ESCAPE: //Si se presiona la tecla Esc, se llaman la función Callback respectiva
        this->schedule(CC_SCHEDULE_SELECTOR(NivelDosScene::stopMusic));
        NivelDosScene::GoBack(this);
        break;
    case EventKeyboard::KeyCode::KEY_ENTER:
        NivelDosScene::showQuestion(this);
        break;
    case EventKeyboard::KeyCode::KEY_1:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP1 == false)
        {
            R1 = 1;
            respuestaP1 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = -1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_2:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP1 == false)
        {
            R1 = 2;
            respuestaP1 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = -1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_3:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP1 == false)
        {
            R1 = 3;
            respuestaP1 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = -1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_4:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP1 == false)
        {
            R1 = 4;
            respuestaP1 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = -1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_7:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP2 == false)
        {
            R2 = 1;
            respuestaP2 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = 1;

        break;
    case EventKeyboard::KeyCode::KEY_8:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP2 == false)
        {
            R2 = 2;
            respuestaP2 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = 1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_9:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP2 == false)
        {
            R2 = 3;
            respuestaP2 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = 1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    case EventKeyboard::KeyCode::KEY_0:
        //If que se asegura que el player no ha respondido todavia
        if (respuestaP2 == false)
        {
            R2 = 4;
            respuestaP2 = true;
        }

        //if que maneja la prioridad: = -1 gana P1, = 1 gana P2
        if (prioridad == 0)
            prioridad = 1;

        if (respuestaP1 == true && respuestaP2 == true)
            revisarRespuesta();

        break;
    }
}

void NivelDosScene::stopMusic(float m) {

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

//Revisa si ya existe la posición de las opciones en el arreglo de posiciones
bool NivelDosScene::checkrep(int n, int num[])
{
    for (int i = 0; i < 4; i++)
        if (n == num[i])
            return true;
    return false;
}

void NivelDosScene::showQuestion(cocos2d::Ref* sender) {

    if (!respuestaP1 || !respuestaP2) //validar que ambos contesten la pregunta para pasar a siguiente
        return;

    //===================
    //Al mostrar la preguntan reseta la prioridad y las respuestas de los jugadores
    respuestaP1 = false;
    respuestaP2 = false;
    prioridad = 0;
    R1 = 0;
    R2 = 0;

    this->lbPregunta->setString("El padre de la filosofia es considerado ser:");

    item1->setString("Socrates");
    item2->setString("Rene Descartes");
    item3->setString("Aristoteles");
    item4->setString("Heraclito");

    bgItemA->setVisible(true);
    bgItemB->setVisible(true);
    bgItemC->setVisible(true);
    bgItemD->setVisible(true);

    //Para que las posiciones de los botones sean de manera aleatoria
    int posiciones[4]; //arreglo que contiene las posiciones ya obtenidas
    int pos;//guardará número random entre 0 y 3
    for (int i = 0; i < 4; i++)
    {
        do {
            pos = rand() % 4;
        } while (checkrep(pos, posiciones)); //revisa si ya existe la posición en el arreglo

        posiciones[i] = pos;
    }

    item1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[0])));
    item2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[1])));
    item3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[2])));
    item4->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[3])));

    //PROTOTIPO
    //La posicion de la primera respuesta sera la correcta
    correcta = posiciones[0] + 1;
}

void NivelDosScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

void NivelDosScene::revisarRespuesta()
{
    //IFs que revisan los 4 casos
    if (R1 == correcta && R2 != correcta)
    {
        //PLAYER 1 GANA
        p2PierdeVida();
    }
    else if (R1 != correcta && R2 == correcta)
    {
        //PLAYER 2 GANA
        p1PierdeVida();
    }
    else if (R1 != correcta && R2 != correcta)
    {
        //EMPATE
    }
    else if (R1 == correcta && R2 == correcta)
    {
        //AMBOS RESPONDEN BIEN
        if (prioridad == -1)
        {
            //PLAYER 1 GANA
            p2PierdeVida();
        }
        else if (prioridad == 1)
        {
            //PLAYER 2 GANA
            p1PierdeVida();
        }
    }
}

void NivelDosScene::p1PierdeVida()
{
    this->vidaP1--;
    p1Vidas->setString("Vidas P1: " + to_string(vidaP1));

    if (vidaP1 == 0)
    {
        //Jugador 2 Gana
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/Ofortuna.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Ofortuna.mp3");
    }
}

void NivelDosScene::p2PierdeVida()
{
    this->vidaP2--;
    p2Vidas->setString("Vidas P2: " + to_string(vidaP2));

    if (vidaP2 == 0)
    {
        //Jugador 1 gana
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/HallowedBeThyName.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/HallowedBeThyName.mp3");
    }
}
