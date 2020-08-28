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

    auto bg = cocos2d::LayerColor::create(Color4B(30, 144, 255, 255));
    this->addChild(bg, -2);

    //Título
    auto titulo = Sprite::create("images/tituloRuleta.png");
    if (titulo != nullptr) {
        titulo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titulo->getContentSize().height + 20));
        this->addChild(titulo, 1);
    }

    //Instrucciones
    auto instrucciones = Label::createWithTTF("Gire la ruleta, clickee Enter para \nvisualizar la pregunta y luego\nseleccione una opcion.", "fonts/Marker Felt.ttf", 11);
    if (instrucciones != nullptr) {
        instrucciones->setColor(Color3B::WHITE);
        // position the label on the center of the screen
        instrucciones->setPosition(Vec2(origin.x + 90, origin.y + visibleSize.height / 2 + 85));

        // add the label as a child to this layer
        this->addChild(instrucciones, 1);
    }

    //Cuadro de categorías
    auto categorias = Sprite::create("Images/categorias.png");
    if (categorias != nullptr) {
        categorias->setPosition(Vec2(origin.x + visibleSize.width / 4 - 30, origin.y + visibleSize.height / 3 + 50));
        this->addChild(categorias, 1);
    }


    //Crear el botón para girar la ruleta y posicionarlo
    ui::Button* botonS = ui::Button::create("images/P1.png", "images/P2.png");
    botonS->setPosition(Vec2(visibleSize.width / 2 + 80, (visibleSize.height /3.7)));

    //Añadirle evento al botón que hace girar la ruleta 
    botonS->addTouchEventListener(CC_CALLBACK_2(NivelUnoScene::spinR, this));

    //Creación del sprite de la ruleta y posicionarla
    Ruleta = Sprite::create("images/ruleta.png");
    Ruleta->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + 5));

    Apuntador = Sprite::create("images/guia.png");
    Apuntador->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 3.7) + 5));


    //Añadir botones y ruleta a la escena
    this->addChild(Apuntador, 2);
    this->addChild(Ruleta, 1);
    this->addChild(botonS, 2);

    //Agregar la categoría actual
    actualCategory = Sprite::create("images/empty.png");
    if (actualCategory != nullptr) {
        actualCategory->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2) + 95));
        this->addChild(actualCategory, 1);
    }

    //Se crea el label donde sale la pregunta
    pregunta = Label::createWithTTF("", "fonts/Marker Felt.ttf", 14);
    if (pregunta != nullptr) {
        pregunta->setColor(Color3B::WHITE);
        // Pone el Label a la derecha de la pantalla
        pregunta->setPosition(Vec2(origin.x + (visibleSize.width / 2) + 165, origin.y + (visibleSize.height / 2) + 75));

        // Añade el child al layer
        this->addChild(pregunta, 1);
    }

    //Se crea el sprite de la puntuación obtenida
    puntosSprite = Sprite::create("images/empty.png");
    if (puntosSprite != nullptr) {
        puntosSprite->setPosition(Vec2(visibleSize.width / 2 + 170, visibleSize.height / 2 - 65));
        this->addChild(puntosSprite, 1);
    }

    //se crea el sprite que da feedback a respuesta correcta o incorrecta
    feedback = Sprite::create("images/empty.png");
    if (feedback != nullptr) {
        feedback->setPosition(Vec2(origin.x + 130, visibleSize.height / 2 - 100));
        this->addChild(feedback, 1);
    }

    //Agrega los botones de opciones
    item1 = MenuItemFont::create("Opcion 1", CC_CALLBACK_1(NivelUnoScene::correctAnswerCallback, this));
    item2 = MenuItemFont::create("Opcion 2", CC_CALLBACK_1(NivelUnoScene::wrongAnswerCallback, this));
    item3 = MenuItemFont::create("Opcion 3", CC_CALLBACK_1(NivelUnoScene::wrongAnswerCallback, this));
    item4 = MenuItemFont::create("Opcion 4", CC_CALLBACK_1(NivelUnoScene::wrongAnswerCallback, this));

    item1->setFontSizeObj(12);
    item2->setFontSizeObj(12);
    item3->setFontSizeObj(12);
    item4->setFontSizeObj(12);

    mapad = Menu::create(item1, item2, item3, item4, NULL);
    mapad->setPosition(Point(0, 0));
    mapad->setVisible(false);
    this->addChild(mapad, 1);

    this->puntuacion = 0;
    //Se inicializa label de puntuación
    puntuacionLabel = Label::createWithTTF("Puntuacion: " + to_string(puntuacion), "fonts/Marker Felt.ttf", 18);
    if (puntuacionLabel != nullptr) {
        puntuacionLabel->setColor(Color3B::WHITE);
        // Pone el Label a la derecha de la pantalla
        puntuacionLabel->setPosition(Vec2(origin.x + (visibleSize.width / 2) + 170, origin.y + 40));

        // Añade el child al layer
        this->addChild(puntuacionLabel, 1);
    }

    //para eventos del teclado
    inicializarTeclado();

    //-------------------------
    //LOS ITERADORES SE INICIAN EN 0
    this->iteradorA = 0;
    this->iteradorH = 0;
    this->iteradorP = 0;
    this->iteradorC = 0;

    this->respuesta = false;

    this->questionShown = false;

    return true;
}

