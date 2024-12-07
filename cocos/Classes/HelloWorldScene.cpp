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
#include "FarmGround.h"


USING_NS_CC;

void HelloWorld::onMenuItemClicked(Ref* sender) {
    // �л��� MenuScene
    Director::getInstance()->replaceScene(FarmScene::createScene());
}


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
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

// ��ӱ���ͼƬ
    auto background = Sprite::create("homepage.jpg");
    if (!background) {
        CCLOG("Failed to load background image.");
        return false;
    }
    background->setPosition(origin + visibleSize / 2);  // ������ͼƬ����Ϊ��Ļ����
    background->setContentSize(visibleSize);           // ��ѡ��������Ļ��С
    this->addChild(background, -1);                    // ��ӵ����������� z-order Ϊ -1 ʹ��λ����ײ�


    // ����ԭʼͼƬ����
    auto texture = Director::getInstance()->getTextureCache()->addImage("menu.png");
    if (!texture) {
        CCLOG("Failed to load menu image.");
        return false;
    }

    //��ȡmenu���ϲ��֣�������
    Rect titleRect(0, 0,
        texture->getContentSize().width,  // �����������
        texture->getContentSize().height / 4 + 50); // �߶�������߶ȵ�һ��
    auto title_sprite = Sprite::createWithTexture(texture, titleRect);  // �����ü���ľ���
    if (!title_sprite) {
        CCLOG("Failed to create title_sprite.");
        return false;
    }
    title_sprite->setScale(1.5f); // ������Ŵ� 1.5 ��
    title_sprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));// ���òü���ľ���λ�ã���Ļ�����м䣩
    this->addChild(title_sprite, 0); // z-order Ϊ 0��ȷ���ڱ����Ϸ�




    auto menuItem1 = MenuItemImage::create("load1.png", "load2.png"); // ������ť��ָ������״̬��ѡ��״̬��ͼƬ
    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    // ��������¼�������
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event) {
        // ��ȡ���λ��
        Vec2 mousePos = Director::getInstance()->convertToGL(static_cast<EventMouse*>(event)->getLocationInView());

        // �ж�����Ƿ���ͣ�ڰ�ť��
        Rect menuItemRect = menuItem1->getBoundingBox();
        if (menuItemRect.containsPoint(mousePos)) {
            // �����ͣ�ڰ�ť�ϣ��Ŵ�ť���л��� load2.png
            menuItem1->setScale(1.2f);  // �Ŵ�ť
            menuItem1->setNormalImage(Sprite::create("load2.png")); // �޸���ͨ״̬Ϊ load2.png
        }
        else {
            // ����뿪��ť���ָ�����״̬
            menuItem1->setScale(1.0f);  // �ָ�ԭʼ��С
            menuItem1->setNormalImage(Sprite::create("load1.png")); // �ָ���ͨ״̬Ϊ load1.png
        }
        };

    // ��Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // ��������ťʱ�л������Ļص�����
    auto onButtonClicked = [](Ref* sender) {
        // �л�����һ������
        Director::getInstance()->replaceScene(FarmScene::createScene());  // �滻Ϊ��һ������������ʹ�� MenuScene ��Ϊ���ӣ�
        };

    // ���ð�ť�ĵ���ص�����
    menuItem1->setCallback(onButtonClicked);
    // �����˵�����ӵ�������
    Menu* menu = Menu::create(menuItem1, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
