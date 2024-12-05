//这里是游戏内部的属性
/*

包括：
1.玩家属性(玩家基本信息（姓名 ID 手机号码）经验总数经验等级（对应等级奖励） 金钱 声望 背包)
2.探索
工具属性（不同工具对应不同障碍）
掉落属性（掉落物品）
背包填充
3.地图属性（树 石头 水 设施）
4.NPC属性 （姓名 在小镇上的社会关系（职业） 对玩家的好感度 ）
5.社区


1、种植
种植季节（不可以种植非应季作物） 浇水天数达到成熟天数即可
土地施肥可以加速作物生长
2、养殖（鸡猪羊兔牛）

动态 喂食（每天一次） 升级 获得农产品
3、探索（工具）
斧头->树
锄头->种植
镰刀->草
钓具->鱼
剑->怪
镐->石头
 
在探索中获取物品->背包
 
4、NPC
动态 （不同身份、工作、亲属关系）
好感度（交互获得 买卖关系）
交互（触发对话 节日庆典）
5、场景
土地（施肥 种植）（树 草 石头 玩家的家园）
水（钓鱼）
不可到达的地方（工具清除障碍即可到达（变为可耕种的土地），同时掉落物品）
6、玩家属性
声望（与小镇居民互动可提升声望）
经验（种植、饲养动物，进行买卖，与NPC交互，探索荒地）
钱（售卖 购买）
背包（植物种子 成熟品 肥料 物品 工具）
7、时间系统
以玩家在线时间为时间流逝
30天一个季度
包括作物成熟时长 白天黑夜


*/

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
    int level = experience / ExperienceOfLevel;              // 经验等级
    int money;               // 钱财
    class Backpack;  // 背包物品

public:
    // 构造函数
    PlayerProperty(std::string name) : experience(0), money(0) {}

    // 增加经验
    void addExperience(int exp) {
        experience += exp;
    }
    // 增加钱财
    void addMoney(int mon) {
        money += mon;
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


#ifndef BACKPACK_H
#define BACKPACK_H



// 基础物品类，所有物品的基类
class Item {
public:
    virtual ~Item() = default;  // 虚拟析构函数
    virtual std::string getName() const = 0;  // 获取物品名称
};

// 工具类，继承自 Item 类，表示背包中的工具
class Tool : public Item {
public:
    // 定义工具类型
    enum class ToolType { Axe, Hoe, Sickle, FishingRod, Sword, Pickaxe };

    // 构造函数，初始化工具类型
    Tool(ToolType type) : type(type) {}

    // 获取工具名称
    std::string getName() const override {
        switch (type) {
            case ToolType::Axe: return "斧头";  // 斧头
            case ToolType::Hoe: return "锄头";  // 锄头
            case ToolType::Sickle: return "镰刀";  // 镰刀
            case ToolType::FishingRod: return "钓具";  // 钓具
            case ToolType::Sword: return "剑";  // 剑
            case ToolType::Pickaxe: return "镐";  // 镐
        }
        return "未知工具";
    }

private:
    ToolType type;  // 工具类型
};

// 种子类，继承自 Item 类，表示背包中的种子
class Seed : public Item {
public:
    // 定义种子类型(暂时包括小麦种子和玉米种子)
    enum class SeedType { WheatSeed, CornSeed};

    // 构造函数，初始化种子类型
    Seed(SeedType type) : type(type) {}

    // 获取种子名称
    std::string getName() const override {
        switch (type) {
            case SeedType::WheatSeed: return "小麦种子";  // 小麦种子
            case SeedType::CornSeed: return "玉米种子";  // 玉米种子
        }
        return "未知种子";
    }

private:
    SeedType type;  // 种子类型
};

// 材料类，继承自 Item 类，表示背包中的材料
class Material : public Item {
public:
    // 定义材料类型
    enum class MaterialType { IronOre, Wood, Straw };

    // 构造函数，初始化材料类型
    Material(MaterialType type) : type(type) {}

    // 获取材料名称
    std::string getName() const override {
        switch (type) {
            case MaterialType::IronOre: return "铁矿";  // 铁矿
            case MaterialType::Wood: return "木材";  // 木材
            case MaterialType::Straw: return "草料";  // 草料
        }
        return "未知材料";
    }

private:
    MaterialType type;  // 材料类型
};

// 农作物类，继承自 Item 类，表示背包中的农作物
class Crop : public Item {
public:
    // 定义农作物类型
    enum class CropType { Pork, Mutton, Beef, Egg, Wheat, Corn };

    // 构造函数，初始化农作物类型
    Crop(CropType type) : type(type) {}

    // 获取农作物名称
    std::string getName() const override {
        switch (type) {
            case CropType::Pork: return "猪肉";  // 猪肉
            case CropType::Mutton: return "羊肉";  // 羊肉
            case CropType::Beef: return "牛肉";  // 牛肉
            case CropType::Egg: return "鸡蛋";  // 鸡蛋
            case CropType::Wheat: return "小麦";  // 小麦
            case CropType::Corn: return "玉米";  // 玉米
        }
        return "未知农作物";
    }

private:
    CropType type;  // 农作物类型
};

// 肥料类，继承自 Item 类，表示背包中的肥料
class Fertilizer : public Item {
public:
    // 构造函数，初始化肥料名称
    Fertilizer(std::string name) : name(name) {}

    // 获取肥料名称
    std::string getName() const override {
        return name;  // 返回肥料名称
    }

private:
    std::string name;  // 肥料名称
};

// 背包类，用于管理所有物品
class Backpack {
public:
    // 添加物品到背包
    void addItem(std::shared_ptr<Item> item) {
        items.push_back(item);  // 将物品添加到背包
    }

    // 从背包移除指定名称的物品
    void removeItem(const std::string& itemName) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;  // 找到并移除物品
            }),
            items.end());
    }

    // 显示背包中的所有物品(这里后续改成面板)
    void displayItems() const {
        cocos2d::log("背包内容:");
        for (const auto& item : items) {
            cocos2d::log(" - %s", item->getName().c_str());  // 输出物品名称
        }
    }

