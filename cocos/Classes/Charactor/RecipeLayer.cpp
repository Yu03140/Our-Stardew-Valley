#include "RecipeLayer.h"

USING_NS_CC;

RecipeLayer::RecipeLayer()
    : board(nullptr), ingredientLabel(nullptr), closeBtn(nullptr)
{
}

RecipeLayer::~RecipeLayer()
{
}

RecipeLayer* RecipeLayer::create()
{
    RecipeLayer* ret = new RecipeLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool RecipeLayer::init()
{
    // ������ͼ
    board = Sprite::create("recipeboard.png");
    board->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(board);
    board->setScale(MapSize);

    // ����ʳ�ﾫ��
    createFoodSprites();

    // ����������ʾ��ǩ
    ingredientLabel = Label::createWithSystemFont("", "Arial", 24);
    ingredientLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height * 0.8));
    ingredientLabel->setColor(Color3B::WHITE);
    this->addChild(ingredientLabel);

    // �����رհ�ť
    createCloseButton();

    // ��ʼ��ʳ���ԭ���ϵ�ӳ��
    foodRecipes["ice_cream"] = { "cow_milk" };
    foodRecipes["french_fries"] = { "pumpkin_fruit" };
    foodRecipes["pizza"] = { "pumpkin_fruit", "chicken_egg"};

    return true;
}

void RecipeLayer::createFoodSprites()
{
    // �ȼ��� bag.plist �ļ�
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bag.plist");

    Vec2 Pos = Director::getInstance()->getVisibleSize() / 2;

    // ��������ܾ���
    Sprite* icecream = Sprite::createWithSpriteFrameName("ice_cream.png");
    icecream->setPosition(Vec2(Pos.x-120,Pos.y));
    icecream->setTag(1);
    this->addChild(icecream, Taskbarlayer);
    icecream->setScale(MapSize * 2);

    // �������⾫��
    Sprite* cake = Sprite::createWithSpriteFrameName("french_fries.png");
    cake->setPosition(Vec2(Pos.x, Pos.y));
    cake->setTag(2);
    this->addChild(cake, Taskbarlayer);
	cake->setScale(MapSize * 2);

    // ������������
    Sprite* pizza = Sprite::createWithSpriteFrameName("pizza.png");
    pizza->setPosition(Vec2(Pos.x + 120, Pos.y));
    pizza->setTag(3);
    this->addChild(pizza, Taskbarlayer);
	pizza->setScale(MapSize * 2);

    // ��Ӵ����¼�������
    auto icecreamListener = EventListenerTouchOneByOne::create();
    auto cakeListener = EventListenerTouchOneByOne::create();
    auto pizzaListener = EventListenerTouchOneByOne::create();

    // �����¼��������Ĵ����ص�
    icecreamListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        if (target->getBoundingBox().containsPoint(touch->getLocation())) {
            CCLOG("Ice Cream clicked!");
            onFoodSpriteClicked(target);
            return true;
        }
        return false;
        };

    cakeListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        if (target->getBoundingBox().containsPoint(touch->getLocation())) {
            CCLOG("Cake clicked!");
            onFoodSpriteClicked(target);
            return true;
        }
        return false;
        };

    pizzaListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        if (target->getBoundingBox().containsPoint(touch->getLocation())) {
            CCLOG("Pizza clicked!");
            onFoodSpriteClicked(target);
            return true;
        }
        return false;
        };

    // Ϊÿ����������¼�������
    icecream->getEventDispatcher()->addEventListenerWithSceneGraphPriority(icecreamListener, icecream);
    cake->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cakeListener, cake);
    pizza->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pizzaListener, pizza);

}

void RecipeLayer::onFoodSpriteClicked(Ref* sender)
{
    Sprite* foodSprite = dynamic_cast<Sprite*>(sender);//?

    if (foodSprite)
    {
        // ���ݾ����Tag���жϵ�������ĸ�ʳ��
        if (foodSprite->getTag() == 1)
            currentFood = "icecream";
        else if (foodSprite->getTag() == 2)
            currentFood = "cake";
        else if (foodSprite->getTag() == 3)
            currentFood = "pizza";

        // ����ʳ��ԭ������ʾ
        updateIngredientLabel(currentFood);
		canCookFood(currentFood);

    }
}

void RecipeLayer::updateIngredientLabel(const std::string& foodName)
{
    auto it = foodRecipes.find(foodName);
    if (it != foodRecipes.end())
    {
        std::string ingredients = "Ingredients: ";
        for (const auto& ingredient : it->second)
        {
            ingredients += ingredient + " ";
        }
        ingredientLabel->setString(ingredients);
    }
}

void RecipeLayer::canCookFood(const std::string& foodName)
{
	//�ж��Ƿ����㹻��ԭ����
	auto backpacklayer = BackpackLayer::getInstance();
	auto it = foodRecipes.find(foodName);
	if (it != foodRecipes.end())
	{
        for (const auto& ingredient : it->second)
        {
			if (!backpacklayer->removeItem(ingredient))
			{
                return;
			}
        }
    }
	backpacklayer->addItem(foodName);
    return;
}

void RecipeLayer::createCloseButton()
{
    closeBtn = MenuItemImage::create("XforTaskBar.png", "XforTaskBar.png", CC_CALLBACK_0(RecipeLayer::closeRecipe, this));
    closeBtn->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 50, Director::getInstance()->getVisibleSize().height - 50));

    Menu* closeMenu = Menu::create(closeBtn, nullptr);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu);
}

void RecipeLayer::closeRecipe()
{
    // �Ƴ�ʳ�ײ�
    this->removeFromParentAndCleanup(true);
}
