//Leo Pazzetti
#include "NivelDosScene.h"
#include "MapScene.h"

USING_NS_CC;


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

    auto teclasJugador1 = Sprite::create("images/teclasJugador1.png");
    if (teclasJugador1 != nullptr) {
        teclasJugador1->setPosition(Vec2(origin.x + visibleSize.width / 2  - 210 , origin.y + visibleSize.height / 2 - 95));
        this->addChild(teclasJugador1, 1);
    }

    auto teclasJugador2 = Sprite::create("images/teclasJugador2.png");
    if (teclasJugador2 != nullptr) {
        teclasJugador2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 130, origin.y + visibleSize.height / 2 - 95));
        this->addChild(teclasJugador2, 1);
    }

    //T�tulo
    auto titulo = Sprite::create("images/tituloEpistemefighter.jpg");
    if (titulo != nullptr) {
        titulo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titulo->getContentSize().height + 20));
        this->addChild(titulo, 0);
    }

    //Iniciar label para preguntas con instrucciones breves
    lbPregunta = Label::createWithTTF("Objetivo: Ganar la batalla entre empiristas y racionalistas \ncontestando correcta y velozmente cada pregunta. \nPresione Enter para iniciar.", 
        "fonts/arial.ttf", 12);
    lbPregunta->setColor(Color3B::BLACK);
    lbPregunta->setAlignment(TextHAlignment::CENTER);
    lbPregunta->setPosition(Vec2(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height / 2 + 90));
    this->addChild(lbPregunta, 2);

    //Inicializar opciones de respuestas
    item1 = Label::createWithTTF(" ", "fonts/arial.ttf", 12);
    item1->setColor(Color3B::BLACK);
    item1->setAlignment(TextHAlignment::LEFT);
    item1->setAnchorPoint(Vec2(0,0));
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

    //inicializar eventos del teclado
    inicializarTeclado();

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

//Funci�n que maneja lo que suceder� al presionar una tecla
void NivelDosScene::presionarTecla(EventKeyboard::KeyCode key, Event* event) {

    switch (key) { //Dependiendo de la tecla que se presione suceden distintos casos

    case EventKeyboard::KeyCode::KEY_ESCAPE: //Si se presiona la tecla Esc, se llaman la funci�n Callback respectiva
        NivelDosScene::GoBack(this);
        break;
    case EventKeyboard::KeyCode::KEY_ENTER:
        NivelDosScene::showQuestion(this);
        break;
    case EventKeyboard::KeyCode::KEY_1:
        break;
    }
}

//Revisa si ya existe la posici�n de las opciones en el arreglo de posiciones
bool NivelDosScene::checkrep(int n, int num[])
{
    for (int i = 0; i < 4; i++)
        if (n == num[i])
            return true;
    return false;
}

void NivelDosScene::showQuestion(cocos2d::Ref* sender) {
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
    int pos;//guardar� n�mero random entre 0 y 3
    for (int i = 0; i < 4; i++)
    {
        do {
            pos = rand() % 4;
        } while (checkrep(pos, posiciones)); //revisa si ya existe la posici�n en el arreglo

        posiciones[i] = pos;
    }

    item1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[0])));
    item2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[1])));
    item3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[2])));
    item4->setPosition(Vec2(origin.x + visibleSize.width / 2 - 90, origin.y + visibleSize.height / 2 - (40 * posiciones[3])));
}

void NivelDosScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}