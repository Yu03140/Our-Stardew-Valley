#include "crop.h"
#define MAG_TIME_CROP 1.5f
// ���徲̬��Ա��������ʼ��
cocos2d::Texture2D* crop::transparent_texture = nullptr;
cocos2d::Size crop::crop_size = cocos2d::Size(0, 0);

// ����ʵ��
crop* crop::create(const std::string& plist_name, float width, float height)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    crop_size.width = width;
    crop_size.height = height;

    //����ʵ��
    crop* crop_sprite = new crop();

    // ����͸�����ڴ�飬����Ϊȫ͸�� (RGBA8888 ��ʽ)
    int dataSize = width * height * 4;  // ÿ������ 4 �ֽڣ�RGBA ��ʽ��
    unsigned char* transparentData = new unsigned char[dataSize];

    // ���͸������ (ÿ�����ص� 4 ��ͨ��ֵ��Ϊ 0)
    memset(transparentData, 0, dataSize);

    // ����͸������
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, width, height, cocos2d::Size(width, height));
    transparent_texture = transparentTexture;

    // �ͷ��ڴ�
    delete[] transparentData;


    //�ж��Ƿ��ܳɹ�����
    if (transparentTexture)
    {
        crop_sprite->initWithTexture(transparentTexture);
        crop_sprite->autorelease();
        crop_sprite->init_mouselistener();
        CCLOG("Creation cope successfully!");
        return crop_sprite;
    }
    CCLOG("Creation cope unsuccessfully!");
    CC_SAFE_DELETE(crop_sprite);
    return nullptr;
}

// ��ʼ����������
void crop::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ��갴��ʱ�Ļص�
    listener->onMouseDown = CC_CALLBACK_1(crop::on_mouse_click, this);
    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
// ��갴��ʱ�Ļص�
void crop::on_mouse_click(cocos2d::Event* event)
{
    /*------------------------------------------------------renew-------------------------------------------------------------*/
    //��ȡ����λ��
    Vec2 crop_pos = this->convertToWorldSpace(Vec2(0, 0));
    // ����������Ч��Χ
    float min_x = crop_pos.x;
    float max_x = crop_pos.x + crop_size.width * MapSize;
    float min_y = crop_pos.y;
    float max_y = crop_pos.y + crop_size.height * MapSize;
    if (is_in_control) {
        if ((MOUSE_POS.x > min_x &&
            MOUSE_POS.x < max_x &&
            MOUSE_POS.y > min_y &&
            MOUSE_POS.y < max_y))
        {
            CCLOG("click crop:%d", develop_level);
            switch (develop_level)
            {
            case -1: //�����ή���������
                CCLOG("clear the dead crop");
                this->clear();
                break;
            case 5: //������죬����ջ�
                CCLOG("harvest the crop");
                this->harvest();
            case 0://��ʱΪ�յ�
                if (CROP_MAP.count(backpackLayer->getSelectedItem())) //�����õ���Ʒ��ֲ������
                {
                    CCLOG("plant a crop");
                    this->planting(backpackLayer->getSelectedItem());
                }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                if (backpackLayer->getSelectedItem().find("Can") != std::string::npos) //���ϵĹ���Ϊˮ����ִ�н�ˮ
                {
                    CCLOG("water this crop");
                    this->water(backpackLayer->getSelectedItem());
                }
                else if (backpackLayer->getSelectedItem().find("Fertilizer") != std::string::npos)//���ϵĹ���Ϊ���ϣ�ִ��ʩ��
                {
                    CCLOG("fertilize this crop");
                    this->fertilize(backpackLayer->getSelectedItem());
                }
                else
                {
                    CCLOG("couldn't do anything to the crop");
                }
                break;
            default:
                CCLOG("ERROR develop_level!!!!");
                break;
            }

        }
    }
}

//��ˮ,���ݹ��ߵȼ������ߵȼ�Խ�ߣ���һ��ˮ����Ч����Խ��
void crop::water(std::string name)
{
    if (watered_today)//������컹�н�ˮ����
    {
        char last_char = name[name.size() - 1];
        int level = last_char - '0';
        watered_today = std::min(watered_today - level, 0);
        this->setSpriteFrame("water.png");

        // �� 0.2 ���ָ�ԭͼ
        this->scheduleOnce([this](float dt) {
            this->setSpriteFrame(crop_name + "-" + std::to_string(this->develop_level) + ".png");
            }, 0.2f, "reset_texture_crop");

        //����ˮ-1
        backpackLayer->removeItem(name);
        CCLOG("water successfully");
    }
    else
        CCLOG("couldn't water today");
}

//��ֲ
void crop::planting(std::string name) {
    if (CROP_MAP.at(name).at("season") == timeSystem->getSeason()) //��ʱ����ֲ�������ļ���
    {
        crop_name = name;
        develop_level = 1;
        develop_day = CROP_MAP.at(name).at("develop_day");
        std::string framename = this->crop_name + "-1.png";//��ʾ��һ�׶���ֲͼƬ����ʾ��ֲ�ɹ�
        this->setSpriteFrame(framename);
        this->setScale(MAG_TIME_CROP);

        //����������-1
        backpackLayer->removeItem(name);
        CCLOG("plant successfully");
    }
    else
        CCLOG("the crop couldn't be planted in this season");
}

//ʩ��,��������++�����ݹ��ߵȼ������ߵȼ�Խ�ߣ�������������Խ��
void crop::fertilize(std::string name)
{
    char last_char = name[name.size() - 1];
    int level = last_char - '0';
    develop_level = std::min(develop_level + level, 5);
    std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
    this->setSpriteFrame(framename);

    //���������-1
    backpackLayer->removeItem(name);
    CCLOG("fertilize successfully");
}

//���գ�ÿ���ջ�����EXPERIENCE����ֵ
void crop::harvest()
{
    //����������뱳�� 
    backpackLayer->addItem(HARVEST_MAP.at(crop_name));
    //���ﾭ������10
    Player* player = Player::getInstance("me");
    player->playerproperty.addExperience(EXPERIENCE);
    //�������
    this->clear();
}

//���
void crop::clear()
{
    water_count = 0;
    unwater_count = 0;
    develop_day = 0;
    develop_level = 0;
    crop_name = "";
    watered_today = 2 + timeSystem->getweather();
    this->initWithTexture(transparent_texture);
}

//����
void crop::update_day(float deltaTime)
{
    if (timeSystem->getDay() != now_day)//���������
    {

        if (develop_level > 0) {
            if (watered_today)//˵�����콽ˮ����û�дﵽҪ��
            {
                CCLOG("unwater today");
                unwater_count++;
                if (unwater_count == DIE_DRY) {
                    develop_level = -1;
                    this->setSpriteFrame("-1.png");
                    CCLOG("the crop die");
                }
            }
            else//���콽ˮ�ﵽҪ��
            {
                CCLOG("water successfully today:%d", water_count);
                water_count++;
                //�鿴�Ƿ���Ҫ���³ɳ�״̬
                if (water_count > develop_level * develop_day && water_count <= MAX_LEVEL * develop_day) {
                    this->develop_level++;
                    //������ʾ�ĳɳ�״̬
                    std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
                    this->setSpriteFrame(framename);
                }
            }
        }
        now_day = timeSystem->getDay();
        watered_today = WATER_PRED + timeSystem->getweather();
    }
}