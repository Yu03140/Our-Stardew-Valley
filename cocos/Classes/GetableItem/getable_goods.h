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
	{"stones",{{"get","stone"},{"tool","Pick"}}},
	{"bigstone",{{"get","stone"},{"tool","Pick"}}},
	{"mine",{{"get","copper"},{"tool","Pick"}}},
	{"tree",{{"get","wood"},{"tool","Axe"}}},
	{"badGreenhouse",{{"get",""},{"tool",""}}}
};
const std::unordered_map<std::string, int> GOODS_CLICK_MAP =
{
	{"grass",3 * 2},{"stones",5 * 2},{"bigstone",10 * 2},{"mine",15 * 2},{"tree",10 * 2},{"badGreenhouse", 30 * 2}
};

class getable_goods : public cocos2d::Sprite
{
private:
	Size sprite_size;
	static cocos2d::Texture2D* transparent_texture;
	progress_bar* click_bar = nullptr;
protected:
	std::string sprite_name;
	int click_count = 0;
	bool is_getable = 0;//1->�пɻ�ȡ��0->�Ѿ�����ȡ���˴�Ϊ��
public:
	// ����ʵ��
	void set_info(std::string name, Size size);
	static getable_goods* create(const std::string& plist_name);
	virtual void setImag();

	bool get_is_getable() { return is_getable; }
	// ��ʼ����������
	void init_mouselistener();
	// ��갴��ʱ�Ļص�
	void on_mouse_click(cocos2d::Event* event);
	void show_click_bar();
	void hide_click_bar();
	virtual void update();
	void add_in(ValueMap dict, getable_goods* sprite, std::string name, cocos2d::TMXTiledMap* tileMap);
	virtual ~getable_goods() {}
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