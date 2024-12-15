#pragma once
#include <string>      // 用于 std::string 类型
#include <vector>      // 用于 std::vector
#include <iostream>    // 用于输入输出流
#include <ctime>       // 用于时间操作（例如日期和季节管理）
#include "cocos2d.h"  // Cocos2d 主要头文件，包含所有核心类
#include "2d/CCSprite.h"   // 用于图像和精灵渲染
#include "ui/UIButton.h"    // 用于按钮类（如果需要交互按钮）
#include "base/CCEventListener.h"   // 用于事件监听
#include <cmath>           // 用于数学运算（例如作物生长加速等）
#include <cstdlib>         // 用于随机数生成（例如随机掉落物品）
#include <algorithm>       // 用于一些常用算法，如 std::find
#include "ui/CocosGUI.h"// 用于 UI 按钮
#include <fstream>// 用于文件读写
#include <windows.h> // 包含 Windows 头文件，使用 MessageBoxW
#include <memory>// 用于智能指针


class PlayerPosition {//这里初始化应该为中间 后续改一下！！！！！！！！！！！！！！！
    int player_x = 1050;
    int player_y = 1050;
};




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







//玩家财产属性（经验值和经验等级 钱财 背包 声望）
class PlayerProperty {

private:
    int experience;          // 经验值
    int level = experience / 100;              // 经验等级
    int money;               // 钱财
    int reputation;          // 声望
    class Backpack;  // 背包物品

public:
    // 构造函数
    PlayerProperty(std::string name) : experience(0), money(0), reputation(0) {}

    // 增加经验
    void addExperience(int exp);
    // 增加钱财
    void addMoney(int mon);
    void addReputation(int reputation_change);
    //获取玩家属性并输出  (后面改成面板)
    void displayPlayerInfo() const;

};


class Player {
public:
    PlayerPosition playerposition;
    PlayerInformation playerinformation;  // 玩家信息
    PlayerProperty playerproperty;        // 玩家财产属性

};
