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




class PlayerInformation;//玩家本身属性：玩家基本信息（姓名 ID 手机号码）
#define ExperienceOfLevel 100
class PlayerProperty;//玩家财产属性（经验值和经验等级 钱财 背包 声望）

class Backpack;// 背包类，用于管理所有物品

class Item;// 基础物品类，所有物品的基类
class Tool;// 工具类，继承自 Item 类，表示背包中的工具
class Seed;// 种子类，继承自 Item 类，表示背包中的种子
class Material;// 材料类，继承自 Item 类，表示背包中的材料
class Crop;// 农作物类，继承自 Item 类，表示背包中的农作物
class Fertilizer;// 肥料类，继承自 Item 类，表示背包中的肥料
class NPC;// NPC 类，表示游戏中的 NPC，包括Farmer（农民）等
class NPCtalk;// NPC 对话类，用于管理 NPC 对话