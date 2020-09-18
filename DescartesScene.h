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

    //Variable que determina si se cambia de escuela
    bool cambiarEscena;

    // Funciones para inicializar teclado y manejar sus eventos
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    void GoBack(Ref* pSender);
    std::vector<std::vector<std::string>> vectorEpis;
    void cargarPreguntasEpis();
    void showQuestion(Ref*);
    bool checkrep(int, int[]);
    bool checkpreg(int, int[], int);
    int A[5];
};

#endif // !DESCARTES_SCENE_H
