#ifndef __NIVELUNO_SCENE_H__
#define __NIVELUNO_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <utility>

class NivelUnoScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(NivelUnoScene);

private:

    cocos2d::Sprite* Ruleta;

    int puntuacion;
    Label* puntuacionLabel;

    //Funci�n para seleccionar la categor�a en base a la ruleta
    void selectCategory();
    int angle, vueltas;

    Size visibleSize;
    Label* pregunta; //label que contiene la pregunta a mostrarse

    //opciones a cada pregunta
    MenuItemFont* item1;
    MenuItemFont* item2;
    MenuItemFont* item3;
    MenuItemFont* item4;
    Menu* mapad;

    bool checkrep(int, int[]);

    //Funciones para las preguntas de cada categor�a
    void arte();
    void historia();
    void politica();
    void ciencia();

    //Sprite que contiene la imagen con el t�tulo respectivo a cada categor�a
    Sprite* actualCategory;

    Sprite* puntosSprite;

    Sprite* feedback;

    std::pair<std::string, int> actualQuestion; //primero categoria, segundo n�mero de pregunta

    // Funciones para inicializar teclado y manejar sus eventos
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    //Funciones callback
    void GoBack(Ref* pSender);
    void spinR( Ref* sender, ui::Widget::TouchEventType type);
    void correctAnswerCallback(Ref* sender);
    void wrongAnswerCallback(Ref* sender);
    void showQuestion(Ref*);

};

#endif // __NIVELUNO_SCENE_H__
