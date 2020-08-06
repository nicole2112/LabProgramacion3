
#ifndef __PUNTUACION_SCENE_H__
#define __PUNTUACION_SCENE_H__

#include "cocos2d.h"
#include "CCEventKeyboard.h"
USING_NS_CC;
class Puntuacion : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void salirCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void puntuacionCloseCallback(cocos2d::Ref* pSender);

   // void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void inicializarTeclado(void);
    void presionarTecla(EventKeyboard::KeyCode key, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(Puntuacion);

    cocos2d::Sprite* mySprite;

    void GoBack(Ref* pSender);

};

#endif // __PUNTUACION_SCENE_H__