//Inicializa los eventos del teclado
void NivelUnoScene::inicializarTeclado() {
    // Crear el escuchador de eventos de teclado
    auto escuchador = EventListenerKeyboard::create();

    escuchador->onKeyPressed = [](EventKeyboard::KeyCode, Event* event) {return true; };
    escuchador->onKeyReleased = CC_CALLBACK_2(NivelUnoScene::presionarTecla, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

//Función que maneja lo que sucederá al presionar una tecla
void NivelUnoScene::presionarTecla(EventKeyboard::KeyCode key, Event* event) {

    switch (key) { //Dependiendo de la tecla que se presione suceden distintos casos

    case EventKeyboard::KeyCode::KEY_ESCAPE: //Si se presiona la tecla Esc, se llaman la función Callback respectiva
        NivelUnoScene::GoBack(this);
        break;
    case EventKeyboard::KeyCode::KEY_ENTER:
        NivelUnoScene::showQuestion(this);
        break;
    }
}

//Callback de regresar al mapa
void NivelUnoScene::GoBack(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, scene));
}

void NivelUnoScene::showQuestion(Ref* sender) {
    if (respuesta && questionShown) { //para que no sigan mostrando preguntas de la misma categoría en caso no 
                                        //se haya contestado o no se haya mostrado pregunta
        selectCategory();
        questionShown = false;
    }
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

    if (!respuesta) { //en caso de que ya esté contestada la pregunta, se puede realizar el giro de ruleta y demás

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

            actualCategory->setTexture("Images/empty.png");
            puntosSprite->setTexture("images/empty.png");
            pregunta->setString("");
            feedback->setTexture("Images/empty.png");
            mapad->setVisible(false);

            //---------------------------
            //LA VARIABLE SE RESETA CADA VEZ QUE SE GIRA EL TIMON
            respuesta = true;

            questionShown = true;

            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            log("touch moved ");
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED:
            log("Touch ended");
            break;

        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            log("touch Canceled");
            break;

        default:
            break;
        }
    }
}

//Función que selecciona la categoría en base al ángulo de la rueda
void NivelUnoScene::selectCategory()
{

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

    mapad->setVisible(true);

}

//FUNCIONES PARA LAS PREGUNTAS Y OPCIONES DE CADA CATEGORÍA

//Revisa si ya existe la posición de las opciones en el arreglo de posiciones
bool NivelUnoScene::checkrep(int n, int num[])
{
    for (int i = 0; i < 4; i++)
        if (n == num[i])
            return true;
    return false;
}

