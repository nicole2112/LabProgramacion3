#include "DescartesScene.h"
#include "MapScene.h"
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
    lbPregunta = Label::createWithTTF("Objetivo: Contestar todas las preguntas \nde la escuela de Kant.\nPresione Enter para iniciar", "fonts/arial.ttf", 12);
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

    //inicializar eventos del teclado
    inicializarTeclado();

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
        DescartesScene::showQuestion(this);
        break;
    }
}

void DescartesScene::GoBack(cocos2d::Ref* pSender)
{
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

void DescartesScene::cargarPreguntasEpis() {

    ifstream episIn("DescartesScenePreguntas.txt", ios::in);

    if (!episIn)
    {
        cout << "Error al abrir archivo DescartesScenePreguntas.txt" << endl;
        return;
    }

    string line;

    while (getline(episIn, line)) {

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
        this->vectorEpis.push_back(Q);
    }
}

bool DescartesScene::checkpreg(int n, int num[], int size)
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
    if (iteradorepis >= vectorEpis.size() || A[vectorEpis.size() - 1] != -1)
    {
        for (int i = 0; i < vectorEpis.size(); i++)
        {
            A[i] = -1;
            iteradorepis = 0;
        }
    }

    int random = 0;

    do {
        random = (rand() % 4);
    } while (checkpreg(random, A, vectorEpis.size()));
    A[iteradorepis] = random;
    iteradorepis++;

    if (A[4] != NULL) {

        for (int i = 0; i <= 4; i++) {
            A[i] = NULL;
            iteradorepis = 0;

        }

    }

    lbPregunta->setString(vectorEpis[random][0]);

    item1->setString(vectorEpis[random][1]);
    item2->setString(vectorEpis[random][2]);
    item3->setString(vectorEpis[random][3]);
    item4->setString(vectorEpis[random][4]);

    /*bgItemA->setVisible(true);
    bgItemB->setVisible(true);
    bgItemC->setVisible(true);
    bgItemD->setVisible(true);*/

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
}
