//----------------------------------------------------
// ���飺��ͨ�������ڵ�ͼ�л�ȡ����Ʒ
// ˵������Ҫ����Ʒ���ơ���ȡ��������������ȡ���蹤��
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
	bool is_getable = 0;//1->�пɻ�ȡ��0->�Ѿ�����ȡ���˴�Ϊ��

public:
	// ����ʵ��
	void set_info(std::string name, Size size);
	static getable_goods* create(const std::string& plist_name);
	void setImag();

	bool get_is_getable() { return is_getable; }
	// ��ʼ����������
	void init_mouselistener();
	// ��갴��ʱ�Ļص�
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
    // ʹ�� std::vector ���洢����
    std::vector<getable_goods*> goods;
	int getable_count = 0;
public:
	static GoodsManager* create();
    // ��Ӿ��鵽����
	void add_goods(getable_goods* sprite);

	// �������������ʾ���
	void get_getable_count();

    // �������һ�����飨ͨ����������
	void random_access();
	void start_scheduler();
	void stop_scheduler();

};


#endif __GETABLE_GOOD_H__