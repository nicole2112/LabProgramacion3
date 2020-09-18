#pragma once
#ifndef __NIVELDOS_SCENE_H__
#define __NIVELDOS_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include <utility>
#include <vector>
#include <fstream>

class NivelDosScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NivelDosScene);

private:

    Size visibleSize;
    Point origin;

    // Funciones para inicializar teclado y manejar sus eventos
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    int iteradorepis;

    Sprite* titulo;

    cocos2d::Sprite* mySprite;
    Label* lbPregunta;
    Label* item1;
    Label* item2;
    Label* item3;
    Label* item4;
    Label* lbSalir;

    Sprite* bgItemA;
    Sprite* bgItemB;
    Sprite* bgItemC;
    Sprite* bgItemD;
    Sprite* p1Vida;
    Sprite* p2Vida;

    void GoBack(Ref* pSender);
    void showQuestion(Ref*);

    bool checkrep(int, int[]);
    void revisarRespuesta();
    //---------------Marvin, Agregue metodos para las preguntas y text file
    bool checkpreg(int, std::vector<int>, int);
    std::vector<std::vector<std::string>> vectorEpis;
    void cargarPreguntasEpis();
    std::vector<int> A;


    void p1PierdeVida();
    void p2PierdeVida();

    void stopMusic(float);

    //============================
    int prioridad;
    bool respuestaP1;
    bool respuestaP2;
    int correcta;
    int R1;
    int R2;
    int vidaP1;
    int vidaP2;
};
#endif // __NIVELDOS_SCENE_H__

