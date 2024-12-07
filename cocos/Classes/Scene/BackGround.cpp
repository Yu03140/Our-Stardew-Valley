#include "BackGround.h"
#include "cocos2d.h"

USING_NS_CC;

/*Scene* HomePage::createScene()
{
    return  Scene::create();
}

bool HomePage::init() {
    // 调用父类的 init 方法，确保场景初始化
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕可见区域的大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 添加背景图片
    auto background = Sprite::create("HelloWorld.png");
    if (!background) {
        CCLOG("Failed to load background image.");
        return false;
    }
    background->setPosition(origin + visibleSize / 2);  // 将背景图片设置为屏幕中央
    background->setContentSize(visibleSize);           // 可选：适配屏幕大小
    this->addChild(background, -1);                    // 添加到场景，设置 z-order 为 -1 使其位于最底层
        return true;
}

*/
