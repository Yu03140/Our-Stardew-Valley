#include "ChristmasScene.h"



/*����������Ҫ���������л�����
 #include "ChristmasScene.h"

void checkDateAndSwitchScene()
{
    int month = getCurrentMonth(); // �Զ��庯������ȡ��ǰ�·�
    int day = getCurrentDay();     // �Զ��庯������ȡ��ǰ����

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


    //ע�⣡����������������ң�����������
    
    auto background = Sprite::create("stardew_christmas_home.png");
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(Vec2::ZERO);
    this->addChild(background, 0);

    // 1. ��ʼ����Ҿ���
    playerSprite = cocos2d::Sprite::create("npc3.png");
    // 2. �����Ҿ��鴴��ʧ�ܣ����� false
    if (!playerSprite) return false;

    // 3. ������Ҿ����λ��
    playerSprite->setPosition(cocos2d::Vec2(1020, 1020));//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // 4. ����Ҿ�����ӵ���ǰ������
    this->addChild(playerSprite);

    // 5. ��ʼ�� NPC ����

    //�����Ǳ������ж�����������������������������������������������������������������������������������������������

    /*if (npcType == "NPC1") {
        npc1Position = cocos2d::Vec2(x * layer->getTileWidth(), y * layer->getTileHeight());
        CCLOG("NPC1 Position: (%f, %f)", npc1Position.x, npc1Position.y);
    }
    else if (npcType == "NPC2") {
        npc2Position = cocos2d::Vec2(x * layer->getTileWidth(), y * layer->getTileHeight());
        CCLOG("NPC2 Position: (%f, %f)", npc2Position.x, npc2Position.y);
    }*/


    //�����޸�һ�����õ�λ��


    npc3 = NPC::create(cocos2d::Vec2(1000, 1000), "May", 80, {
    "Merry Christmas! Enjoy the holiday season!",
        });
    // 6. �� NPC ������ӵ���ǰ������
    this->addChild(npc3);






    // 7. ���ö�ʱ���º���
    this->schedule([this](float deltaTime) {
        // 8. ÿ֡���ø��º���
        this->update(deltaTime);
        }, "update_key");

    // 9. ��ʼ���ɹ������� true
    return true;
}


ChristmasScene* ChristmasScene::create() {
    // 1. ���� NPCScene ����
    ChristmasScene* scene = new ChristmasScene();

    // 2. ����ʼ���Ƿ�ɹ�
    if (scene && scene->init()) {
        // 3. �����ʼ���ɹ����Զ������ڴ�
        scene->autorelease();




        // 4. ���سɹ������� NPCScene ����
        return scene;
    }
    else {
        // 5. �����ʼ��ʧ�ܣ���ӡ��־��Ϣ
        CCLOG("fail!!!11111��");
        // 6. �ͷ��ѷ�����ڴ�
        delete scene;
        // 7. ���ؿ�ָ���ʾʧ��
        return nullptr;
    }
}


void ChristmasScene::update(float delta) {
    // ��������NPC�Ľ���
    checkNPCInteraction();

    // ��������NPC�ľ��룬�����°�ť����ʾ״̬
    if (playerSprite->getPosition().distance(npc3->getPosition()) < 50) {
        npc3->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc3->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }

    
}


void ChristmasScene::checkNPCInteraction() {
    // �����Һ�NPC֮��ľ����Ƿ�С��100��λ��
    // 100�Ǵ��������ķ�Χ��ֵ���������NPC�ľ���С��100ʱ�����п�����NPC������
    if (playerSprite->getPosition().distance(npc3->getPosition()) < 50) {

        // ���NPC��ǰ��������״̬����NPCû����������ҶԻ���������ʾ������ʾ��
        if (!npc3->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }

    }
}
