#ifndef __RECIPE_LAYER_H__
#define __RECIPE_LAYER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"
#include "Global/Global.h"  

class RecipeLayer : public cocos2d::Layer
{
public:
    RecipeLayer();
    ~RecipeLayer();

    // ����ʳ�ײ�
    static RecipeLayer* create();

    // ��ʼ����
    virtual bool init();

    // �ر�ʳ�ײ�Ļص�����
    void closeRecipe();

    // �ж��Ƿ��������ĳ��ʳ��
    void canCookFood(const std::string& foodName);

    // ����ʳ�ﾫ�鲢����������ʾ
    void createFoodSprites();

    // ���ʳ�ﾫ��Ļص�����
    void onFoodSpriteClicked(cocos2d::Ref* sender);

    // ����XforTaskBar��ť
    void createCloseButton();

    // ����ʳ���ԭ������ʾ
    void updateIngredientLabel(const std::string& foodName);

private:
    cocos2d::Sprite* board;          // ��ͼ
    cocos2d::Label* ingredientLabel; // ԭ������ʾ��ǩ
    cocos2d::MenuItemImage* closeBtn; // �رհ�ť

    // ʳ����ԭ���ϵ�ӳ��
    std::map<std::string, std::vector<std::string>> foodRecipes;

    // ��ǰѡ�е�ʳ������
    std::string currentFood;
};

#endif // __RECIPE_LAYER_H__