//-------------
bool NivelUnoScene::checkpreg(int n, int num[])
{
    for (int i = 0; i < 5; i++)
        if (n == num[i])
            return true;
    return false;
}

//ARTE
void NivelUnoScene::arte()
{

    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[5][5];//Prototipo: 5 preguntas, 4 respuestas por pregunta
    Questions[0][0] = "Encargado de pintar \nla capilla Sixtina:";
    Questions[1][0] = "Genio del renacimiento que \nesculpio el Moises, el \nDavid y la Pieta:";
    Questions[2][0] = "Estilo artistico que impregno\n el arte, filosofia, pintura \ny escritura, durante \nel renacimiento:";
    Questions[3][0] = "Vision del hombre reflejada \nen el arte, la politica y las \nciencias durante el \nrenamiciento:";
    Questions[4][0] = "4 genios del renacimiento \nllevados a la pantalla en los \ncomics de:";
    for (int i = 0; i < 5; i++) //la primera opción siempre será la respuesta correcta
    {

        if (i == 0) {
            Questions[i][1] = "-Miguel Angel";
            Questions[i][2] = "-Donatello";
            Questions[i][3] = "-Leonardo Da Vinci";
            Questions[i][4] = "-Francis Bacon";
        }
        else if (i == 1) {
            Questions[i][1] = "-Miguel Angel";
            Questions[i][2] = "-Rafael Sanzio";
            Questions[i][3] = "-Leonardo Da Vinci";
            Questions[i][4] = "-Galileo Galilei";
        }
        else if (i == 2) { //falta modificar desde aca
            Questions[i][1] = "-El Barroco";
            Questions[i][2] = "-El Gotico";
            Questions[i][3] = "-El Clasicismo";
            Questions[i][4] = "-Romanticismo";
        }
        else if (i == 3) {
            Questions[i][1] = "-Humanismo";
            Questions[i][2] = "-Antropocentrismo";
            Questions[i][3] = "-Paradigma Antropologico";
            Questions[i][4] = "-Teocentrismo";
        }
        else if (i == 4) {
            Questions[i][1] = "-Las Tortugas Ninjas";
            Questions[i][2] = "-Los Caballeros del Zodiaco";
            Questions[i][3] = "-Los Cuatro Fantasticos";
            Questions[i][4] = "-Enemigos en Attack on Titan";
        }

    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    //---------------
    //SE LLENA EL ARREGLO PARA VERIFICAR LAS PREGUNTAS
    if (iteradorA >= 5 || A[4] != -1)
    {
        for (int i = 0; i < 5; i++)
        {
            A[i] = -1;
            iteradorA = 0;
        }
    }

    //SE OBTIENE UN NUMERO RANDOM Y SE REVISA QUE NO ESTE EN EL ARREGLO
    int random = 0;
    do
    {
        random = (rand() % 5);
    } while (checkpreg(random, A));
    A[iteradorA] = random;
    iteradorA++;

    pregunta->setString(Questions[random][0]);

    this->actualQuestion = make_pair("arte", random);

    item1->setString(Questions[random][1]);
    item2->setString(Questions[random][2]);
    item3->setString(Questions[random][3]);
    item4->setString(Questions[random][4]);

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

    //Colocar las posiciones de cada botón
    item1->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[0])) - 25));
    item2->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[1])) - 25));
    item3->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[2])) - 25));
    item4->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[3])) - 25));

}

