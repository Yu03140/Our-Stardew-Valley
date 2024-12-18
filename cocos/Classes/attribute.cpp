#include "attribute.h"

// 初始化 Player 的单例实例为 nullptr
Player* Player::player = nullptr;

// PlayerProperty 的成员函数：增加经验
void PlayerProperty::addExperience(int exp) {
    experience += exp;
    CCLOG("Experience: %d", experience);
}

// PlayerProperty 的成员函数：增加钱财
void PlayerProperty::addMoney(int mon) {
    money += mon;
    CCLOG("Money: %d", money);
}

// PlayerProperty 的成员函数：增加声望
void PlayerProperty::addReputation(int reputation_change) {
    reputation += reputation_change;
    CCLOG("Reputation: %d", reputation);
}

// Player 构造函数
Player::Player(const std::string& username)
    : playerproperty(username) {
    // 可以在这里初始化更多玩家属性
    CCLOG("Player %s created!", username.c_str());
}

// 获取 Player 的单例实例
Player* Player::getInstance(const std::string& username) {
    if (player == nullptr) {
        player = new Player(username);
    }
    return player;
}
