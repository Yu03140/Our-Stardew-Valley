
#include "HelloWorldScene.h"
#include "FarmGround.h"


USING_NS_CC;

// 切换到 MenuScene
void HelloWorld::onMenuItemClicked(Ref* sender) {
    Director::getInstance()->replaceScene(FarmScene::createScene());
}


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

// 添加背景图片
    auto background = Sprite::create("homepage.jpg");
    if (!background) {
        CCLOG("Failed to load background image.");
        return false;
    }
    background->setPosition(origin + visibleSize / 2);  // 将背景图片设置为屏幕中央
    background->setContentSize(visibleSize);           // 可选：适配屏幕大小
    this->addChild(background, -1);                    // 添加到场景，设置 z-order 为 -1 使其位于最底层


    auto title_sprite = Sprite::create("menu.png");
    title_sprite->setScale(1.5f); // 将精灵放大 1.5 倍
    title_sprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));// 设置位置（屏幕顶部中间）
    this->addChild(title_sprite, 0); // z-order 为 0，确保在背景上方


    auto menuItem1 = MenuItemImage::create("load1.png", "load2.png"); // 创建按钮，指定正常状态和选中状态的图片
    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event) {
        // 获取鼠标位置
        Vec2 mousePos = Director::getInstance()->convertToGL(static_cast<EventMouse*>(event)->getLocationInView());

        // 转换鼠标位置到 menuItem1 父节点的局部坐标
        Vec2 localMousePos = menuItem1->getParent()->convertToNodeSpace(mousePos);

        // 获取 menuItem1 的边界框
        Rect menuItemRect = menuItem1->getBoundingBox();

        // 判断鼠标是否悬停在按钮上
        if (menuItemRect.containsPoint(localMousePos)) {
            // 鼠标悬停在按钮上，放大按钮并切换到 load2.png
            menuItem1->setScale(1.2f);  // 放大按钮
            menuItem1->setNormalImage(Sprite::create("load2.png")); // 修改普通状态为 load2.png
        }
        else {
            // 鼠标离开按钮，恢复正常状态
            menuItem1->setScale(1.0f);  // 恢复原始大小
            menuItem1->setNormalImage(Sprite::create("load1.png")); // 恢复普通状态为 load1.png
        }
        };

    // 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // 定义点击按钮时切换场景的回调函数
    auto onButtonClicked = [](Ref* sender) {
        // 切换到下一个场景
        Director::getInstance()->replaceScene(FarmScene::createScene());  // 替换为下一个场景
        };

    // 设置按钮的点击回调函数
    menuItem1->setCallback(onButtonClicked);
    // 创建菜单并添加到场景中
    Menu* menu = Menu::create(menuItem1, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
