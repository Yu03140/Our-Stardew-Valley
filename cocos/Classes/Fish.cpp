#include "Fish.h"
#define MAG_TIME_CROP 1.5f
// ���徲̬��Ա��������ʼ��
cocos2d::Texture2D* fish::transparent_texture = nullptr;
cocos2d::Size fish::fish_size = cocos2d::Size(0, 0);

// ����ʵ��
fish* fish::create(const std::string& plist_name, float width, float height)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    fish_size.width = width;
    fish_size.height = height;

    //����ʵ��
    fish* fish_sprite = new fish();

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
        fish_sprite->initWithTexture(transparentTexture);

        fish_sprite->autorelease();
        fish_sprite->init_mouselistener();
        CCLOG("Creation fishhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh successfully!");
        return fish_sprite;
    }
    CCLOG("Creation fishhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh unsuccessfully!");
    CC_SAFE_DELETE(fish_sprite);
    return nullptr;
}

// ��ʼ����������
void fish::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ��갴��ʱ�Ļص�
    listener->onMouseDown = CC_CALLBACK_1(fish::on_mouse_click, this);
    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
// ��갴��ʱ�Ļص�
void fish::on_mouse_click(cocos2d::Event* event)
{
    //��ȡ����λ��
    Vec2 fish_pos = this->convertToWorldSpace(Vec2(0, 0));
    // ����������Ч��Χ
    float min_x = fish_pos.x;
    float max_x = fish_pos.x + fish_size.width * MapSize;
    float min_y = fish_pos.y;
    float max_y = fish_pos.y + fish_size.height * MapSize;
    if (is_in_control) {
        //��������λ�ú���Ч��Χ
        if ((MOUSE_POS.x > min_x &&
            MOUSE_POS.x < max_x &&
            MOUSE_POS.y > min_y &&
            MOUSE_POS.y < max_y))
        {
                if (backpackLayer->getSelectedItem().find("Can") != std::string::npos) //���ϵĹ���Ϊˮ����ִ�н�ˮ
                {
                    CCLOG("water this crop");
                    this->water(backpackLayer->getSelectedItem());
                }
                else if (backpackLayer->getSelectedItem().find("Rod") != std::string::npos)//���ϵĹ���Ϊ���
                {
                    CCLOG("doing fishing");
                    this->fishing(backpackLayer->getSelectedItem());
                }
                else
                {
                    CCLOG("couldn't do anything to the crop");
                }

        }
    }
}

//��ˮ,���ݹ��ߵȼ������ߵȼ�Խ�ߣ���һ��ˮ����Ч����Խ��
void fish::water(std::string name)
{
    this->setSpriteFrame("water.png");


    //����ˮ+1
    backpackLayer->addItem(name);
    CCLOG("water successfully");
}
  
//����
void fish::fishing(std::string name)
{


    auto sprite = cocos2d::Sprite::create("menu.png");
    if (sprite) {
        // ���þ����λ�ã���Ļ����Ϊ����
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // ȷ�����������ϲ�
        sprite->setGlobalZOrder(1000); // �ϴ��ֵ�����ڸ��ϲ���ʾ

        // ��ӵ���ǰ����
        this->addChild(sprite);
        CCLOG("create sprite.");

   // // �ӳ�һ������ؾ���
   // this->scheduleOnce([sprite](float dt) {
   //     sprite->setVisible(false); // ����ֱ���� removeFromParent()
   //     }, 1.0f, "hide_sprite");
    }
    else {
        CCLOG("Failed to create sprite.");
    }
    std::string framename = "bluefish.png";
    this->setSpriteFrame(framename);

    CCLOG("%s", HARVEST_FISH_MAP.at(fish_name));
    //����������뱳�� 
    backpackLayer->addItem(fish_name,1);
    //���ﾭ������10
    Player* player = Player::getInstance("me");
    player->playerproperty.addExperience(EXPERIENCE);
    CCLOG("fishing successfully");

}


//���
void fish::clear()
{
    fish_name = "";
    this->initWithTexture(transparent_texture);
}
