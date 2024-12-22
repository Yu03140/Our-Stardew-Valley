#ifndef BACKPACK_LAYER_H
#define BACKPACK_LAYER_H

#include "cocos2d.h"

struct ItemSlot {
    std::string name;                                                                    // ��Ʒ����
    int quantity;                                                                        // ��Ʒ����
    cocos2d::Sprite* sprite;                                                             // ��ʾ��Ʒ�ľ���
};

class BackpackLayer : public cocos2d::Layer {
public:

    BackpackLayer();
    virtual ~BackpackLayer();
    static BackpackLayer* create();
    static BackpackLayer* getInstance();
    void BackpackLayer::destroyInstance();
    virtual bool init();
    void onMouseDown(cocos2d::Event* event);                                            // ������¼�������
    bool BackpackLayer::addItem(const std::string& itemName, const int num = 1);        // �����Ʒ
	bool BackpackLayer::removeItem(const std::string& itemName, const int num = 1);     // �Ƴ���Ʒ
    std::string getSelectedItem() const;                                                // �õ�ѡ�е���Ʒ
    cocos2d::TMXTiledMap* tilemap;                                                      // ��Ƭ��ͼ

private:

	static BackpackLayer* instance;                                                     // ����ģʽ
    float X0;
    float Y0;
    std::string selectedItem;
	void updateItemTexture(int slotIndex);     							                // ������Ʒ����
	void clearItemTexture(int slotIndex);	  							                // �����Ʒ����
    std::vector<ItemSlot> itemSlots;                                                    // ������������
};

#endif // BACKPACK_LAYER_H
