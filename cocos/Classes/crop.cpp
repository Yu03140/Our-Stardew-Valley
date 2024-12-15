#include "crop.h"

//ȫ�ֱ�����ʱ���л�ȡ


// ���徲̬��Ա��������ʼ��
std::string crop::crop_name = "";
int crop::develop_day = 0;
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
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto crop_pos = this->getPosition();
    // ����������Ч��Χ
    float min_x = crop_pos.x - crop_size.width / 2;
    float max_x = crop_pos.x + crop_size.width / 2;
    float min_y = crop_pos.y - crop_size.height / 2;
    float max_y = crop_pos.y + crop_size.height / 2;

    // ��������λ�ú���Ч��Χ
    CCLOG("Mouse clicked at: (%.2f, %.2f)", mouse_pos.x, mouse_pos.y);
    CCLOG("Crop valid range: X[%.2f, %.2f], Y[%.2f, %.2f]", min_x, max_x, min_y, max_y);

    if (mouse_pos.x > crop_pos.x - crop_size.width / 2 &&
        mouse_pos.x < crop_pos.x + crop_size.width / 2 &&
        mouse_pos.y > crop_pos.y - crop_size.height / 2 &&
        mouse_pos.y < crop_pos.y + crop_size.height / 2)
    {
        CCLOG("click crop");
        if (develop_level == -1) //�����ή���������
        {
            this->clear();
            CCLOG("clear the dead crop");
        }
        else if (develop_level == 5) {
            this->harvest();
            CCLOG("harvest the crop");
        }
        else if (goods_inhand.goods_name == "Can" && develop_level > 0) //��Ҫ���ϵĹ���Ϊˮ����ִ�н�ˮ
        {
            this->water();
            CCLOG("water this crop successfully");
        }
        else if (CROP_MAP.count(goods_inhand.goods_name) && develop_level == 0) //��������õ���Ʒ����ֲֲ��
        {
            this->planting(goods_inhand.goods_name);
            CCLOG("plant a crop");
        }
        else{
            CCLOG("water crop should take can in hand");
        }
    }
}

//��ˮ
void crop::water()
{
    if(watered_today)//������컹�н�ˮ����
    {
        watered_today -= 1;
    }
}

//��ֲ
void crop::planting(std::string name) {
    if (CROP_MAP.at(name).at("season") == SEASON) {
        crop_name = name;
        develop_level = 1;
        develop_day = 1; /************************************************/
        std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
        this->setSpriteFrame(framename);
        this->setScale(6.0f);  // ������Ŵ� 4 ��

        //����������-1
        CCLOG("plant successfully");
    }
    else
        CCLOG("the crop couldn't plant in this season");
}

//ʩ��
void crop::fertilize()
{
    develop_level += 1;
    std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
    this->setSpriteFrame(framename);
    //���������-1
}

//����
void crop::harvest()
{
    //����������뱳�� 
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
    watered_today = 1 + IS_DRY_DAY;
    this->initWithTexture(transparent_texture);
}

//����
void crop::update_day()
{
    if (TODAY != now_day)//���������
    {
        if (develop_level > 0) {
            if (watered_today)//˵�����콽ˮ����û�дﵽҪ��
            {
                unwater_count++;
                if (unwater_count == DIE_DRY) {
                    develop_level = -1;
                    this->setSpriteFrame("-1.png");
                    
                }
            }
            else//���콽ˮ�ﵽҪ��
            {
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
        now_day = TODAY;
        watered_today = 1 + IS_DRY_DAY;

    }
}
