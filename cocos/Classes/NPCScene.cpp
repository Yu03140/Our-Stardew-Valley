#include "NPCScene.h"


NPCScene::NPCScene() : playerSprite(nullptr), npc(nullptr) {}

NPCScene::~NPCScene() {}


bool NPCScene::init() {




    //注意！！！！！这里是玩家！！！！！！


    // 1. 初始化玩家精灵
    playerSprite = cocos2d::Sprite::create("Fizz.png");
    // 2. 如果玩家精灵创建失败，返回 false
    if (!playerSprite) return false;

    // 3. 设置玩家精灵的位置
    playerSprite->setPosition(cocos2d::Vec2(1020, 1020));//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // 4. 将玩家精灵添加到当前场景中
    this->addChild(playerSprite);

    // 5. 初始化 NPC 对象
    npc = NPC::create(cocos2d::Vec2(1050, 1050), "John", 50, {
        "Hello, traveler!",
        "How can I help you today?",
        "I hope you're having a good day!"
        });
    // 6. 将 NPC 对象添加到当前场景中
    this->addChild(npc);

    // 7. 设置定时更新函数
    this->schedule([this](float deltaTime) {
        // 8. 每帧调用更新函数
        this->update(deltaTime);
        }, "update_key");

    // 9. 初始化成功，返回 true
    return true;
}


NPCScene* NPCScene::create() {
    // 1. 创建 NPCScene 对象
    NPCScene* scene = new NPCScene();

    // 2. 检查初始化是否成功
    if (scene && scene->init()) {
        // 3. 如果初始化成功，自动管理内存
        scene->autorelease();
        // 4. 返回成功创建的 NPCScene 对象
        return scene;
    }
    else {
        // 5. 如果初始化失败，打印日志信息
        CCLOG("fail!!!11111！");
        // 6. 释放已分配的内存
        delete scene;
        // 7. 返回空指针表示失败
        return nullptr;
    }
}


void NPCScene::update(float delta) {
    // 检查玩家与NPC的交互
    checkNPCInteraction();

    // 检查玩家与NPC的距离，并更新按钮的显示状态
    if (playerSprite->getPosition().distance(npc->getPosition()) < 50) {
        npc->showChatButton(true);  // 在范围内时显示按钮
    }
    else {
        npc->showChatButton(false);  // 不在范围内时隐藏按钮
    }
}


void NPCScene::checkNPCInteraction() {
    // 检查玩家和NPC之间的距离是否小于100单位。
    // 100是触发交互的范围阈值，即玩家与NPC的距离小于100时，才有可能与NPC互动。
    if (playerSprite->getPosition().distance(npc->getPosition()) < 100) {

        // 如果NPC当前不在聊天状态（即NPC没有正在与玩家对话），则显示互动提示。
        if (!npc->isChattingStatus()) {
            // 输出日志，提示玩家按下“Chat”键与NPC互动。
            CCLOG("Press 'Chat' to interact with NPC.");
        }
    }
}