//CIENCIA
void NivelUnoScene::ciencia()
{

    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[5][5];//Prototipo: 5 preguntas, 4 respuestas por pregunta
    Questions[0][0] = "Uno de los precursores \nfilosofo-cientifico del \nheliocentrismo: ";
    Questions[1][0] = "Uno de los siguientes no es \nprecursor del metodo \ncientifico: ";
    Questions[2][0] = "Es uno de los precursores del \npensamiento Moderno: ";
    Questions[3][0] = "De los siguientes filosofos \nniega el geocentrismo: ";
    Questions[4][0] = "Uno de los inventos que \nsuscito un conocimiento \nilimitado, fue el de \nGutenberg: ";
    for (int i = 0; i < 5; i++) //la primera opción siempre será la respuesta correcta
    {

        if (i == 0) {
            Questions[i][1] = "-Galileo Galilei";
            Questions[i][2] = "-Tomas Moro";
            Questions[i][3] = "-Platon";
            Questions[i][4] = "-Ptolomeo";
        }
        else if (i == 1) {
            Questions[i][1] = "-Nicolas Maquiavelo";
            Questions[i][2] = "-Francis Bacon";
            Questions[i][3] = "-Rene Descartes";
            Questions[i][4] = "-Galileo Galilei";
        }
        else if (i == 2) {
            Questions[i][1] = "-Rene Descartes";
            Questions[i][2] = "-Isaac Newton";
            Questions[i][3] = "-Leonardo Da Vinci";
            Questions[i][4] = "-Erasmo de Roterdam";
        }
        else if (i == 3) {
            Questions[i][1] = "-Nicolas Copernico";
            Questions[i][2] = "-Tomas de Aquino";
            Questions[i][3] = "-Aristoteles";
            Questions[i][4] = "-Platon";
        }
        else if (i == 4) {
            Questions[i][1] = "-La imprenta";
            Questions[i][2] = "-El Astrolabio";
            Questions[i][3] = "-La Nao y la Carabela";
            Questions[i][4] = "-El Telescopio";
        }

    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    //---------------
    //SE LLENA EL ARREGLO PARA VERIFICAR LAS PREGUNTAS
    if (iteradorC >= 5 || C[4] != -1)
    {
        for (int i = 0; i < 5; i++)
        {
            C[i] = -1;
            iteradorC = 0;
        }
    }

    //SE OBTIENE UN NUMERO RANDOM Y SE REVISA QUE NO ESTE EN EL ARREGLO
    int random = 0;
    do
    {
        random = (rand() % 5);
    } while (checkpreg(random, C));
    C[iteradorC] = random;
    iteradorC++;

    pregunta->setString(Questions[random][0]);

    this->actualQuestion = make_pair("ciencia", random);

    item1->setString(Questions[random][1]);
    item2->setString(Questions[random][2]);
    item3->setString(Questions[random][3]);
    item4->setString(Questions[random][4]);

    //Para que las posiciones de los botones sean de manera aleatoria
    int posiciones[4]; //arreglo que contiene las posiciones ya obtenidas
    int pos;//guardará número random entre 0 y 2
    for (int i = 0; i < 4; i++)
    {
        do {
            pos = rand() % 4;
        } while (checkrep(pos, posiciones)); //revisa si ya existe la posición en el arreglo

        posiciones[i] = pos;
    }

    //Colocar las posiciones de cada botón
    item1->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[0])) - 25));
    item2->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[1])) - 25));
    item3->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[2])) - 25));
    item4->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[3])) - 25));
}

