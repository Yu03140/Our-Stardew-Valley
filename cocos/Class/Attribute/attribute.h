#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>      // 用于 std::string 类型
#include "cocos2d.h"   // Cocos2d 主要头文件，包含所有核心类

// 玩家基本信息（如用户名、ID、手机号等）
class PlayerInformation {
public:
    PlayerInformation(const std::string& username, int playerId, const std::string& phoneNumber)
        : username(username), playerId(playerId), phoneNumber(phoneNumber) {}

    // 获取玩家信息
    std::string getUsername() const { return username; }
    int getPlayerId() const { return playerId; }
    std::string getPhoneNumber() const { return phoneNumber; }

private:
    std::string username;    // 玩家用户名
    int playerId;            // 玩家ID
    std::string phoneNumber; // 玩家手机号
};

// 玩家财产属性（经验、钱财、声望等）
class PlayerProperty {
public:
    // 构造函数
    PlayerProperty(const std::string& playerName)
        : experience(0), money(0), reputation(0) {}

    // 增加经验、钱财和声望
    void addExperience(int exp);
    void addMoney(int mon);
    void addReputation(int reputation_change);

    // 获取财产属性
    int getExperience() const { return experience; }
    int getMoney() const { return money; }
    int getReputation() const { return reputation; }

private:
    int experience;   // 经验值
    int money;        // 钱财
    int reputation;   // 声望
};

// 玩家类：管理玩家的财产属性和信息
class Player {
public:
    // 获取 Player 的单例实例
    static Player* getInstance(const std::string& username = "");

    // 删除拷贝构造函数和赋值操作符，确保单例不被复制
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    // 玩家财产属性
    PlayerProperty playerproperty;

private:
    // 私有构造函数，防止外部直接创建实例
    Player(const std::string& username);

    // 静态成员变量，用于保存唯一的 Player 实例
    static Player* player;

};

#endif // __PLAYER_H__
