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
    static RecipeLayer* create();
    virtual bool init();
    void closeRecipe();                                                 // �ر�ʳ�ײ�Ļص����� 
    void canCookFood(const std::string& foodName);                      // �ж��Ƿ��������ĳ��ʳ��
    void createFoodSprites();                                           // ����ʳ�ﾫ�鲢����������ʾ 
    void onFoodSpriteClicked(cocos2d::Ref* sender);                     // ���ʳ�ﾫ��Ļص����� 
    void createCloseButton();                                           // ����XforTaskBar��ť
    void updateIngredientLabel(const std::string& foodName);            // ����ʳ���ԭ������ʾ

private:
    cocos2d::Sprite* board;                                             // ��ͼ
    cocos2d::Label* ingredientLabel;                                    // ԭ������ʾ��ǩ
    cocos2d::MenuItemImage* closeBtn;                                   // �رհ�ť
    std::map<std::string, std::vector<std::string>> foodRecipes;        // ʳ����ԭ���ϵ�ӳ��
    std::string currentFood;                                            // ��ǰѡ�е�ʳ������
};

#endif // __RECIPE_LAYER_H__