private:
    std::vector<std::shared_ptr<Item>> items;  // 存储物品的容器
};

#endif // BACKPACK_H



class NPC : public cocos2d::Node {
private:
    std::string name;       // NPC的名字
    int affection;          // 好感度，范围为-100到100
    std::string dialogue;   // NPC的对话内容

public:
    // 构造函数，初始化NPC的名字、好感度和默认对话
    NPC(std::string npcName, int initialAffection, std::string npcDialogue)
        : name(npcName), affection(initialAffection), dialogue(npcDialogue) {}

    // 获取NPC的名字
    const std::string& getName() const {
        return name;
    }

    // 获取NPC的好感度
    int getAffection() const {
        return affection;
    }

    // 获取NPC的对话内容
    std::string getDialogue() const {
        return dialogue;
    }

    // 玩家与NPC的对话
    void talkToPlayer() {
        // 打印对话内容到控制台
        std::cout << name << " says: " << dialogue << std::endl;

        // 在游戏界面上显示对话
        // 使用cocos2d的Label显示文本
        cocos2d::Label* dialogueLabel = cocos2d::Label::createWithSystemFont(dialogue, "Arial", 24);
        dialogueLabel->setPosition(cocos2d::Vec2(500, 300));  // 设置位置（可以根据需要调整）
        this->addChild(dialogueLabel);  // 将标签添加到NPC节点下
    }

    // 玩家提高与NPC的好感度
    void increaseAffection(int amount) {
        affection += amount;
        if (affection > 100) affection = 100;  // 限制最大好感度

        std::cout << name << "'s affection increased by " << amount << "!" << std::endl;
    }

    // 玩家降低与NPC的好感度
    void decreaseAffection(int amount) {
        affection -= amount;
        if (affection < -100) affection = -100; // 限制最小好感度

        std::cout << name << "'s affection decreased by " << amount << "!" << std::endl;
    }

    // 展示NPC的当前状态（后续变为面板）
    void showStatus() const {
        std::cout << "NPC: " << name << "\n"
            << "Affection: " << affection << "\n"
            << "Dialogue: " << dialogue << "\n";
    }

    // 创建NPC的工厂方法
    static NPC* createNPC(std::string npcName, int initialAffection, std::string npcDialogue) {
        NPC* npc = new NPC(npcName, initialAffection, npcDialogue);
        if (npc) {
            npc->autorelease(); // 自动释放内存
        }
        return npc;
    }
};

// 在Cocos2d场景中使用这个NPC类(后续更改)
class NPCtalk : public cocos2d::Scene {
public:
    NPCtalk() {
        // 创建一个NPC实例
        NPC* npc1 = NPC::createNPC("Mysterious Stranger", 50, "Hello, traveler. Care to talk?");

        // 将NPC添加到场景
        this->addChild(npc1);

        // 显示NPC的状态
        npc1->showStatus();

        // 玩家与NPC对话
        npc1->talkToPlayer();

        // 玩家增加好感度
        npc1->increaseAffection(10);

        // 再次展示NPC状态
        npc1->showStatus();
    }
};

