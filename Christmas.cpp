#include "Christmas.h"
#include "Global/Global.h"  
#include "cocos2d.h"
#include "Scene/FarmGround.h"

USING_NS_CC;

// 构造函数：初始化成员变量
ChristmasScene::ChristmasScene()
    : _background(nullptr), _talkBoard(nullptr), _scrollingText(nullptr), _getButton(nullptr),
    _isTextScrolling(false), _scrollingSpeed(0.2f) {}

// 析构函数：清理资源（这里暂时无手动清理逻辑）
ChristmasScene::~ChristmasScene() {}

// 创建场景静态方法，用于实例化圣诞场景对象
ChristmasScene* ChristmasScene::createScene() {
    // 创建 ChristmasScene 对象
    ChristmasScene* scene = new ChristmasScene();
    if (scene && scene->init()) { // 初始化场景
        scene->autorelease();     // 设置自动释放，防止内存泄漏
        return scene;
    }
    CC_SAFE_DELETE(scene);        // 如果初始化失败，安全释放内存
    return nullptr;
}

// 初始化方法：创建场景的所有元素（如背景、按钮等）
bool ChristmasScene::init() {
    // 调用父类的初始化方法，确保基础场景初始化成功
    if (!Scene::init()) {
        return false;
    }

    // 加载圣诞背景图
    _background = Sprite::create("ChristmasScene.png"); // 加载背景图资源
    if (_background) {
        // 设置背景图片位置为屏幕中央
        _background->setPosition(Director::getInstance()->getVisibleSize() / 2);
        _background->setScale(0.8);

        this->addChild(_background); // 将背景添加到当前场景
    }

    // 加载对话框背景
    _talkBoard = Sprite::create("TalkBoard.png"); // 加载对话框图片资源
    if (_talkBoard) {
        // 设置对话框位置为屏幕下方
        _talkBoard->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _talkBoard->getContentSize().height ));
        _talkBoard->setScale(2.0f);
        this->addChild(_talkBoard); // 将对话框添加到当前场景

        // 创建文字标签并添加到对话框
        _message = "Merry Christmas, Traveller!!!\n1000$ has been gathered for you!"; // 全部文字内容
        createFixedText(); // 调用方法创建文字标签
    }



    // 创建领取奖励按钮
    _getButton = MenuItemImage::create(
        "GetButton_Normal.png",   // 按钮正常状态的图片
        "GetButton_Normal.png",   // 按钮按下状态的图片
        CC_CALLBACK_1(ChristmasScene::onGetRewardClicked, this) // 按钮点击事件回调
    );
    if (_getButton) {
        // 设置按钮位置
        _getButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _getButton->getContentSize().height/2));
        // 创建菜单对象，将按钮加入菜单
        auto menu = Menu::create(_getButton, nullptr);
        menu->setPosition(Vec2::ZERO); // 将菜单位置设为零点
        //_talkBoard->setScale(0.5f);
        this->addChild(menu); // 将菜单添加到场景中
    }



    return true; // 初始化成功
}

// 创建滚动文本
void ChristmasScene::createFixedText() {
    // 使用系统字体创建空的文本标签
    _scrollingText = Label::createWithSystemFont("", "Arial", 15);
    if (_scrollingText) {
        // 偏移量（可以根据需求调整）
        float offsetX = -200.0f;  // X 轴偏移量
        float offsetY = 0.0f; // Y 轴偏移量

        // 设置文字标签位置，并加上偏移量
        _scrollingText->setPosition(Vec2(
            _talkBoard->getContentSize().width /32*10,   // X 坐标
            _talkBoard->getContentSize().height / 2 + offsetY   // Y 坐标
        ));

        _scrollingText->setColor(Color3B::BLACK); // 设置文字颜色为黑色
        _scrollingText->setOpacity(255);         // 设置完全不透明

        // 将文字标签作为子节点添加到对话框背景
        _talkBoard->addChild(_scrollingText);

        // 启动逐字显示逻辑
        schedule([this](float dt) {
            this->updateTextPerCharacter(dt); // 每帧更新显示一个字符
            }, 0.1f, "character_display_key"); // 每 0.1 秒更新一次
    }
}



void ChristmasScene::updateTextPerCharacter(float dt) {
    static size_t index = 0; // 当前显示到的字符索引
    if (index < _message.length()) {
        // 获取当前字符并追加到文字标签内容中
        std::string currentText = _scrollingText->getString();
        currentText += _message[index];
        _scrollingText->setString(currentText);

        // 索引递增，准备显示下一个字符
        index++;
    }
    else {
        // 文字显示完毕，取消调度器
        unschedule("character_display_key");
    }
}


// 点击领取奖励按钮的回调
void ChristmasScene::onGetRewardClicked(Ref* sender) {
    // 假设 Player 类管理玩家的货币
    Player* player = Player::getInstance("me"); // 获取当前玩家的实例
    player->playerproperty.addMoney(1000);      // 为玩家增加 1000$，这里假设 Player 类已经实现了货币管理
    goBackToMainScene();                        // 返回主场景
}

// 返回主场景
void ChristmasScene::goBackToMainScene() {
    // 使用 Cocos2d-x 的 popScene 方法，返回到场景栈中的上一场景（主场景）
    cocos2d::Director::getInstance()->popScene();
}


