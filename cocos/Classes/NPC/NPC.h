#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"

class NPC : public cocos2d::Node {
public:
    NPC();
    ~NPC();

    // ��ʼ��NPC���������֡��øжȡ�λ�á��Ի�����
    bool init(const cocos2d::Vec2& position, const std::string& name, int affection,
        const std::vector<std::string>& chatTexts);

    // ����NPC����
    static NPC* create(const cocos2d::Vec2& position, const std::string& name, int affection,
        const std::vector<std::string>& chatTexts);

    // NPC�������ܣ���������
    void startChat();

    // ���������NPC�Ľ���
    void interact();

    // ����NPC������״̬
    bool isChattingStatus() const { return isChatting; }

    // ��ȡNPC������
    std::string getNPCName() const { return npcName; }

    // ��ȡNPC�ĺøж�
    int getAffection() const { return affection; }

    void showChatButton(bool show);



private:
    cocos2d::Sprite* npcSprite; // NPC����
    std::string npcName;        // NPC����
    int affection;              // NPC����ҵĺøж�
    cocos2d::MenuItemLabel* chatButton; // �����족��ť
    std::vector<std::string> chatMessages; // �����ı�
    size_t currentChatIndex;   // ��ǰ�����ı�����
    bool isChatting;           // �Ƿ���������
    cocos2d::Vec2 position;    // NPCλ��
    cocos2d::Label* currentChatLabel;  // ���ڴ洢��ǰ��ʾ�������ǩ

};

#endif // __NPC_H__
