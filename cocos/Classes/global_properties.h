#pragma once
#include <string>
#include <cocos2d.h>

/*
BagManage.h
背包：
成员：
手上拿着的东西的名称 string
手上拿着的东西的等级 int 1/2
vector n个背包格（精灵的地址）；（显示的图片 plist
        //最开始瓦片地图导入的时候 遍历所有的bag_room 初始化精灵（纹理为空）
vector n个对应的名称
函数：
加入物品到背包（name）如果没有，设置纹理

包里有什么
消耗背包里的东西（消耗物品的名称 数量）

玩家：
成员：
玩家的位置
各种技能的经验值（种植、砍树、钓鱼、挖矿、料理）
与npc的互动好感度（关系、声望）

时间：
季节、当前季节天数
干旱日、节日（
新的一天：一天结束，跳出弹窗

任务
*/

extern int TODAY;
struct GOODS_INHAND {
    std::string goods_name;
};

extern struct GOODS_INHAND goods_inhand;
