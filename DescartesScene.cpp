#include "DescartesScene.h"
#include "MapScene.h"
#include "KantScene.h"
#include <string>
#include <iostream>
#include <fstream>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

Scene* DescartesScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = DescartesScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DescartesScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto aula = Sprite::create("Images/lab.jpg");
    aula->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(aula, -2);

    auto desc = Sprite::create("Images/bandoDescartes.png");
    desc->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 2 - 45));
    this->addChild(desc, -1);

    //================================================
    //Iniciar label para preguntas con instrucciones breves
    lbPregunta = Label::createWithTTF("Objetivo: Contestar todas las preguntas \nde la escuela de Descartes.\nPresione Enter para iniciar", "fonts/arial.ttf", 12);
    lbPregunta->setColor(Color3B::BLACK);
    lbPregunta->setAlignment(TextHAlignment::CENTER);
    lbPregunta->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 70));
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

    //Cargar preguntas
    cargarPreguntasEpis();

    for (int i = 0; i < vectorDescartes.size(); i++)
    {
        A.push_back(-1);
        iteradorepis = 0;
    }

    //inicializar eventos del teclado
    inicializarTeclado();

    this->respCorrecta = 0;
    this->respondido = true;

    //se crea el sprite que da feedback a respuesta correcta o incorrecta
    feedback = Sprite::create("images/empty.png");
    if (feedback != nullptr) {
        feedback->setPosition(Vec2(origin.x + 400, visibleSize.height / 2 - 100));
        this->addChild(feedback, 3);
    }

    this->cambiarEscena = false;
    this->contadorPreguntas = 0;

    return true;
}

//==============================================

//Inicializa los eventos del teclado
void DescartesScene::inicializarTeclado() {
    // Crear el escuchador de eventos de teclado
    auto escuchador = EventListenerKeyboard::create();

    escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
    escuchador->onKeyReleased = CC_CALLBACK_2(DescartesScene::presionarTecla, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

void DescartesScene::presionarTecla(EventKeyboard::KeyCode key, Event* event)
{
    switch (key)
    {
    case EventKeyboard::KeyCode::KEY_ESCAPE:
        DescartesScene::GoBack(this);
        break;
    case EventKeyboard::KeyCode::KEY_ENTER:
        if (this->cambiarEscena) {
            if (this->contadorPreguntas > this->vectorDescartes.size())
                DescartesScene::showKant(this);
            else {
                this->finEscena();
                contadorPreguntas++;
            }
        }
        else
            DescartesScene::showQuestion(this);
        break;
    case EventKeyboard::KeyCode::KEY_1:

        if (this->respCorrecta == 1) {
            this->respuestaCorrecta();
        }
        else {
            this->respuestaIncorrecta();
        }

        break;
    case EventKeyboard::KeyCode::KEY_2:

        if (this->respCorrecta == 2) {
            this->respuestaCorrecta();
        }
        else {
            this->respuestaIncorrecta();
        }

        break;
    case EventKeyboard::KeyCode::KEY_3:
        if (this->respCorrecta == 3) {
            this->respuestaCorrecta();
        }
        else {
            this->respuestaIncorrecta();
        }
        break;
    case EventKeyboard::KeyCode::KEY_4:

        if (this->respCorrecta == 4) {
            this->respuestaCorrecta();
        }
        else {
            this->respuestaIncorrecta();
        }

        break;
    }
}

void DescartesScene::showKant(cocos2d::Ref* pSender)
{
    auto scene = KantScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, scene));
}


