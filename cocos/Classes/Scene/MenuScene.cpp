/****************************************************************************
 * ���ܽ���:
 * ����һ���򵥵� Cocos2d-x ��Ϸ������չʾ�����ʹ�þ��顢�˵�������¼��������������档
 * ��Ҫ���ܰ�����
 * - ��ʾһ������ͼƬ�ͱ���ͼƬ
 * - ����һ����ť�������������ͣ״̬���İ�ť��ͼƬ�ʹ�С
 * - �����ťʱ�л�����һ������
 * - �ṩ�رհ�ť�˳�����
 ****************************************************************************/

#include "MenuScene.h"
#include "FarmGround.h"

USING_NS_CC;

// ����˵���ʱ�Ļص�����
void MenuScene::onMenuItemClicked(Ref* sender) {
    // �л��� FarmScene ����
    Director::getInstance()->replaceScene(FarmScene::createScene());
}

// ��������
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// ��������ļ�ʱ�Ĵ�����Ϣ
static void problemLoading(const char* filename)
{
    printf("���ش���: %s\n", filename);
    printf("������ı��뷽ʽ��������Ҫ���ļ���ǰ���� 'Resources/' ·��\n");
}

// �ڳ�ʼ��ʱ����ʵ����
bool MenuScene::init()
{
    //////////////////////////////
    // 1. ���ø���ĳ�ʼ������
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ��Ļ��������Ĵ�С��ԭ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. ���һ���˵��������˳�����
    // ����Ը�����Ҫ�޸ĸò��֡�

    // ����һ�����رա���ť�����˳�����
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' �� 'CloseSelected.png' �ļ�");
    }
    else
    {
        // ���á��رա���ť��λ��
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // ��ӱ���ͼƬ
    auto background = Sprite::create("homepage.jpg");
    if (!background) {
        CCLOG("���ر���ͼƬʧ��.");
        return false;
    }
    // ���ñ���λ��Ϊ��Ļ����
    background->setPosition(origin + visibleSize / 2);
    // ��ѡ��������Ļ��С
    background->setContentSize(visibleSize);
    // ��ӵ����������� z-order Ϊ -1��ʹ��λ����ײ�
    this->addChild(background, -1);

    // ����ԭʼͼƬ����
    auto texture = Director::getInstance()->getTextureCache()->addImage("menu.png");
    if (!texture) {
        CCLOG("���ز˵�ͼƬʧ��.");
        return false;
    }

    // ��ȡ menu.png ���ϲ�����Ϊ����
    Rect titleRect(0, 0,
        texture->getContentSize().width,  // �����������
        texture->getContentSize().height / 4 + 50); // �߶�������߶ȵ�һ����
    auto title_sprite = Sprite::createWithTexture(texture, titleRect);  // �����ü���ľ���
    if (!title_sprite) {
        CCLOG("�������⾫��ʧ��.");
        return false;
    }
    title_sprite->setScale(1.5f); // �Ŵ���⾫�� 1.5 ��
    title_sprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4)); // ���ñ���λ�ã���Ļ�����м䣩
    this->addChild(title_sprite, 0); // z-order Ϊ 0��ȷ�������ڱ����Ϸ�

    // ����һ���˵��ť
    auto menuItem1 = MenuItemImage::create("load1.png", "load2.png"); // ������ť��ָ����ͨ״̬��ѡ��״̬��ͼƬ
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
            menuItem1->setNormalImage(Sprite::create("load2.png")); // �л��� load2.png
        }
        else {
            // ����뿪��ť���ָ�ԭ��С
            menuItem1->setScale(1.0f);  // �ָ�ԭʼ��С
            menuItem1->setNormalImage(Sprite::create("load1.png")); // �ָ�Ϊ load1.png
        }
        };

    // ����¼�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ��������ťʱ�л������Ļص�����
    auto onButtonClicked = [](Ref* sender) {
        // �����ť���л��� FarmScene ����
        Director::getInstance()->replaceScene(FarmScene::createScene());
        };

    // ���ð�ť�ĵ���ص�����
    menuItem1->setCallback(onButtonClicked);

    // �����˵�����ӵ�������
    Menu* menu = Menu::create(menuItem1, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);


}

// �رհ�ť�Ļص�����
void MenuScene::menuCloseCallback(Ref* pSender)
{
    // �ر� Cocos2d-x ��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();

    /*������� iOS ƽ̨����ϣ������ԭ�� iOS ���棬����ֱ�ӵ��� Director::getInstance()->end()��
    * ��Ҫ����һ���Զ����¼���������������
    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}
