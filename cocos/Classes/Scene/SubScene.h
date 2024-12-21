#ifndef __SUB_SCENE_H__
#define __SUB_SCENE_H__

#include "cocos2d.h"
#include "Global/Global.h"


class SubScene : public cocos2d::Scene
{
public:

    static Scene* createScene() {};

    // ��ʼ������
    bool init() {
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


        // ����������¼�������
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(SubScene::changeScene, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

        // ����update����
        this->scheduleUpdate();

        /*
        //----------------------------------------------------
        // ���ܣ����ӱ���ͼ��
        // ˵�������ӱ���ͼ�㵽��ǰ��������ʼ������
        // ͼ�㣺Backpacklayer
        //----------------------------------------------------
        backpackLayer = BackpackLayer::create();
        if (backpackLayer) {
            this->addChild(backpackLayer, Backpacklayer);
            backpackLayer->setName("backpackLayer");
        }
        else
            CCLOG("Failed to load the backpack layer");

        CCLOG("BackpackLayer position: (%f, %f)", backpackLayer->getPositionX(), backpackLayer->getPositionY());
        CCLOG("BackpackLayer size: (%f, %f)", backpackLayer->getContentSize().width, backpackLayer->getContentSize().height);

       


        //----------------------------------------------------
        // ���ܣ������ƶ�����
        // ˵�����������ǣ�����λ�ڵ�ͼ����
        // ͼ�㣺Playerlayer
        //----------------------------------------------------
        auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
        if (sprite_move)
        {
            sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            this->addChild(sprite_move, Playerlayer);
            sprite_move->init_keyboardlistener();

            sprite_move->schedule([this, sprite_move](float dt) { // ���� `this` �� `sprite_move`
                sprite_move->update(dt);                         // ���������ƶ��߼�
                }, "update_key_person");

        }
        // ���㾭�����ź��ʵ�ʳߴ�
        Size originalSize = sprite_move->getContentSize();
        float scale = sprite_move->getScale();
        Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
        auto sprite_tool = moveable_sprite_key_tool::create("Tools.plist", TOOL_WIDTH, TOOL_HEIGHT);
        if (sprite_tool)
        {
            sprite_tool->setPosition(Vec2(visibleSize.width / 2 + origin.x + scaledSize.width / 2, visibleSize.height / 2 + origin.y));
            this->addChild(sprite_tool, 1);
            sprite_tool->init_keyboardlistener();
            sprite_tool->init_mouselistener();
            sprite_tool->schedule([sprite_tool](float dt) {
                sprite_tool->update(dt);
                }, "update_key_tool");
        }


        */




        return true;
    }

    // ����һ����ʼ����ͼ�ĺ���
    virtual void initTileMap() {}

    // ��дupdate������������չ��̬�߼�
    virtual void update(float delta) override{}

    // ������¼�����
    virtual void changeScene(cocos2d::Event* event){}

protected:
    // ��Ƭ��ͼ��ָ��
    cocos2d::TMXTiledMap* tileMap;

};

#endif // __SUB_SCENE_H__