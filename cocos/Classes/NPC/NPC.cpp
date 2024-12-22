#include "NPC.h"


NPC::NPC()
    : npcSprite(nullptr), npcName("Unnamed"), affection(0), currentChatIndex(0), isChatting(false) {}

NPC::~NPC() {}

bool NPC::init(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    // ����NPC����
    npcSprite = cocos2d::Sprite::create("Bouncer.png"); 
    if (!npcSprite) return false;  
    this->setPosition(position); 
    this->addChild(npcSprite); 

    // ��ʼ��NPC����
    npcName = name;  
    this->affection = affection;  
    chatMessages = chatTexts; 
    currentChatIndex = 0; 
    currentChatLabel = nullptr;  

    // �������찴ť
    chatButton = cocos2d::MenuItemLabel::create(
        cocos2d::Label::createWithSystemFont("Chat", "Arial", 24),  
        CC_CALLBACK_0(NPC::interact, this)  
    );
    chatButton->setScale(0.5); // �Ŵ��ı�

    // �����˵���������찴ť
    auto menu = cocos2d::Menu::create(chatButton, nullptr); 
    menu->setPosition(cocos2d::Vec2(0, -50));  

    this->addChild(menu, 16);
    //this->addChild(menu);  

    // �������찴ť
    chatButton->setVisible(false);

    return true; 
}




NPC* NPC::create(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    //  ���� NPC ����
    NPC* npc = new NPC();  

    // ��ʼ�� NPC ����
    if (npc && npc->init(position, name, affection, chatTexts)) {
        npc->autorelease();  
        return npc;  
    }
    else {
        delete npc;  
        return nullptr;  
    }
}


void NPC::startChat() {
    if (currentChatIndex < chatMessages.size()) {
        if (currentChatLabel) {
            currentChatLabel->removeFromParent(); 
        }

        // �����ǰ��������
        cocos2d::log("NPC [%s]: %s", npcName.c_str(), chatMessages[currentChatIndex].c_str());

        // �����µ������ǩ����ʾ
        currentChatLabel = cocos2d::Label::createWithTTF(chatMessages[currentChatIndex], "fonts/arial.ttf", 24);
        currentChatLabel->setPosition(getPosition() + cocos2d::Vec2(0, 100)); 
        currentChatLabel->setScale(2); 
        currentChatLabel->setTextColor(cocos2d::Color4B::BLACK);
        this->getParent()->addChild(currentChatLabel);  

        // ������������
        currentChatIndex++;
        currentChatLabel->setVisible(true);
    }
    else {
        // ���û�и���Ի��������Ի�
        cocos2d::log("End of conversation with NPC [%s].", npcName.c_str());
        currentChatIndex = 0;
        currentChatLabel->setVisible(false);
        isChatting = false;  // ��������

    }
}


void NPC::interact() {
    // �����־�鿴�Ƿ���뵽����
    cocos2d::log("NPC [%s] clicked, isChatting: %d", npcName.c_str(), isChatting);

    if (isChatting) {
        startChat();
    }
    else {
        isChatting = true;
        startChat();  // ��ʼ�Ի�
    }
}

void NPC::showChatButton(bool show) {
    if (chatButton) {
        chatButton->setVisible(show);  // ���ݲ������ư�ť�Ƿ�ɼ�
    }
}