//POLÍTICA
void NivelUnoScene::politica()
{
    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[5][5];//Prototipo: 5 preguntas, 4 respuestas por pregunta
    Questions[0][0] = "Durante el renacimiento, el \nmodelo de gobierno es \nuno de los siguientes: ";
    Questions[1][0] = "De los siguientes aconteci-\nmientos, seleccione el que \ninicia el periodo moderno: ";
    Questions[2][0] = "Durante el siglo XV, la \nsociedad se estratifica en 3 \nestamentos definidos: ";
    Questions[3][0] = "Autor del realismo politico, \nbasado en un orden definido, \nexplicacion y sugerencias \nde como gobernar: ";
    Questions[4][0] = "Terminada la edad media, \nen el contexto de la \npolitica resulta que: ";
    for (int i = 0; i < 5; i++) //la primera opción siempre será la respuesta correcta
    {

        if (i == 0) {
            Questions[i][1] = "-Monarquia Absoluta";
            Questions[i][2] = "-Tirania Republicana";
            Questions[i][3] = "-Democracia Participativa";
            Questions[i][4] = "-Liberalismo Politico";
        }
        else if (i == 1) {
            Questions[i][1] = "-Tratado de paz de Westfalia";
            Questions[i][2] = "-Toma de Constantinopla";
            Questions[i][3] = "-Toma de la Bastilla";
            Questions[i][4] = "-La ruta de la seda";
        }
        else if (i == 2) {
            Questions[i][1] = "-Nobleza, clero y estado llano";
            Questions[i][2] = "-Clase Media, baja y alta";
            Questions[i][3] = "-Artesanos, guardianes y \ngobernantes";
            Questions[i][4] = "-Presidente, Ministro y estado";
        }
        else if (i == 3) {
            Questions[i][1] = "-Nicolas Maquiavelo";
            Questions[i][2] = "-Tomas Moro";
            Questions[i][3] = "-Jean Bodin";
            Questions[i][4] = "-Erasmo de Rotterdam";
        }
        else if (i == 4) {
            Questions[i][1] = "-La Iglesia pierde el \npapel rector.";
            Questions[i][2] = "-La Iglesia resalta su poder.";
            Questions[i][3] = "-La Iglesia evangelica \nentra en politica.";
            Questions[i][4] = "-No ocurrio nada.";
        }

    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    //---------------
    //SE LLENA EL ARREGLO PARA VERIFICAR LAS PREGUNTAS
    if (iteradorP >= 5 || P[4] != -1)
    {
        for (int i = 0; i < 5; i++)
        {
            P[i] = -1;
            iteradorP = 0;
        }
    }

    //SE OBTIENE UN NUMERO RANDOM Y SE REVISA QUE NO ESTE EN EL ARREGLO
    int random = 0;
    do
    {
        random = (rand() % 5);
    } while (checkpreg(random, P));
    P[iteradorP] = random;
    iteradorP++;

    pregunta->setString(Questions[random][0]);

    this->actualQuestion = make_pair("politica", random);

    item1->setString(Questions[random][1]);
    item2->setString(Questions[random][2]);
    item3->setString(Questions[random][3]);
    item4->setString(Questions[random][4]);

    //Para que las posiciones de los botones sean de manera aleatoria
    int posiciones[4]; //arreglo que contiene las posiciones ya obtenidas
    int pos;//guardará número random entre 0 y 2
    for (int i = 0; i < 4; i++)
    {
        do {
            pos = rand() % 4;
        } while (checkrep(pos, posiciones)); //revisa si ya existe la posición en el arreglo

        posiciones[i] = pos;
    }

    //Colocar las posiciones de cada botón
    item1->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (25 * posiciones[0])) - 25));
    item2->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (25 * posiciones[1])) - 25));
    item3->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (25 * posiciones[2])) - 25));
    item4->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (25 * posiciones[3])) - 25));
}

