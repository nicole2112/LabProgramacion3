#pragma once

#ifndef _MAP_SCENE_H
#define _MAP_SCENE_H

#include "cocos2d.h"

class Map : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

};


#endif // !MAPSCENE_H

