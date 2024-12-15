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

    // ��ӻ��Ƴ���Ʒ
    void addItem(const std::string& itemName);
    void removeItem(const std::string& itemName);

private:
    // ���º������Ʒ����
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // ������������
    std::vector<ItemSlot> itemSlots;

    // ��Ƭ��ͼ
    cocos2d::TMXTiledMap* tilemap;

    // ����ѡ�����Ʒ
    std::string selectedItemImage;
};

#endif // BACKPACK_LAYER_H
