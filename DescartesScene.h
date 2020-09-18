#ifndef DESCARTES_SCENE_H
#define DESCARTES_SCENE_H

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DescartesScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(DescartesScene);

    //====================
    Point origin;
    Size visibleSize;
    int iteradorepis;

    Label* lbPregunta;
    Label* item1;
    Label* item2;
    Label* item3;
    Label* item4;

    Sprite* bgItemA;
    Sprite* bgItemB;
    Sprite* bgItemC;
    Sprite* bgItemD;

    //Para guardar la respuesta correcta
    int respCorrecta;

    bool respondido;

    //Variable que determina si se cambia de escuela
    bool cambiarEscena;
    int contadorPreguntas;

    void finEscena();

    // Funciones para inicializar teclado y manejar sus eventos
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    Sprite* feedback;
    void respuestaCorrecta();
    void respuestaIncorrecta();

    void GoBack(Ref* pSender);
    void showKant(Ref* pSender);

    std::vector<std::vector<std::string>> vectorDescartes;
    void cargarPreguntasEpis();
    void showQuestion(Ref*);
    bool checkrep(int, int[]);
    bool checkpreg(int, std::vector<int>, int);

    std::vector<int> A;
};

#endif // !DESCARTES_SCENE_H