/* 程序入口
int main(int argc, char** argv) {
    // 初始化Cocos2d引擎
    cocos2d::Application app(argc, argv);

    // 创建场景并运行
    HelloWorld* scene = new HelloWorld();
    cocos2d::Director::getInstance()->runWithScene(scene);

    return app.run();
}*/










/*注册界面

class RegisterScene : public cocos2d::Scene {
public:
    RegisterScene() : playerIdCounter(0) {}

    static RegisterScene* create() {
        RegisterScene* ret = new RegisterScene();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        else {
            delete ret;
            return nullptr;
        }
    }

    bool init() {
        // 创建用户名输入框
        auto usernameLabel = cocos2d::Label::createWithSystemFont("Username:", "Arial", 24);
        usernameLabel->setPosition(200, 400);
        this->addChild(usernameLabel);

        usernameInput = cocos2d::ui::TextField::create("Enter your username", "Arial", 24);
        usernameInput->setPosition(cocos2d::Vec2(400, 400));
        this->addChild(usernameInput);

        // 创建手机号输入框
        auto phoneLabel = cocos2d::Label::createWithSystemFont("Phone Number:", "Arial", 24);
        phoneLabel->setPosition(200, 300);
        this->addChild(phoneLabel);

        phoneInput = cocos2d::ui::TextField::create("Enter phone number", "Arial", 24);
        phoneInput->setPosition(cocos2d::Vec2(400, 300));
        this->addChild(phoneInput);

        // 创建注册按钮
        auto registerButton = cocos2d::ui::Button::create("button_normal.png", "button_pressed.png");
        registerButton->setTitleText("Register");
        registerButton->setTitleFontSize(24);
        registerButton->setPosition(cocos2d::Vec2(400, 200));
        registerButton->addClickEventListener(CC_CALLBACK_1(RegisterScene::onRegister, this));
        this->addChild(registerButton);

        return true;
    }

private:
    int playerIdCounter;
    cocos2d::ui::TextField* usernameInput;
    cocos2d::ui::TextField* phoneInput;

    // 注册按钮点击事件
    void onRegister(cocos2d::Ref* sender) {
        std::string username = usernameInput->getString();
        std::string phoneNumber = phoneInput->getString();

        if (username.empty() || phoneNumber.empty()) {
            // 调用 Cocos2d 的 MessageBox 显示错误消息
            MessageBoxW(NULL, L"Username or Phone Number cannot be empty!", L"Error", MB_OK);

            return;
        }


        // 自动生成玩家ID
        playerIdCounter++;

        // 创建新的玩家对象
        Player newPlayer(username, playerIdCounter, phoneNumber);

        // 输出玩家信息
        std::cout << "Player Registered: " << std::endl;
        std::cout << "Username: " << newPlayer.getUsername() << std::endl;
        std::cout << "ID: " << newPlayer.getPlayerId() << std::endl;
        std::cout << "Phone: " << newPlayer.getPhoneNumber() << std::endl;

        // 可以将玩家数据存储到数据库或本地文件中
        // For example: savePlayerData(newPlayer);

        // 提示注册成功
        MessageBoxW(nullptr, L"Registration Successful!", L"Success", MB_OK);

    }
};


// 将玩家数据存储到本地文件中:
void savePlayerData(const Player& player) {
    std::ofstream file("players_data.txt", std::ios::app);
    file << "Username: " << player.getUsername() << "\n";
    file << "Player ID: " << player.getPlayerId() << "\n";
    file << "Phone: " << player.getPhoneNumber() << "\n";
    file << "==============================\n";
}*/























