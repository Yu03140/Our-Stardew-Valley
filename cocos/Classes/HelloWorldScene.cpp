/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "moveable_sprite_key.h"
#include "hover_button.h"
#include "FarmGround.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
   ///////////////////////////////
   //// 2. add a menu item with "X" image, which is clicked to quit the program
   ////    you may modify it.
   //
   //// add a "close" icon to exit the progress. it's an autorelease object
   //auto closeItem = MenuItemImage::create(
   //                                       "CloseNormal.png",
   //                                       "CloseSelected.png",
   //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
   //
   //if (closeItem == nullptr ||
   //    closeItem->getContentSize().width <= 0 ||
   //    closeItem->getContentSize().height <= 0)
   //{
   //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
   //}
   //else
   //{
   //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
   //    float y = origin.y + closeItem->getContentSize().height/2;
   //    closeItem->setPosition(Vec2(x,y));
   //}
   //
   //// create menu, it's an autorelease object
   //auto menu = Menu::create(closeItem, NULL);
   //menu->setPosition(Vec2::ZERO);
   //this->addChild(menu, 1);
   //
   ///////////////////////////////
   //// 3. add your codes below...
   //
   //// add a label shows "Hello World"
   //// create and initialize a label
   //
   //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
   //if (label == nullptr)
   //{
   //    problemLoading("'fonts/Marker Felt.ttf'");
   //}
   //else
   //{
   //    // position the label on the center of the screen
   //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
   //                            origin.y + visibleSize.height - label->getContentSize().height));
   //
   //    // add the label as a child to this layer
   //    this->addChild(label, 1);
   //}
   //
   //// add "HelloWorld" splash screen"
   //auto sprite = Sprite::create("HelloWorld.png");
   //if (sprite == nullptr)
   //{
   //    problemLoading("'HelloWorld.png'");
   //}
   //else
   //{
   //    // position the sprite on the center of the screen
   //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
   //
   //    // add the sprite as a child to this layer
   //    this->addChild(sprite, 0);
   //}
   //
   //测试

    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist","Jas_Winter");
    if (sprite_move)
    {
        // 设置初始位置
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // 将精灵添加到场景中
        this->addChild(sprite_move,1);
    
        // 初始化键盘监听器
        sprite_move->init_keyboardlistener();
    
        // 定时调用 update 更新精灵的位置
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key_person");
    }
   
    // 获取精灵的原始尺寸
    Size originalSize = sprite_move->getContentSize();
    // 获取精灵的缩放比例
    float scale = sprite_move->getScale();
    // 计算经过缩放后的实际尺寸
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
   
   // auto sprite_move_tool = moveable_sprite_key_tool::create("Tools.plist",1,1);
   // if (sprite_move_tool)
   // {
   //     // 设置初始位置
   //     sprite_move_tool->setPosition(Vec2(visibleSize.width / 2 + origin.x + scaledSize.width/2, visibleSize.height / 2 + origin.y));
   //     // 将精灵添加到场景中
   //     this->addChild(sprite_move_tool, 2);
   // 
   //     // 初始化键盘监听器
   //     sprite_move_tool->init_keyboardlistener();
   //     // 初始化鼠标监听器
   //     sprite_move_tool->init_mouselistener();
   //
   //     // 定时调用 update 更新精灵的位置
   //     sprite_move_tool->schedule([sprite_move_tool](float dt) {
   //         sprite_move_tool->update(dt);
   //         }, "update_key_tool");
   // }
   //
   //// 创建 hover_button 实例
   //auto button = hover_button::create("Tools.plist", "Pick1-left");
   //if (button)
   //{
   //    // 设置按钮的位置
   //    button->setPosition(Vec2(300, 200));  // 例如放在 (300, 200) 位置
   //    // 将按钮添加到当前层
   //    this->addChild(button);
   //    // 初始化鼠标监听器
   //    button->init_mouselistener();
   //}
   //
   //auto button1 = hover_button::create("Tools.plist", "Axe1-left");
   //if (button1)
   //{
   //    // 设置按钮的位置
   //    button1->setPosition(Vec2(300, 300));  // 例如放在 (300, 200) 位置
   //    // 将按钮添加到当前层
   //    this->addChild(button1);
   //    // 初始化鼠标监听器
   //    button1->init_mouselistener();
   //}


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
