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

    //ÿ10s����TODAY
    this->schedule([](float dt) {
        TODAY++;CCLOG("TODAY: %d", TODAY);
        }, 10.0f, "global_variable_increment");


   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();

   //����

    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist","Jas_Winter");
    if (sprite_move)
    {
        // ���ó�ʼλ��
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // ��������ӵ�������
        this->addChild(sprite_move,1);
    
        // ��ʼ�����̼�����
        sprite_move->init_keyboardlistener();
    
        // ��ʱ���� update ���¾����λ��
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key_person");
    }
   
    // ��ȡ�����ԭʼ�ߴ�
    Size originalSize = sprite_move->getContentSize();
    // ��ȡ��������ű���
    float scale = sprite_move->getScale();
    // ���㾭�����ź��ʵ�ʳߴ�
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
   
    //auto sprite_move_tool = moveable_sprite_key_tool::create("Tools.plist",1,1);
    //if (sprite_move_tool)
    //{
    //    // ���ó�ʼλ��
    //    sprite_move_tool->setPosition(Vec2(visibleSize.width / 2 + origin.x + scaledSize.width/2, visibleSize.height / 2 + origin.y));
    //    // ��������ӵ�������
    //    this->addChild(sprite_move_tool, 2);
    //
    //    // ��ʼ�����̼�����
    //    sprite_move_tool->init_keyboardlistener();
    //
    //    // ��ʼ����������
    //    sprite_move_tool->init_mouselistener();
    //
    //    // ��ʱ���� update ���¾����λ��
    //    sprite_move_tool->schedule([sprite_move_tool](float dt) {
    //        sprite_move_tool->update(dt);
    //        }, "update_key_tool");
    //}
   
    auto crop = crop::create("crop.plist", scaledSize.width, scaledSize.height);
    if (crop)
    {
        // ���ó�ʼλ��
        crop->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 4 + origin.y));
        // ��������ӵ�������
        this->addChild(crop, 4);

        // ��ʼ�����̼�����
        crop->init_mouselistener();

        // ��ʱ���� update ���¾����λ��
        crop->schedule([crop](float dt) {
            crop->update(dt);
            }, "update_crop");
    }

   //// ���� hover_button ʵ��
   //auto button = hover_button::create("Tools.plist", "Pick1-left");
   //if (button)
   //{
   //    // ���ð�ť��λ��
   //    button->setPosition(Vec2(300, 200));  // ������� (300, 200) λ��
   //    // ����ť��ӵ���ǰ��
   //    this->addChild(button);
   //    // ��ʼ����������
   //    button->init_mouselistener();
   //}
   //
   //auto button1 = hover_button::create("Tools.plist", "Axe1-left");
   //if (button1)
   //{
   //    // ���ð�ť��λ��
   //    button1->setPosition(Vec2(300, 300));  // ������� (300, 200) λ��
   //    // ����ť��ӵ���ǰ��
   //    this->addChild(button1);
   //    // ��ʼ����������
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