/*玩家属性
class Player {
public:

    //这里需要一个构造函数，用于初始化玩家属性。注册界面需要完成
    Player(std::string name, int id, std::string phoneNumber)
        : name(name), id(id), phoneNumber(phoneNumber), experience(0), level(1), money(0), reputation(0) {}

    void addExperience(int points);
    void levelUp();
    void earnMoney(int amount);
    void spendMoney(int amount);
    void updateReputation(int delta);

    // 背包相关
    void addToInventory(const std::string& item);
    void removeFromInventory(const std::string& item);

    // 获取玩家基本信息
    std::string getName() const { return name; }
    int getId() const { return id; }
    std::string getPhoneNumber() const { return phoneNumber; }
    int getExperience() const { return experience; }
    int getLevel() const { return level; }
    int getMoney() const { return money; }
    int getReputation() const { return reputation; }

private:
    std::string name;
    int id;
    std::string phoneNumber;
    int experience;
    int level;
    int money;
    int reputation;
    std::vector<std::string> inventory;  // 背包，存储物品名称
};

class Tool {
public:
    enum class ToolType { Axe, Hoe, Scythe, FishingRod, Sword, Pickaxe };

    Tool(ToolType type) : type(type) {}

    ToolType getType() const { return type; }

    // 工具功能
    void use() {
        switch (type) {
            case ToolType::Axe:
                // 砍树
                break;
            case ToolType::Hoe:
                // 锄地
                break;
            case ToolType::Scythe:
                // 收割草
                break;
            case ToolType::FishingRod:
                // 钓鱼
                break;
            case ToolType::Sword:
                // 打怪
                break;
            case ToolType::Pickaxe:
                // 挖石头
                break;
        }
    }

private:
    ToolType type;
};

class Terrain {
private:

    bool isAccessible;     // 是否可通过

public:
    // 枚举类型定义不同地形
    enum class TerrainType { Tree, Stone, Water, Grass, Home };

    // 构造函数
    Terrain(TerrainType type) : type(type), isAccessible(true) {}

    // 判断是否可通过
    bool isAccessible() const { return isAccessible; }

    // 使该地形可通过
    void makeAccessible() { isAccessible = true; }

    // 获取地形类型
    TerrainType getType() const { return type; }
private:
    TerrainType type;      // 地形类型


};

class Map {
public:
    Map(int width, int height) : width(width), height(height) {
        terrainGrid.resize(width, std::vector<Terrain>(height, Terrain(Terrain::TerrainType::Grass)));
    }

    void setTerrain(int x, int y, Terrain::TerrainType type) {
        terrainGrid[x][y] = Terrain(type);
    }

    Terrain getTerrain(int x, int y) const {
        return terrainGrid[x][y];
    }

private:
    int width;
    int height;
    std::vector<std::vector<Terrain>> terrainGrid;
};

class NPC {
public:
    NPC(std::string name, std::string occupation)
        : name(name), occupation(occupation), affection(0) {}

    void interact(Player& player);
    void updateAffection(int delta);

    std::string getName() const { return name; }
    std::string getOccupation() const { return occupation; }
    int getAffection() const { return affection; }

private:
    std::string name;
    std::string occupation;
    int affection;  // NPC对玩家的好感度
};

class Crop {
public:
    enum class CropType { Wheat, Carrot, Potato, Tomato };

    Crop(CropType type, int growthTime, int fertilizationTime)
        : type(type), growthTime(growthTime), fertilizationTime(fertilizationTime), currentGrowthTime(0) {}

    void waterCrop();
    void fertilizeCrop();
    void grow();
    bool isReadyForHarvest() const;

    CropType getType() const { return type; }

private:
    CropType type;
    int growthTime;          // 作物成长所需的时间
    int fertilizationTime;   // 施肥加速的时间
    int currentGrowthTime;   // 当前成长进度
};

class Farm {
public:
    void plantCrop(Crop::CropType type);
    void waterCrop(int x, int y);
    void fertilizeCrop(int x, int y);
    void harvestCrop(int x, int y);

    // 检查某个位置是否可以种植作物
    bool canPlant(int x, int y) const;

private:
    std::vector<std::vector<Crop>> farmGrid;  // 模拟土地格局
};

class Animal {
public:
    enum class AnimalType { Chicken, Pig, Sheep, Rabbit, Cow };

    Animal(AnimalType type) : type(type), hunger(100), level(1) {}

    void feed();
    void grow();
    void collectProducts();

    AnimalType getType() const { return type; }

private:
    AnimalType type;
    int hunger;
    int level;
    std::vector<Item> products;  // 动物产品（如鸡蛋、牛奶等）
};

class TimeSystem {
public:
    TimeSystem() : currentDay(1), currentMonth(1), currentSeason(1), isDayTime(true) {}

    void advanceDay();
    void switchToNextSeason();

    int getCurrentDay() const { return currentDay; }
    int getCurrentMonth() const { return currentMonth; }
    int getCurrentSeason() const { return currentSeason; }
    bool isDaytime() const { return isDayTime; }

private:
    int currentDay;
    int currentMonth;
    int currentSeason;
    bool isDayTime;
};

class Item {
public:
    enum class ItemType { Seed, Fertilizer, Tool, Crop, AnimalProduct };

    Item(ItemType type, std::string name) : type(type), name(name) {}

    ItemType getType() const { return type; }
    std::string getName() const { return name; }

private:
    ItemType type;
    std::string name;
};*/
