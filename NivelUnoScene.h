#ifndef __NIVELUNO_SCENE_H__
#define __NIVELUNO_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
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

    //Función para seleccionar la categoría en base a la ruleta
    void selectCategory();
    int angle, vueltas;

    Size visibleSize;
    Label* pregunta; //label que contiene la pregunta a mostrarse
    //MenuItemFont* opcion1; // opciones de las preguntas
    //MenuItemFont* opcion2; 
    //MenuItemFont* opcion3;

    ui::Button* opcion1;
    ui::Button* opcion2;
    ui::Button* opcion3;
    bool checkrep(int, int[]);

    //Funciones para las preguntas de cada categoría
    void arte();
    void historia();
    void politica();
    void ciencia();

    //Sprite que contiene la imagen con el título respectivo a cada categoría
    Sprite* actualCategory;

    Sprite* puntosSprite;

    //Funciones callback
    void GoBack(Ref* pSender);
    void spinR( Ref* sender, ui::Widget::TouchEventType type);
    
    void addSprite();
    void addSpriteBad();

};

#endif // __NIVELUNO_SCENE_H__
