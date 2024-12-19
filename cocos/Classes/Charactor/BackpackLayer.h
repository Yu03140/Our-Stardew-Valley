#ifndef BACKPACK_LAYER_H
#define BACKPACK_LAYER_H

#include "cocos2d.h"

struct ItemSlot {
    std::string name;        // ��Ʒ����
    int quantity;            // ��Ʒ����
    cocos2d::Sprite* sprite; // ��ʾ��Ʒ�ľ���
};

class BackpackLayer : public cocos2d::Layer {
public:
    BackpackLayer();
    virtual ~BackpackLayer();

    static BackpackLayer* create();
    virtual bool init();

    // ������¼�������
    void onMouseDown(cocos2d::Event* event);

    // ��ӻ��Ƴ���Ʒ
    bool BackpackLayer::addItem(const std::string& itemName, const int num = 1);
    bool BackpackLayer::removeItem(const std::string& itemName, const int num = 1);


	// �õ�ѡ�е���Ʒ
    std::string getSelectedItem() const;

    // ��Ƭ��ͼ
    cocos2d::TMXTiledMap* tilemap;

private:

    float X0;
    float Y0;
    std::string selectedItem;
    // ���º������Ʒ����
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // ������������
    std::vector<ItemSlot> itemSlots;
};

#endif // BACKPACK_LAYER_H