//HISTORIA
void NivelUnoScene::historia()
{
    //Crea arreglo bidimensional tipo string donde se almacenan preguntas y respuestas
    string Questions[5][5];//Prototipo: 5 preguntas, 4 respuestas por pregunta
    Questions[0][0] = "Despues del feudalismo \nmedieval surge esta \nnueva clase social: ";
    Questions[1][0] = "Monarquia europea \ncentralizada que nace \nen el renacimiento: ";
    Questions[2][0] = "Dos ciudades-estado de Italia \nenfrentadas entre si, \nantes de la consolidacion \ndel estado moderno: ";
    Questions[3][0] = "La toma de Constantinopla \nsupone un bloqueo comercial \nentre Europa y Asia, \n ocurrio en: ";
    Questions[4][0] = "Resurge el interes por \nGrecia y Roma, junto al \ndeclive del sistema feudal e\n innovaciones entre ellas: ";
    for (int i = 0; i < 5; i++) //la primera opción siempre será la respuesta correcta
    {

        if (i == 0) {
            Questions[i][1] = "-La burguesia";
            Questions[i][2] = "-La monarquia";
            Questions[i][3] = "-El mercantilismo";
            Questions[i][4] = "-El proletariado";
        }
        else if (i == 1) {
            Questions[i][1] = "-Inglaterra";
            Questions[i][2] = "-Grecia";
            Questions[i][3] = "-Yugoslavia";
            Questions[i][4] = "-Egipto";
        }
        else if (i == 2) {
            Questions[i][1] = "-Florencia y Napoli";
            Questions[i][2] = "-Amsterdam y Cracovia";
            Questions[i][3] = "-Reims y Colonia";
            Questions[i][4] = "-Milan y Lourdes";
        }
        else if (i == 3) {
            Questions[i][1] = "-Estambul en Turquia";
            Questions[i][2] = "-Mesopotamia";
            Questions[i][3] = "-Eslovaquia";
            Questions[i][4] = "-China";
        }
        else if (i == 4) {
            Questions[i][1] = "-La imprenta y brujula";
            Questions[i][2] = "-La rueda y escritura";
            Questions[i][3] = "-Las maquinas a vapor";
            Questions[i][4] = "-Las maquinas de produccion \nen masa";
        }

    }

    //Luego de crear el arreglo, se crea un Label con el texto guardado al azar
    //---------------
    //SE LLENA EL ARREGLO PARA VERIFICAR LAS PREGUNTAS
    if (iteradorH >= 5 || H[4] != -1)
    {
        for (int i = 0; i < 5; i++)
        {
            H[i] = -1;
            iteradorH = 0;
        }
    }

    //SE OBTIENE UN NUMERO RANDOM Y SE REVISA QUE NO ESTE EN EL ARREGLO
    int random = 0;
    do
    {
        random = (rand() % 5);
    } while (checkpreg(random, H));
    H[iteradorH] = random;
    iteradorH++;

    pregunta->setString(Questions[random][0]);

    this->actualQuestion = make_pair("historia", random);

    item1->setString(Questions[random][1]);
    item2->setString(Questions[random][2]);
    item3->setString(Questions[random][3]);
    item4->setString(Questions[random][4]);

    //Para que las posiciones de los botones sean de manera aleatoria
    int posiciones[4]; //arreglo que contiene las posiciones ya obtenidas
    int pos;//guardará número random entre 0 y 2
    for (int i = 0; i < 4; i++)
    {
        do {
            pos = rand() % 4;
        } while (checkrep(pos, posiciones)); //revisa si ya existe la posición en el arreglo

        posiciones[i] = pos;
    }

    //Colocar las posiciones de cada botón
    item1->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[0])) - 25));
    item2->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[1])) - 25));
    item3->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[2])) - 25));
    item4->setPosition(Vec2(visibleSize.width / 2 + 160, (visibleSize.height / 2 + (20 * posiciones[3])) - 25));
}

//Ambos metodos agregan los sprites de los puntajes

