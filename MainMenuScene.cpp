#include "MainMenuScene.h"
#include <cocos\base\ccTypes.cpp>
#include <cocos\ui\UIScale9Sprite.h>
#include "MapScene.h"
#include "../proj.win32/MapScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    log("Initializing scene");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //2. Colocando la imagen de fondo
    auto spriteFondo = Sprite::create("Images/background.jpg");
    spriteFondo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(spriteFondo, 0); //Añadir la imagen a la pantalla

    /////////////////////////////
    // creating a Menu 
    auto menuItem1 = MenuItemFont::create("MAPA", CC_CALLBACK_1(MainMenu::mapaCloseCallback, this));
    menuItem1->setFontSizeObj(22);
    auto menuItem2 = MenuItemFont::create("PUNTUACION", CC_CALLBACK_1(MainMenu::puntuacionCloseCallback, this));
    menuItem2->setFontSizeObj(22);
    auto menuItem3 = MenuItemFont::create("SALIR", CC_CALLBACK_1(MainMenu::salirCloseCallback, this));
    menuItem3->setFontSizeObj(22);

    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menuItem2->setPosition(Vec2(origin.x + visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menuItem3->setPosition(Vec2(origin.x +visibleSize.width / 2, (visibleSize.height / 4) * 1));
    menuItem1->setColor(Color3B::ORANGE);

    /* repeat for as many menu items as needed */

    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("PRIMER JUEGO", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr) {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}

void MainMenu::puntuacionCloseCallback(Ref* sender) {
    log("Puntuacion");
}

void MainMenu::mapaCloseCallback(Ref* sender) {
    log("Mapa");
    //create scene
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::salirCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}