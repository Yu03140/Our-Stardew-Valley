#include "attribute.h" 

//对于玩家
#ifndef __PLAYER_H__
#define __PLAYER_H__




//玩家本身属性：玩家基本信息（姓名 ID 手机号码）
class PlayerInformation {
public:
    // 构造函数，用于初始化玩家属性
    PlayerInformation(const std::string& username, int playerId, const std::string& phoneNumber)
        : username(username), playerId(playerId), phoneNumber(phoneNumber) {
        std::cout << "Player created: " << username << ", ID: " << playerId << ", Phone: " << phoneNumber << std::endl;
    }





    // 获取玩家用户名
    std::string getUsername() const { return username; }

    // 获取玩家ID
    int getPlayerId() const { return playerId; }

    // 获取玩家手机号
    std::string getPhoneNumber() const { return phoneNumber; }

private:
    std::string username;  // 玩家用户名
    int playerId;          // 玩家ID
    std::string phoneNumber; // 玩家注册手机号
};

#endif // __PLAYER_H__





//玩家财产属性（经验值和经验等级 钱财 背包 声望）
class PlayerProperty {

private:
    int experience;          // 经验值
    int level = experience/100;              // 经验等级
    int money;               // 钱财
    int reputation;          // 声望
    class Backpack;  // 背包物品

public:
    // 构造函数
    PlayerProperty(std::string name) : experience(0), money(0),reputation(0) {}

    // 增加经验
    void addExperience(int exp) {
        experience += exp;
    }
    // 增加钱财
    void addMoney(int mon) {
        money += mon;
    }
    void addReputation(int reputation_change) {
        reputation += reputation_change;
    }
    //获取玩家属性并输出  (后面改成面板)
    void displayPlayerInfo() const {
        std::cout << "经验值: " << experience << std::endl;
        std::cout << "等级: " << level << std::endl;
        std::cout << "钱财: " << money << std::endl;
        std::cout << "背包物品: ";
        /*for (const std::string& item : Backpack) {
            std::cout << item << " ";
        }*/
        std::cout << std::endl;
    }

};

