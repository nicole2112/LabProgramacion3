#ifndef __NIVELUNO_SCENE_H__
#define __NIVELUNO_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <utility>
#include <vector>
#include <fstream>

class NivelUnoScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NivelUnoScene);

private:

    cocos2d::Sprite* Ruleta;

    int puntuacion;
    Label* puntuacionLabel;

    //Función para seleccionar la categoría en base a la ruleta
    void selectCategory();
    int angle, vueltas;

    Size visibleSize;
    Label* pregunta; //label que contiene la pregunta a mostrarse

    //opciones a cada pregunta
    MenuItemLabel* item1;
    MenuItemLabel* item2;
    MenuItemLabel* item3;
    MenuItemLabel* item4;
    Menu* mapad;

    bool checkrep(int, int[]);
    bool questionShown;
    //-------------
    bool checkpreg(int, int[], int);
    bool respuesta;
    //Iteradores y arreglos que manejan preguntas
    int iteradorA;
    int iteradorH;
    int iteradorP;
    int iteradorC;
    int A[5];
    int H[5];
    int P[5];
    int C[5];

    //Funciones para las preguntas de cada categoría
    void arte();
    void historia();
    void politica();
    void ciencia();

    void cargarArte();
    void cargarHistoria();

    std::vector<std::vector<std::string>> vectorArte;
    std::vector<std::vector<std::string>> vectorHistoria;

    //Sprite que contiene la imagen con el título respectivo a cada categoría
    Sprite* actualCategory;

    Sprite* puntosSprite;

    Sprite* feedback;

    Sprite* Apuntador;

    std::pair<std::string, int> actualQuestion; //primero categoria, segundo número de pregunta

    // Funciones para inicializar teclado y manejar sus eventos
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    //Funciones callback
    void GoBack(Ref* pSender);
    void spinR(Ref* sender, ui::Widget::TouchEventType type);
    void correctAnswerCallback(Ref* sender);
    void wrongAnswerCallback(Ref* sender);
    void showQuestion(Ref*);

};

#endif // __NIVELUNO_SCENE_H__
