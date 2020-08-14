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

    cocos2d::Sprite* Ruleta;

    //Funci�n para seleccionar la categor�a en base a la ruleta
    void selectCategory();
    int angle, vueltas;

    Size visibleSize;
    Label* pregunta;

    //Funciones para las preguntas de cada categor�a
    void arte();
    void historia();
    void politica();
    void ciencia();

    //Sprite que contiene la imagen con el t�tulo respectivo a cada categor�a
    Sprite* actualCategory;

    Sprite* puntosSprite;

    //Funciones callback
    void GoBack(Ref* pSender);
    void spinR( Ref* sender, ui::Widget::TouchEventType type);
    
    void addSprite();
    void addSpriteBad();

};

#endif // __NIVELUNO_SCENE_H__
