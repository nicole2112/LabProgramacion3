#pragma once
#ifndef __NIVELDOS_SCENE_H__
#define __NIVELDOS_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

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

    cocos2d::Sprite* mySprite;
    Label* lbPregunta;
    Label* item1;
    Label* item2;
    Label* item3;
    Label* item4;
    Label* p1Vidas;
    Label* p2Vidas;

    Sprite* bgItemA;
    Sprite* bgItemB;
    Sprite* bgItemC;
    Sprite* bgItemD;

    void GoBack(Ref* pSender);
    void showQuestion(Ref*);

    bool checkrep(int, int[]);
    void revisarRespuesta();

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
