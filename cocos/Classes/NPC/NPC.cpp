#include "NPC.h"


NPC::NPC()
    : npcSprite(nullptr), npcName("Unnamed"), affection(0), currentChatIndex(0), isChatting(false) {}

NPC::~NPC() {}

bool NPC::init(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    // 1. ����NPC����
    npcSprite = cocos2d::Sprite::create("Bouncer.png"); // ����һ�����飬����������ΪNPC��ͼ��ʹ��"Bouncer.png"ͼƬ
    if (!npcSprite) return false;  // ���ͼƬû�м��سɹ�������false����ʾ��ʼ��ʧ��

    // 2. ����NPC��λ��
    this->setPosition(position);  // ���õ�ǰNPC�����λ�ã�λ��ͨ����������
    this->addChild(npcSprite);  // �������ľ�����ӵ���ǰNPC�ڵ��У���ʾNPC����ʾ�ڸ�λ��

    // 3. ��ʼ��NPC����
    npcName = name;  // �������name������ֵ��NPC������
    this->affection = affection;  // ����NPC����ҵĺøж�
    chatMessages = chatTexts;  // �洢NPC�������ı�
    currentChatIndex = 0;  // ���õ�ǰ�����ı�����������ʼֵΪ0����ʾ��һ���ı�
    currentChatLabel = nullptr;  // ��ʼ��Ϊnullptr����ʾû�е�ǰ��ʾ�������ǩ

    // 4. �������찴ť
    chatButton = cocos2d::MenuItemLabel::create(
        cocos2d::Label::createWithSystemFont("Chat", "Arial", 24),  // ����һ����ʾ"Chat"���ֵı�ǩ������ΪArial����СΪ24
        CC_CALLBACK_0(NPC::interact, this)  // ���ð�ť���ʱ�Ļص���������������NPC�����interact����
    );
    chatButton->setScale(0.5); // �Ŵ��ı�

    // 5. �����˵���������찴ť
    auto menu = cocos2d::Menu::create(chatButton, nullptr);  // ����һ���˵����˵���ֻ����һ����ť
    menu->setPosition(cocos2d::Vec2(0, -50));  // ���ò˵���λ�ã�����ť������NPC���·�300����λ�ĵط�

    this->addChild(menu, 16);
    //this->addChild(menu);  // ���˵���ӵ�NPC�ڵ��У�������ť������ʾ����

    // 6. �������찴ť
    chatButton->setVisible(false);  // Ĭ������²���ʾ��ť


    return true;  // ����true����ʾ��ʼ���ɹ�
}




NPC* NPC::create(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    // 1. ���� NPC ����
    NPC* npc = new NPC();  // ��̬����һ���µ� NPC ����

    // 2. ��ʼ�� NPC ����
    if (npc && npc->init(position, name, affection, chatTexts)) {
        // ��� NPC ���󴴽��ɹ��ҳ�ʼ���ɹ�
        npc->autorelease();  // �Զ������ڴ棬ʹ�� cocos2d::Node ���ڴ�������
        return npc;  // ���سɹ������� NPC ����
    }
    else {
        // ����������ʼ��ʧ�ܣ�ɾ�����󲢷��ؿ�ָ��
        delete npc;  // �ֶ�ɾ�����󣬷�ֹ�ڴ�й©
        return nullptr;  // ���ؿ�ָ�룬��ʾ����ʧ��
    }
}


void NPC::startChat() {
    if (currentChatIndex < chatMessages.size()) {
        // ���֮ǰ�жԻ����Ƴ���
        if (currentChatLabel) {
            currentChatLabel->removeFromParent();  // �Ӹ��ڵ����Ƴ���ǰ�ı�ǩ
        }

        // �����ǰ��������
        cocos2d::log("NPC [%s]: %s", npcName.c_str(), chatMessages[currentChatIndex].c_str());

        // �����µ������ǩ����ʾ
        currentChatLabel = cocos2d::Label::createWithTTF(chatMessages[currentChatIndex], "fonts/arial.ttf", 24);
        //currentChatLabel->setVisible(true);
        currentChatLabel->setPosition(getPosition() + cocos2d::Vec2(0, 100));  // ��ʾ��NPC�Ϸ�
        currentChatLabel->setScale(2); // �Ŵ����
        currentChatLabel->setTextColor(cocos2d::Color4B::BLACK);
        this->getParent()->addChild(currentChatLabel);  // ���µı�ǩ��ӵ����ڵ�

        // ������������
        currentChatIndex++;
        currentChatLabel->setVisible(true);
    }
    else {
        // ���û�и���Ի��������Ի�
        cocos2d::log("End of conversation with NPC [%s].", npcName.c_str());
        currentChatIndex = 0;
        currentChatLabel->setVisible(false);//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        isChatting = false;  // ��������

        // �������찴ť����ð�ť
        //chatButton->setVisible(false);  // �������찴ť
        // ���߽��ð�ť
        // chatButton->setEnabled(false);  
    }
}




void NPC::interact() {
    // �����־�鿴�Ƿ���뵽����
    cocos2d::log("NPC [%s] clicked, isChatting: %d", npcName.c_str(), isChatting);

    if (isChatting) {
        // ���NPC�������죬����startChat()�����Ի�
        //currentChatLabel->setVisible(true);
        startChat();
    }
    else {
        // ���NPCû�п�ʼ���죬����Ϊ��������
        isChatting = true;
        //currentChatLabel->setVisible(true);
        startChat();  // ��ʼ�Ի�
    }
}

void NPC::showChatButton(bool show) {
    if (chatButton) {
        chatButton->setVisible(show);  // ���ݲ������ư�ť�Ƿ�ɼ�
    }
}