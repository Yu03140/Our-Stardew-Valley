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

    // 创建食谱层
    static RecipeLayer* create();

    // 初始化层
    virtual bool init();

    // 关闭食谱层的回调函数
    void closeRecipe();

    // 判断是否可以制作某个食物
    void canCookFood(const std::string& foodName);

    // 创建食物精灵并设置悬浮提示
    void createFoodSprites();

    // 点击食物精灵的回调函数
    void onFoodSpriteClicked(cocos2d::Ref* sender);

    // 创建XforTaskBar按钮
    void createCloseButton();

    // 更新食物的原材料提示
    void updateIngredientLabel(const std::string& foodName);

private:
    cocos2d::Sprite* board;          // 底图
    cocos2d::Label* ingredientLabel; // 原材料提示标签
    cocos2d::MenuItemImage* closeBtn; // 关闭按钮

    // 食物与原材料的映射
    std::map<std::string, std::vector<std::string>> foodRecipes;

    // 当前选中的食物名称
    std::string currentFood;
};

#endif // __RECIPE_LAYER_H__
