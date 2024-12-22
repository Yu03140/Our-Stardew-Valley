#include "getable_goods.h"


cocos2d::Texture2D* getable_goods::transparent_texture = nullptr;

void getable_goods::set_info(std::string name, Size size)
{
    sprite_name = name;
    sprite_size = size;
}

getable_goods* getable_goods::create(const std::string& plist_name)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //����ʵ��
    getable_goods* sprite = new getable_goods();

    // ����͸�����ڴ�飬����Ϊȫ͸�� (RGBA8888 ��ʽ)
    int dataSize = DEFAULT_WIDTH * DEFAULT_HEIGHT * 4;  // ÿ������ 4 �ֽڣ�RGBA ��ʽ��
    unsigned char* transparentData = new unsigned char[dataSize];

    // ���͸������ (ÿ�����ص� 4 ��ͨ��ֵ��Ϊ 0)
    memset(transparentData, 0, dataSize);

    // ����͸������
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, DEFAULT_WIDTH, DEFAULT_HEIGHT, cocos2d::Size(DEFAULT_HEIGHT, DEFAULT_HEIGHT));
    transparent_texture = transparentTexture;

    // �ͷ��ڴ�
    delete[] transparentData;

    //�ж��Ƿ��ܳɹ�����
    if (transparentTexture)
    {
        sprite->initWithTexture(transparentTexture);
        sprite->autorelease();
        sprite->init_mouselistener();
        CCLOG("Creation goods successfully!");
        return sprite;
    }
    CCLOG("Creation goods unsuccessfully!");
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void getable_goods::setImag()
{
    // ��ȡָ������֡
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name + ".png");
    this->initWithSpriteFrame(frame);
    is_getable = 1;
}

// ��ʼ����������
void getable_goods::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ���ص�
    listener->onMouseDown = CC_CALLBACK_1(getable_goods::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ��갴��ʱ�Ļص�
void getable_goods::on_mouse_click(cocos2d::Event* event)
{
    //��ȡ��Ʒλ��
    Vec2 goods_pos = this->convertToWorldSpace(Vec2(0, 0));
    // ����������Ч��Χ
    float min_x = goods_pos.x;
    float max_x = goods_pos.x + sprite_size.width ;
    float min_y = goods_pos.y;
    float max_y = goods_pos.y + sprite_size.height;
    if (is_getable && is_in_control) {
        //�����λ������Ч��Χ
        if ((MOUSE_POS.x > min_x &&
            MOUSE_POS.x < max_x &&
            MOUSE_POS.y > min_y &&
            MOUSE_POS.y < max_y))
        {
            if (backpackLayer->getSelectedItem().find(GOODS_MAP.at(sprite_name).at("tool")) != std::string::npos)//�����Ǹ���������Ʒƥ��
            {
                char last_char = backpackLayer->getSelectedItem()[backpackLayer->getSelectedItem().size() - 1];
                int level = last_char - '0';
                click_count += level;
                CCLOG("!!!!click_count:%d", click_count);
                this->show_click_bar();
                this->update();
            }
        }
    }
}

void getable_goods::show_click_bar()
{

    //��ʾ������
    if (!click_bar) {
        // �����������δ�������򴴽�����ʾ��
        click_bar = progress_bar::create();
        click_bar->show_progress_bar(cocos2d::Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2 + 5));
        this->getParent()->addChild(click_bar);
    }
    else {
        click_bar->show_progress_bar(cocos2d::Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2 + 5));
    }

    // ���㵱ǰ�Ľ��Ȱٷֱ�
    float progressValue = (float)click_count / (float)GOODS_CLICK_MAP.at(sprite_name) * 100.0f;
    CCLOG("@@@@@click_count:%d", click_count);

    click_bar->update_progress_bar(progressValue);

    // �ڵ���� 3 �����ؽ�����
    this->scheduleOnce([=](float delta) {
        hide_click_bar();
        }, 3.0f, "hide_progress_key_3s");
}

void getable_goods::hide_click_bar()
{
    if (click_bar) {
        click_bar->hide_progress_bar();
    }
}
void getable_goods::update()
{
    //�ж��Ƿ��ܻ��
    if (click_count >= GOODS_CLICK_MAP.at(sprite_name))
    {
        this->hide_click_bar();
        //����������뱳�� 
        backpackLayer->addItem(GOODS_MAP.at(sprite_name).at("get"));
        //���ﾭ������
        Player* player = Player::getInstance("me");
        player->playerproperty.addExperience(EXPERIENCE * GOODS_CLICK_MAP.at(sprite_name));
        this->setTexture(transparent_texture);//��Ϊ͸��
        click_count = 0;//���
        is_getable = 0;
    }
}

void getable_goods::add_goods(ValueMap dict, getable_goods* sprite, std::string name, cocos2d::TMXTiledMap* tileMap)
{
    float posX = dict["x"].asFloat();
    float posY = dict["y"].asFloat();
    float width = dict["width"].asFloat();
    float height = dict["height"].asFloat();

    // ����͸������ľ���
    sprite->set_info(name, Size(width * MapSize, height * MapSize));
    sprite->setPosition(Vec2(posX, posY));        // ����λ��
    sprite->setAnchorPoint(Vec2(0, 0));     // ����ê��
    sprite->setContentSize(Size(width, height));  // ���ô�С
    tileMap->addChild(sprite, 2);  // ��ӵ���Ƭ��ͼ
    sprite->init_mouselistener();
    sprite->setImag();
}

/*----------------------------------------------------------GoodsManager----------------------------------------------------------------------*/
GoodsManager* GoodsManager::create()
{
    GoodsManager* ret = new (std::nothrow) GoodsManager();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}
// ��Ӿ��鵽����
void GoodsManager::add_goods(getable_goods* sprite){
    goods.push_back(sprite); 
}

void GoodsManager::get_getable_count()
{
    getable_count = 0;
    // �������������ʾ���
    for (auto it = goods.begin(); it != goods.end(); ++it) {
        getable_count = (*it)->get_is_getable();
    }
}

// �������һ�����飨ͨ����������
void GoodsManager::random_access()
{
    get_getable_count();
    //�����ǰ�ɻ�ȡ����Ʒ�������٣��������������
    if (!goods.empty() && getable_count <= goods.size() * PERCENT) 
    {
        auto it = goods.begin();  // ��ȡ�����Ŀ�ʼ������

        std::advance(it, rand() % goods.size());  // �����ת��ĳ��λ��
        if ((*it)->get_is_getable() == 0) {
            (*it)->setImag();
        }
        
    }
}

void GoodsManager::start_scheduler() {
    CCLOG("%%%%START");

    // ʹ�ö�ʱ����ÿ 60 �����һ�� randomAccess
    this->schedule([this](float delta) {
        this->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");
}

void GoodsManager::stop_scheduler() {
    // ֹͣ��ʱ��
    this->unschedule("RandomAccessSchedulerKey");
}


