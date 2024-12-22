//----------------------------------------------------
// 精灵：可通过工具在地图中获取的物品
// 说明：需要该物品名称、获取所需点击次数、获取所需工具
//----------------------------------------------------
#ifndef __GETABLE_GOOD_H__
#define  __GETABLE_GOOD_H__

#include "cocos2d.h"
#include "Global/Global.h"
#include "progress_bar.h"

#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 80
#define EXPERIENCE 5
#define PERCENT 0.5
const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> GOODS_MAP =
{
	{"grass",{{"get","straw"},{"tool","Hoe"}}},
	{"SmallStone_in",{{"get","stone"},{"tool","Pick"}}},
	{"BigStone_in",{{"get","stone"},{"tool","Pick"}}},
	{"Rock_in",{{"get","copper"},{"tool","Pick"}}},
	{"tree",{{"develop_day","wood"},{"season","Axe"}}}
};
const std::unordered_map<std::string, int> GOODS_CLICK_MAP =
{
	{"grass",5 * 2},{"SmallStone_in",3 * 2},{"BigStone_in",5 * 2},{"Rock_in",10 * 2},{"tree",8 * 2}
};

class getable_goods : public cocos2d::Sprite
{
private:
	
	std::string sprite_name;
	Size sprite_size;
	int click_count = 0;
	static cocos2d::Texture2D* transparent_texture;
	progress_bar* click_bar = nullptr;
	bool is_getable = 0;//1->有可获取；0->已经被获取，此处为空

public:
	// 创建实例
	void set_info(std::string name, Size size);
	static getable_goods* create(const std::string& plist_name);
	void setImag();

	bool get_is_getable() { return is_getable; }
	// 初始化鼠标监听器
	void init_mouselistener();
	// 鼠标按下时的回调
	void on_mouse_click(cocos2d::Event* event);
	void show_click_bar();
	void hide_click_bar();
	void update();
	void add_goods(ValueMap dict, getable_goods* sprite, std::string name, cocos2d::TMXTiledMap* tileMap);

};

/*----------------------------------------------------------GoodsManager----------------------------------------------------------------------*/

class GoodsManager :public Node
{
private:
    // 使用 std::vector 来存储精灵
    std::vector<getable_goods*> goods;
	int getable_count = 0;
public:
	static GoodsManager* create();
    // 添加精灵到容器
	void add_goods(getable_goods* sprite);

	// 迭代器遍历访问精灵
	void get_getable_count();

    // 随机访问一个精灵（通过迭代器）
	void random_access();
	void start_scheduler();
	void stop_scheduler();

};


#endif __GETABLE_GOOD_H__