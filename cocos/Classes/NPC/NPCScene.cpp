#include "NPCScene.h"


NPCScene::NPCScene() : playerSprite(nullptr), npc1(nullptr), npc2(nullptr) {}

NPCScene::~NPCScene() {}


bool NPCScene::init() {

    //TimeSystem::getInstance();


    //ע�⣡����������������ң�����������


    // 1. ��ʼ����Ҿ���
    playerSprite = cocos2d::Sprite::create("Fizz.png");
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
    npc1 = NPC::create(cocos2d::Vec2(1050, 1050), "John", 50, {
        "1 Hello, traveler!",
        "1 How can I help you today?",
        "1 I hope you're having a good day!",
        "1 friend~"
    });
    // 6. �� NPC ������ӵ���ǰ������
    this->addChild(npc1);

    npc2 = NPC::create(cocos2d::Vec2(500, 500), "May", 80, {
    "2 Hello, traveler!",
    "2 How can I help you today?",
    "2 I hope you're having a good day!",
    "2 lovers~"
    });
    // 6. �� NPC ������ӵ���ǰ������
    this->addChild(npc2);






    // 7. ���ö�ʱ���º���
    this->schedule([this](float deltaTime) {
        // 8. ÿ֡���ø��º���
        this->update(deltaTime);
        }, "update_key");

    // 9. ��ʼ���ɹ������� true
    return true;
}


NPCScene* NPCScene::create() {
    // 1. ���� NPCScene ����
    NPCScene* scene = new NPCScene();

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


void NPCScene::update(float delta) {
    // ��������NPC�Ľ���
    checkNPCInteraction();

    // ��������NPC�ľ��룬�����°�ť����ʾ״̬
    if (playerSprite->getPosition().distance(npc1->getPosition()) < 50) {
        npc1->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc1->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }
    if (playerSprite->getPosition().distance(npc2->getPosition()) < 50) {
        npc2->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc2->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }
}


void NPCScene::checkNPCInteraction() {
    // �����Һ�NPC֮��ľ����Ƿ�С��100��λ��
    // 100�Ǵ��������ķ�Χ��ֵ���������NPC�ľ���С��100ʱ�����п�����NPC������
    if (playerSprite->getPosition().distance(npc1->getPosition()) < 50) {

        // ���NPC��ǰ��������״̬����NPCû����������ҶԻ���������ʾ������ʾ��
        if (!npc1->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }
        if (!npc2->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }
    }
}
