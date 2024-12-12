
#include "HelloWorldScene.h"
#include "FarmGround.h"


USING_NS_CC;

// �л��� MenuScene
void HelloWorld::onMenuItemClicked(Ref* sender) {
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
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

// ��ӱ���ͼƬ
    auto background = Sprite::create("homepage.jpg");
    if (!background) {
        CCLOG("Failed to load background image.");
        return false;
    }
    background->setPosition(origin + visibleSize / 2);  // ������ͼƬ����Ϊ��Ļ����
    background->setContentSize(visibleSize);           // ��ѡ��������Ļ��С
    this->addChild(background, -1);                    // ��ӵ����������� z-order Ϊ -1 ʹ��λ����ײ�


    auto title_sprite = Sprite::create("menu.png");
    title_sprite->setScale(1.5f); // ������Ŵ� 1.5 ��
    title_sprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));// ����λ�ã���Ļ�����м䣩
    this->addChild(title_sprite, 0); // z-order Ϊ 0��ȷ���ڱ����Ϸ�


    auto menuItem1 = MenuItemImage::create("load1.png", "load2.png"); // ������ť��ָ������״̬��ѡ��״̬��ͼƬ
    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    // ��������¼�������
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event) {
        // ��ȡ���λ��
        Vec2 mousePos = Director::getInstance()->convertToGL(static_cast<EventMouse*>(event)->getLocationInView());

        // ת�����λ�õ� menuItem1 ���ڵ�ľֲ�����
        Vec2 localMousePos = menuItem1->getParent()->convertToNodeSpace(mousePos);

        // ��ȡ menuItem1 �ı߽��
        Rect menuItemRect = menuItem1->getBoundingBox();

        // �ж�����Ƿ���ͣ�ڰ�ť��
        if (menuItemRect.containsPoint(localMousePos)) {
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
        Director::getInstance()->replaceScene(FarmScene::createScene());  // �滻Ϊ��һ������
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