void DescartesScene::GoBack(cocos2d::Ref* pSender)
{
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

void DescartesScene::cargarPreguntasEpis() {

    ifstream desIn("DescartesScenePreguntas.txt", ios::in);

    if (!desIn)
    {
        cout << "Error al abrir archivo DescartesScenePreguntas.txt" << endl;
        return;
    }

    string line;

    while (getline(desIn, line)) {

        vector <string> Q;
        string pregunta = "";
        string respuesta = "";
        bool preguntaAlmacenada = 0;

        for (int i = 0; i < line.size(); i++) {
            if (line.at(i) == ':' && !preguntaAlmacenada) {
                pregunta = pregunta + line.at(i);
                Q.push_back(pregunta);
                preguntaAlmacenada = 1;
            }
            else if (!preguntaAlmacenada) {
                if (line.at(i) == '/') {
                    pregunta = pregunta + "\n";
                }
                else {
                    pregunta = pregunta + line.at(i);
                }
            }
            else if (line.at(i) == '-') {

                Q.push_back(respuesta);
                respuesta = "";
            }
            else {
                if (line.at(i) == '/')
                    respuesta = respuesta + "\n";
                else
                    respuesta = respuesta + line.at(i);

            }
        }
        this->vectorDescartes.push_back(Q);
    }

    desIn.close();
}

bool DescartesScene::checkpreg(int n, std::vector<int> num, int size)
{
    for (int i = 0; i < size; i++)
        if (n == num[i])
            return true;
    return false;
}

bool DescartesScene::checkrep(int n, int num[])
{
    for (int i = 0; i < 4; i++)
        if (n == num[i])
            return true;
    return false;
}

void DescartesScene::showQuestion(Ref* sender)
{
    //Validar que se haya contestado la pregunta
    if (!this->respondido)
        return;

    //reiniciar variable
    this->respondido = false;

    this->contadorPreguntas++;

    //Cuando ya se hayan pasado todas las preguntas
    if (contadorPreguntas == vectorDescartes.size())
        this->cambiarEscena = true;

    feedback->setTexture("images/empty.png");

    //SE LLENA EL ARREGLO PARA VERIFICAR LAS PREGUNTAS
    if (iteradorepis >= vectorDescartes.size() || A[vectorDescartes.size() - 1] != -1)
    {
        for (int i = 0; i < vectorDescartes.size(); i++)
        {
            A[i] = -1;
            iteradorepis = 0;
        }
    }

    int random = 0;

    do {
        random = (rand() % vectorDescartes.size());
    } while (checkpreg(random, A, vectorDescartes.size()));
    A[iteradorepis] = random;
    iteradorepis++;

    lbPregunta->setString(vectorDescartes[random][0]);

    item1->setString(vectorDescartes[random][1]);
    item2->setString(vectorDescartes[random][2]);
    item3->setString(vectorDescartes[random][3]);
    item4->setString(vectorDescartes[random][4]);

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

    //La posicion de la primera respuesta sera la correcta
    this->respCorrecta = posiciones[0] + 1;
}


void DescartesScene::respuestaCorrecta() {
    if (!this->respondido) {
        this->respondido = true;
        feedback->setTexture("Images/cheersCorrect.png");
    }
}

void DescartesScene::respuestaIncorrecta() {
    if (!this->respondido) {
        this->respondido = true;
        feedback->setTexture("Images/cheers1.png");
    }
}

void DescartesScene::finEscena() {
    bgItemA->setVisible(false);
    bgItemB->setVisible(false);
    bgItemC->setVisible(false);
    bgItemD->setVisible(false);
    item1->setVisible(false);
    item2->setVisible(false);
    item3->setVisible(false);
    item4->setVisible(false);
    feedback->setVisible(false);
    lbPregunta->setVisible(false);

    auto lbGanar = Label::createWithTTF("¡Buen trabajo!", "fonts/arial.ttf", 25);
    lbGanar->setColor(Color3B::BLACK);
    lbGanar->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 70));
    this->addChild(lbGanar, 2);

    auto lbSalir = Label::createWithTTF("Presione Enter.", "fonts/arial.ttf", 14);
    lbSalir->setColor(Color3B::BLACK);
    lbSalir->setAlignment(TextHAlignment::CENTER);
    lbSalir->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(lbSalir, 2);
}