void NivelUnoScene::correctAnswerCallback(Ref* sender)
{
    //IF QUE SE ASEGURA QUE AUN NO SE HAYA PRESIONADO NINGUNA OTRA RESPUESTA
    if (respuesta == true)
    {
        respuesta = false;
        puntosSprite->setTexture("images/+100puntos.png");
        this->puntuacion += 100;
        puntuacionLabel->setString("Puntuacion: " + to_string(puntuacion));

        //Settear la imagen del feedback en caso de que seleccionara correctamente opción de Arte
        if (this->actualQuestion.first == "arte" && this->actualQuestion.second == 0)
            feedback->setTexture("images/arte1Correcta.png");
        else if (this->actualQuestion.first == "arte" && this->actualQuestion.second == 1)
            feedback->setTexture("images/arte2Correcta.png");
        else if (this->actualQuestion.first == "arte" && this->actualQuestion.second == 2)
            feedback->setTexture("images/arte3Correcta.png");
        else if (this->actualQuestion.first == "arte" && this->actualQuestion.second == 3)
            feedback->setTexture("images/arte4Correcta.png");
        else if (this->actualQuestion.first == "arte" && this->actualQuestion.second == 4)
            feedback->setTexture("images/arte5Correcta.png");
        //Settear la imagen del feedback en caso de que seleccionara correctamente opción de Ciencia
        if (this->actualQuestion.first == "ciencia" && this->actualQuestion.second == 0)
            feedback->setTexture("images/ciencia1Correcta.png");
        else if (this->actualQuestion.first == "ciencia" && this->actualQuestion.second == 1)
            feedback->setTexture("images/ciencia2Correcta.png");
        else if (this->actualQuestion.first == "ciencia" && this->actualQuestion.second == 2)
            feedback->setTexture("images/ciencia3Correcta.png");
        else if (this->actualQuestion.first == "ciencia" && this->actualQuestion.second == 3)
            feedback->setTexture("images/ciencia4Correcta.png");
        else if (this->actualQuestion.first == "ciencia" && this->actualQuestion.second == 4)
            feedback->setTexture("images/ciencia5Correcta.png");
        //Settear la imagen del feedback en caso de que seleccionara correctamente opción de Política
        if (this->actualQuestion.first == "politica" && this->actualQuestion.second == 0)
            feedback->setTexture("images/politica1Correcta.png");
        else if (this->actualQuestion.first == "politica" && this->actualQuestion.second == 1)
            feedback->setTexture("images/politica2Correcta.png");
        else if (this->actualQuestion.first == "politica" && this->actualQuestion.second == 2)
            feedback->setTexture("images/politica3Correcta.png");
        else if (this->actualQuestion.first == "politica" && this->actualQuestion.second == 3)
            feedback->setTexture("images/politica4Correcta.png");
        else if (this->actualQuestion.first == "politica" && this->actualQuestion.second == 4)
            feedback->setTexture("images/politica5Correcta.png");
        //Settear la imagen del feedback en caso de que seleccionara correctamente opción de Historia
        if (this->actualQuestion.first == "historia" && this->actualQuestion.second == 0)
            feedback->setTexture("images/historia1Correcta.png");
        else if (this->actualQuestion.first == "historia" && this->actualQuestion.second == 1)
            feedback->setTexture("images/historia2Correcta.png");
        else if (this->actualQuestion.first == "historia" && this->actualQuestion.second == 2)
            feedback->setTexture("images/historia3Correcta.png");
        else if (this->actualQuestion.first == "historia" && this->actualQuestion.second == 3)
            feedback->setTexture("images/historia4Correcta.png");
        else if (this->actualQuestion.first == "historia" && this->actualQuestion.second == 4)
            feedback->setTexture("images/historia5Correcta.png");
    }
}

void NivelUnoScene::wrongAnswerCallback(Ref* sender)
{
    //IF QUE SE ASEGURA QUE AUN NO SE HAYA PRESIONADO NINGUNA OTRA RESPUESTA
    if (respuesta == true)
    {
        respuesta = false;
        //puntosSprite->setTexture("images/-50puntos.png");
       // this->puntuacion -= 50;
        puntuacionLabel->setString("Puntuacion: " + to_string(puntuacion));

        if (this->actualQuestion.first == "arte" || this->actualQuestion.first == "historia")
            feedback->setTexture("images/cheers1.png");

        else if (this->actualQuestion.first == "politica" || this->actualQuestion.first == "ciencia")
            feedback->setTexture("images/cheers2.png");
    }
}
