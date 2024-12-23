#include "NPC.h"


NPC::NPC()
    : npcSprite(nullptr), npcName("Unnamed"), affection(0), currentChatIndex(0), isChatting(false) {}

NPC::~NPC() {}

bool NPC::init(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    // 创建NPC精灵
    npcSprite = cocos2d::Sprite::create("Bouncer.png"); // 创建一个精灵，并将它设置为NPC的图像，使用"Bouncer.png"图片
    if (!npcSprite) return false;  // 如果图片没有加载成功，返回false，表示初始化失败

    // 设置NPC的位置
    this->setPosition(position);  // 设置当前NPC对象的位置，位置通过参数传递
    this->addChild(npcSprite);  // 将创建的精灵添加到当前NPC节点中，表示NPC会显示在该位置

    // 初始化NPC属性
    npcName = name;  // 将传入的name参数赋值给NPC的名字
    this->affection = affection;  // 设置NPC对玩家的好感度
    chatMessages = chatTexts;  // 存储NPC的聊天文本
    currentChatIndex = 0;  // 设置当前聊天文本的索引，初始值为0，表示第一条文本
    currentChatLabel = nullptr;  // 初始化为nullptr，表示没有当前显示的聊天标签

    // 创建聊天按钮
    chatButton = cocos2d::MenuItemLabel::create(
        cocos2d::Label::createWithSystemFont("Chat", "Arial", 24),  // 创建一个显示"Chat"文字的标签，字体为Arial，大小为24
        CC_CALLBACK_0(NPC::interact, this)  // 设置按钮点击时的回调函数，点击后调用NPC对象的interact方法
    );
    chatButton->setScale(0.5); // 放大四倍

    // 创建菜单并添加聊天按钮
    auto menu = cocos2d::Menu::create(chatButton, nullptr);  // 创建一个菜单，菜单中只包含一个按钮
    menu->setPosition(cocos2d::Vec2(0, -50));  // 设置菜单的位置，将按钮放置在NPC的下方300个单位的地方

    this->addChild(menu, 16);
    //this->addChild(menu);  // 将菜单添加到NPC节点中，这样按钮就能显示出来

    // 隐藏聊天按钮
    chatButton->setVisible(false);  // 默认情况下不显示按钮


    return true;  // 返回true，表示初始化成功
}




NPC* NPC::create(const cocos2d::Vec2& position, const std::string& name, int affection,
    const std::vector<std::string>& chatTexts) {

    // 创建 NPC 对象
    NPC* npc = new NPC();  // 动态创建一个新的 NPC 对象

    // 初始化 NPC 对象
    if (npc && npc->init(position, name, affection, chatTexts)) {
        // 如果 NPC 对象创建成功且初始化成功
        npc->autorelease();  // 自动管理内存，使用 cocos2d::Node 的内存管理机制
        return npc;  // 返回成功创建的 NPC 对象
    }
    else {
        // 如果创建或初始化失败，删除对象并返回空指针
        delete npc;  // 手动删除对象，防止内存泄漏
        return nullptr;  // 返回空指针，表示创建失败
    }
}


void NPC::startChat() {
    if (currentChatIndex < chatMessages.size()) {
        // 如果之前有对话框，移除它
        if (currentChatLabel) {
            currentChatLabel->removeFromParent();  // 从父节点中移除当前的标签
        }

        // 输出当前聊天内容
        cocos2d::log("NPC [%s]: %s", npcName.c_str(), chatMessages[currentChatIndex].c_str());

        // 创建新的聊天标签并显示
        currentChatLabel = cocos2d::Label::createWithTTF(chatMessages[currentChatIndex], "fonts/arial.ttf", 24);
        //currentChatLabel->setVisible(true);
        currentChatLabel->setPosition(getPosition() + cocos2d::Vec2(0, 100));  // 显示在NPC上方
        currentChatLabel->setScale(2); // 放大二倍
        currentChatLabel->setTextColor(cocos2d::Color4B::BLACK);
        this->getParent()->addChild(currentChatLabel);  // 将新的标签添加到父节点

        // 更新聊天索引
        currentChatIndex++;
        currentChatLabel->setVisible(true);
    }
    else {
        // 如果没有更多对话，结束对话
        cocos2d::log("End of conversation with NPC [%s].", npcName.c_str());
        currentChatIndex = 0;
        currentChatLabel->setVisible(false);//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        isChatting = false;  // 结束聊天

        // 隐藏聊天按钮或禁用按钮
        //chatButton->setVisible(false);  // 隐藏聊天按钮
        // 或者禁用按钮
        // chatButton->setEnabled(false);  
    }
}




void NPC::interact() {
    // 添加日志查看是否进入到函数
    cocos2d::log("NPC [%s] clicked, isChatting: %d", npcName.c_str(), isChatting);

    if (isChatting) {
        // 如果NPC正在聊天，调用startChat()继续对话
        //currentChatLabel->setVisible(true);
        startChat();
    }
    else {
        // 如果NPC没有开始聊天，设置为正在聊天
        isChatting = true;
        //currentChatLabel->setVisible(true);
        startChat();  // 开始对话
    }
}

void NPC::showChatButton(bool show) {
    if (chatButton) {
        chatButton->setVisible(show);  // 根据参数控制按钮是否可见
    }
}
