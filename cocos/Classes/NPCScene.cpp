#include "NPCScene.h"


NPCScene::NPCScene() : playerSprite(nullptr), npc(nullptr) {}

NPCScene::~NPCScene() {}


bool NPCScene::init() {




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
    npc = NPC::create(cocos2d::Vec2(1050, 1050), "John", 50, {
        "Hello, traveler!",
        "How can I help you today?",
        "I hope you're having a good day!"
        });
    // 6. �� NPC ������ӵ���ǰ������
    this->addChild(npc);

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
    if (playerSprite->getPosition().distance(npc->getPosition()) < 50) {
        npc->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }
}


void NPCScene::checkNPCInteraction() {
    // �����Һ�NPC֮��ľ����Ƿ�С��100��λ��
    // 100�Ǵ��������ķ�Χ��ֵ���������NPC�ľ���С��100ʱ�����п�����NPC������
    if (playerSprite->getPosition().distance(npc->getPosition()) < 100) {

        // ���NPC��ǰ��������״̬����NPCû����������ҶԻ���������ʾ������ʾ��
        if (!npc->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }
    }
}
