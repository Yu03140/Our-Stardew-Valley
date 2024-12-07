#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include <vector>

class BackpackManager {
public:
    // ��ȡ�����������ĵ���
    static BackpackManager* getInstance();

    // �����Ʒ������
    void addItem(const std::string& itemName, const std::string& itemImage);

    // ��ȡ�����е���Ʒ�б�
    const std::vector<std::pair<std::string, std::string>>& getItems() const;

    // ��ձ���
    void clear();

private:
    BackpackManager();
    ~BackpackManager();

    // ���汳����Ʒ���б�
    std::vector<std::pair<std::string, std::string>> items;
};

#endif // __BACKPACK_MANAGER_H__
