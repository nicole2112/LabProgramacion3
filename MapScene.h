#pragma once

#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "cocos2d.h"
#include "MainMenuScene.h"

USING_NS_CC;


class MapScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MapScene);

    //funciones callback
    void regresarCloseCallback(cocos2d::Ref* pSender);
    void Play(Ref* pSender);
    void NivelDos(Ref* pSender);
    void NivelTres(Ref* pSender);
};


#endif // !MAPSCENE_H
