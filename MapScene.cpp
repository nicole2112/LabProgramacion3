#include "MapScene.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
    return MapScene::create();
}

bool MapScene::init() 
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    log("Initializing map scene");

    return true;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}