#ifndef __SUB_SCENE_H__
#define __SUB_SCENE_H__

#include "cocos2d.h"
#include "Global/Global.h"
#include"Moveable/moveable_sprite_key.h"

class SubScene : public cocos2d::Scene
{
public:

    static Scene* createScene() {};

    // ��ʼ������
    virtual bool init() {
        // ���ø����ʼ������
        if (!Scene::init())
        {
            return false;
        }
        // ��ʼ����Ƭ��ͼ
        initTileMap();

        // ���ص�ͼ�������м�
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        if (tileMap) {
            tileMap->setAnchorPoint(Vec2(0.5, 0.5));
            float Map_posX = visibleSize.width / 2;
            float Map_posY = visibleSize.height / 2;
            tileMap->setPosition(Vec2(Map_posX, Map_posY));
            this->addChild(tileMap, 0);
            tileMap->setScale(MapSize);
        }
        else {
            CCLOG("Failed to load the tile map");
        }


        // ���������¼�������
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(SubScene::changeScene, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

        // ����update����
        this->scheduleUpdate();

        //----------------------------------------------------
        // ���ܣ�����ƶ�����
        // ˵����������ǣ�����λ�ڵ�ͼ����
        // ͼ�㣺Playerlayer
        //----------------------------------------------------
        auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
        if (sprite_move)
        {
            sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            this->addChild(sprite_move, Playerlayer);
            sprite_move->init_keyboardlistener();

        }
        main_char = sprite_move;
        this->schedule([this](float dt) {
            if (main_char)
            {
                main_char->update(dt); // ���������ƶ��߼�
            }
            }, "update_key_person");

        // ���㾭�����ź��ʵ�ʳߴ�
        Size originalSize = sprite_move->getContentSize();
        float scale = sprite_move->getScale();
        Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
        auto sprite_tool = moveable_sprite_key_tool::create("Tools.plist");
        if (sprite_tool)
        {
            sprite_tool->setPosition(Vec2(visibleSize.width / 2 + origin.x + scaledSize.width / 2, visibleSize.height / 2 + origin.y));
            this->addChild(sprite_tool, Playerlayer);
            sprite_tool->init_keyboardlistener();
            sprite_tool->init_mouselistener();
        }
        main_tool = sprite_tool;
        this->schedule([this](float dt) {
            if (main_tool)
            {
                main_tool->update(dt); // ������Ʒ�ƶ��߼�
            }
            }, "update_key_tool");

        return true;
    }

    // ���һ����ʼ����ͼ�ĺ���
    virtual void initTileMap() {}

    // ��дupdate������������չ��̬�߼�
    virtual void update(float delta) override {}

    // ������¼�����
    virtual void changeScene(cocos2d::Event* event) {}

    void onEnter() {
        Scene::onEnter();

        //----------------------------------------------------
        // ���ܣ���ӱ���ͼ��
        // ˵������ӱ���ͼ�㵽��ǰ��������ʼ������
        // ͼ�㣺Backpacklayer
        //----------------------------------------------------
        auto backpacklayer = BackpackLayer::getInstance();
        if (!backpacklayer->getParent()) {
            this->addChild(backpacklayer, Backpacklayer);
            backpacklayer->setPosition(Vec2(0, 0));
            backpacklayer->setName("backpacklayer");
            CCLOG("Success to load the backpack layer");
        }
        else
            CCLOG("Failed to load the backpack layer");

        // �ڳ�������ʱ��Ӽ��̼�����
        main_char->init_keyboardlistener();
        this->schedule([this](float dt) {
            if (main_char)
            {
                main_char->update(dt); // ���������ƶ��߼�
            }
            }, "update_key_person");

        // �ڳ�������ʱ������ͼ��̼�����
        main_tool->init_keyboardlistener();
        main_tool->init_mouselistener();
        this->schedule([this](float dt) {
            if (main_tool)
            {
                main_tool->update(dt); // ������Ʒ�ƶ��߼�
            }
            }, "update_key_tool");
    }

    void onExit() {
        Scene::onExit();  // ���û���� onExit��ȷ�������Ļ����˳�����
        _eventDispatcher->removeEventListenersForTarget(main_char);
        if (backpackLayer) {
            CCLOG("!!Begin to remove");
            // �ӵ�ǰ�������Ƴ������㣬�������������ڴ�
            backpackLayer->removeFromParent();
            CCLOG("!!remove backpackLayer successfully!");
        }
    }

protected:
    // ��Ƭ��ͼ��ָ��
    cocos2d::TMXTiledMap* tileMap;
    moveable_sprite_key_walk* main_char;
    moveable_sprite_key_tool* main_tool;
};

#endif // __SUB_SCENE_H__