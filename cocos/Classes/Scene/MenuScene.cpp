/****************************************************************************
 * 功能介绍:
 * 这是一个简单的 Cocos2d-x 游戏场景，展示了如何使用精灵、菜单和鼠标事件来制作互动界面。
 * 主要功能包括：
 * - 显示一个背景图片和标题图片
 * - 创建一个按钮，并根据鼠标悬停状态更改按钮的图片和大小
 * - 点击按钮时切换到另一个场景
 * - 提供关闭按钮退出程序
 ****************************************************************************/

#include "MenuScene.h"
#include "FarmGround.h"

USING_NS_CC;

// 点击菜单项时的回调函数
void MenuScene::onMenuItemClicked(Ref* sender) {
    // 切换到 FarmScene 场景
    Director::getInstance()->replaceScene(FarmScene::createScene());
}

// 创建场景
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// 处理加载文件时的错误信息
static void problemLoading(const char* filename)
{
    printf("加载错误: %s\n", filename);
    printf("根据你的编译方式，可能需要在文件名前加上 'Resources/' 路径\n");
}

// 在初始化时进行实例化
bool MenuScene::init()
{
    //////////////////////////////
    // 1. 调用父类的初始化方法
    if (!Scene::init())
    {
        return false;
    }

    // 获取屏幕可视区域的大小和原点
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. 添加一个菜单项，点击后退出程序
    // 你可以根据需要修改该部分。

    // 创建一个“关闭”按钮用于退出程序
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' 和 'CloseSelected.png' 文件");
    }
    else
    {
        // 设置“关闭”按钮的位置
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // 添加背景图片
    auto background = Sprite::create("homepage.jpg");
    if (!background) {
        CCLOG("加载背景图片失败.");
        return false;
    }
    // 设置背景位置为屏幕中央
    background->setPosition(origin + visibleSize / 2);
    // 可选：适配屏幕大小
    background->setContentSize(visibleSize);
    // 添加到场景并设置 z-order 为 -1，使其位于最底层
    this->addChild(background, -1);

    // 加载原始图片纹理
    auto texture = Director::getInstance()->getTextureCache()->addImage("menu.png");
    if (!texture) {
        CCLOG("加载菜单图片失败.");
        return false;
    }

    // 截取 menu.png 的上部分作为标题
    Rect titleRect(0, 0,
        texture->getContentSize().width,  // 宽度是纹理宽度
        texture->getContentSize().height / 4 + 50); // 高度是纹理高度的一部分
    auto title_sprite = Sprite::createWithTexture(texture, titleRect);  // 创建裁剪后的精灵
    if (!title_sprite) {
        CCLOG("创建标题精灵失败.");
        return false;
    }
    title_sprite->setScale(1.5f); // 放大标题精灵 1.5 倍
    title_sprite->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4)); // 设置标题位置（屏幕顶部中间）
    this->addChild(title_sprite, 0); // z-order 为 0，确保标题在背景上方

    // 创建一个菜单项按钮
    auto menuItem1 = MenuItemImage::create("load1.png", "load2.png"); // 创建按钮，指定普通状态和选中状态的图片
    menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event) {
        // 获取鼠标位置
        Vec2 mousePos = Director::getInstance()->convertToGL(static_cast<EventMouse*>(event)->getLocationInView());

        // 判断鼠标是否悬停在按钮上
        Rect menuItemRect = menuItem1->getBoundingBox();
        if (menuItemRect.containsPoint(mousePos)) {
            // 鼠标悬停在按钮上，放大按钮并切换到 load2.png
            menuItem1->setScale(1.2f);  // 放大按钮
            menuItem1->setNormalImage(Sprite::create("load2.png")); // 切换到 load2.png
        }
        else {
            // 鼠标离开按钮，恢复原大小
            menuItem1->setScale(1.0f);  // 恢复原始大小
            menuItem1->setNormalImage(Sprite::create("load1.png")); // 恢复为 load1.png
        }
        };

    // 添加事件监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 定义点击按钮时切换场景的回调函数
    auto onButtonClicked = [](Ref* sender) {
        // 点击按钮后，切换到 FarmScene 场景
        Director::getInstance()->replaceScene(FarmScene::createScene());
        };

    // 设置按钮的点击回调函数
    menuItem1->setCallback(onButtonClicked);

    // 创建菜单并添加到场景中
    Menu* menu = Menu::create(menuItem1, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);


}

// 关闭按钮的回调函数
void MenuScene::menuCloseCallback(Ref* pSender)
{
    // 关闭 Cocos2d-x 游戏场景并退出应用程序
    Director::getInstance()->end();

    /*如果是在 iOS 平台并且希望返回原生 iOS 界面，不能直接调用 Director::getInstance()->end()，
    * 需要触发一个自定义事件，像下面这样：
    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}
