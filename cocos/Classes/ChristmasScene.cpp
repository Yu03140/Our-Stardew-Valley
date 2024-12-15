#include "ChristmasScene.h"



/*主函数里需要用这个语句切换场景
 #include "ChristmasScene.h"

void checkDateAndSwitchScene()
{
    int month = getCurrentMonth(); // 自定义函数，获取当前月份
    int day = getCurrentDay();     // 自定义函数，获取当前日期

    if (month == 12 && day == 25)
    {
        auto christmasScene = ChristmasScene::createScene();
        Director::getInstance()->replaceScene(christmasScene);
    }
}

*/







#include "NPCScene.h"
#include "TimeSystem.h"

ChristmasScene::ChristmasScene() : playerSprite(nullptr), npc3(nullptr){}

ChristmasScene::~ChristmasScene() {}

void ChristmasScene::setupBackground()
{
;
}





bool ChristmasScene::init() {

    //TimeSystem::getInstance();


    //注意！！！！！这里是玩家！！！！！！
    
    auto background = Sprite::create("stardew_christmas_home.png");
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(Vec2::ZERO);
    this->addChild(background, 0);

    // 1. 初始化玩家精灵
    playerSprite = cocos2d::Sprite::create("npc3.png");
    // 2. 如果玩家精灵创建失败，返回 false
    if (!playerSprite) return false;

    // 3. 设置玩家精灵的位置
    playerSprite->setPosition(cocos2d::Vec2(1020, 1020));//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // 4. 将玩家精灵添加到当前场景中
    this->addChild(playerSprite);

    // 5. 初始化 NPC 对象

    //这里是遍历的判断条件！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！

    /*if (npcType == "NPC1") {
        npc1Position = cocos2d::Vec2(x * layer->getTileWidth(), y * layer->getTileHeight());
        CCLOG("NPC1 Position: (%f, %f)", npc1Position.x, npc1Position.y);
    }
    else if (npcType == "NPC2") {
        npc2Position = cocos2d::Vec2(x * layer->getTileWidth(), y * layer->getTileHeight());
        CCLOG("NPC2 Position: (%f, %f)", npc2Position.x, npc2Position.y);
    }*/


    //这里修改一下设置的位置


    npc3 = NPC::create(cocos2d::Vec2(1000, 1000), "May", 80, {
    "Merry Christmas! Enjoy the holiday season!",
        });
    // 6. 将 NPC 对象添加到当前场景中
    this->addChild(npc3);






    // 7. 设置定时更新函数
    this->schedule([this](float deltaTime) {
        // 8. 每帧调用更新函数
        this->update(deltaTime);
        }, "update_key");

    // 9. 初始化成功，返回 true
    return true;
}


ChristmasScene* ChristmasScene::create() {
    // 1. 创建 NPCScene 对象
    ChristmasScene* scene = new ChristmasScene();

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


void ChristmasScene::update(float delta) {
    // 检查玩家与NPC的交互
    checkNPCInteraction();

    // 检查玩家与NPC的距离，并更新按钮的显示状态
    if (playerSprite->getPosition().distance(npc3->getPosition()) < 50) {
        npc3->showChatButton(true);  // 在范围内时显示按钮
    }
    else {
        npc3->showChatButton(false);  // 不在范围内时隐藏按钮
    }

    
}


void ChristmasScene::checkNPCInteraction() {
    // 检查玩家和NPC之间的距离是否小于100单位。
    // 100是触发交互的范围阈值，即玩家与NPC的距离小于100时，才有可能与NPC互动。
    if (playerSprite->getPosition().distance(npc3->getPosition()) < 50) {

        // 如果NPC当前不在聊天状态（即NPC没有正在与玩家对话），则显示互动提示。
        if (!npc3->isChattingStatus()) {
            // 输出日志，提示玩家按下“Chat”键与NPC互动。
            CCLOG("Press 'Chat' to interact with NPC.");
        }

    }
}
