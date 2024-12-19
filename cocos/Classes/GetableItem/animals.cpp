#include "animals.h"

std::string animals::animals_name = "";
int animals::produce_day = 0;
cocos2d::Sprite animals::produce;
cocos2d::Texture2D* animals::transparent_texture = nullptr;
cocos2d::Size animals::produce_size = cocos2d::Size(0, 0);
cocos2d::Vec2 animals::produce_pos = cocos2d::Vec2(0, 0);


// ����ʵ��
animals* animals::create(const std::string& plist_name, std::string name, cocos2d::Vec2 pos, cocos2d::Size size)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    
    //���û�����Ϣ
    animals_name = name;
    produce_size = size;
    produce_pos = pos;
    produce_day = ANIMAL_MAP.at(name);

    //����ʵ��
    animals* animals_sprite = new animals();
    Sprite* produce_sprite = new Sprite();

    // ����͸�����ڴ�飬����Ϊȫ͸�� (RGBA8888 ��ʽ)
    int dataSize = size.width * size.height * 4;  // ÿ������ 4 �ֽڣ�RGBA ��ʽ��
    unsigned char* transparentData = new unsigned char[dataSize];

    // ���͸������ (ÿ�����ص� 4 ��ͨ��ֵ��Ϊ 0)
    memset(transparentData, 0, dataSize);

    // ����͸������
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, size.width, size.height, size);
    transparent_texture = transparentTexture;

    // �ͷ��ڴ�
    delete[] transparentData;
    //�ж��Ƿ��ܳɹ�����
    if (transparentTexture && animals_sprite && produce_sprite)
    {
        animals_sprite->setSpriteFrame(animals_name + "-front.png");
        animals_sprite->autorelease();
        animals_sprite->init_mouselistener();
        animals_sprite->setScale(2.0f);  // ������Ŵ� 2 ��
        produce_sprite->initWithTexture(transparentTexture);
        produce_sprite->autorelease();
        produce_sprite->setScale(2.0f);  // ������Ŵ� 2 ��
        produce.setPosition(pos);
        CCLOG("Creation animal successfully!");
        return animals_sprite;
    }
    CCLOG("Creation animal unsuccessfully!");
    CC_SAFE_DELETE(animals_sprite);
    return nullptr;
}

// ��ʼ����������
void animals::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ��갴��ʱ�Ļص�
    listener->onMouseDown = CC_CALLBACK_1(animals::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ��갴��ʱ�Ļص�
void animals::on_mouse_click(cocos2d::Event* event)
{
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto animals_pos = this->getPosition();
    auto animals_size = this->getContentSize();
    CCLOG("animals clicked");
    if(is_in_control){
        if (mouse_pos.x > animals_pos.x - animals_size.width / 2 &&
            mouse_pos.x < animals_pos.x + animals_size.width / 2 &&
            mouse_pos.y > animals_pos.y - animals_size.height / 2 &&
            mouse_pos.y < animals_pos.y + animals_size.height / 2)//�������
        {
            if (backpackLayer->getSelectedItem() == FOOD) {
                this->feed();
            }
        }
        else if (mouse_pos.x > produce_pos.x - produce_size.width / 2 &&
            mouse_pos.x < produce_pos.x + produce_size.width / 2 &&
            mouse_pos.y > produce_pos.y - produce_size.height / 2 &&
            mouse_pos.y < produce_pos.y + produce_size.height / 2)//��������������
        {
            if (is_produce) {
                this->harvest();
            }
        }
    }
}

//ι��
void animals::feed()
{
    if (feed_today) {
        feed_today--;
        //����ʳ��-1
        backpackLayer->removeItem(FOOD);
        CCLOG("feed successfully");
    }
    else 
        CCLOG("couldn't feed today");
}

//���ɸ���Ʒ
void animals::create_produce()
{
    if (feed_count % produce_day == 0 && feed_count) 
    {
        produce.setSpriteFrame(animals_name + "-produce.png");//��ʾ������
        is_produce = 1;
        CCLOG("create produce");
    }
}

//�ջ���
void animals::harvest()
{    
    //����������뱳��
    backpackLayer->addItem(PRODUCE_MAP.at(animals_name));
    //����������EXPERIENCE
    Player* player = Player::getInstance("me");
    player->playerproperty.addExperience(EXPERIENCE);
    produce.setTexture(transparent_texture);
    is_produce = 0;
}

// �����ƶ��������þ����ͼƬ
void animals::updateDirection(const cocos2d::Vec2& movementDirection) {
    float angle = movementDirection.getAngle();  // ����Ƕ�

    // ���ݽǶ�ѡ��ͼƬ�����磬�ĸ�����
    if (angle > -M_PI_4 && angle <= M_PI_4) {
        // ����
        this->setSpriteFrame(animals_name + "-right.png");
    }
    else if (angle > M_PI_4 && angle <= 3 * M_PI_4) {
        // ����
        this->setSpriteFrame(animals_name + "-back.png");
    }
    else if (angle > -3 * M_PI_4 && angle <= -M_PI_4) {
        // ����
        this->setSpriteFrame(animals_name + "-front.png");
    }
    else {
        // ����
        this->setSpriteFrame(animals_name + "-left.png");
    }
}
//�ε�
void animals::randmove(cocos2d::TMXTiledMap* tileMap)
{
    // ��ȡ��Ƭ��ͼ�Ĵ�С
    auto mapSize = tileMap->getMapSize();
    auto currentPos = this->getPosition();

    // ���ѡ��һ����Ƭ������
    int randomX = rand() % int(mapSize.width - 20);
    int randomY = rand() % int(mapSize.height - 20);

    auto tileSize = tileMap->getTileSize();  // ��ȡ��Ƭ�Ĵ�С

    // ������Ƭ����������
    float worldX = randomX * tileSize.width + tileMap->getPosition().x;
    float worldY = randomY * tileSize.height + tileMap->getPosition().y;

    // ʹ�� MoveTo �����ƶ�����
    auto targetPosition = cocos2d::Vec2(worldX, worldY);
    auto movementDirection = targetPosition - currentPos;  // �����ƶ�����
    this->updateDirection(movementDirection);
    float distance = movementDirection.length();
    auto moveAction = cocos2d::MoveTo::create(distance/SPEED, targetPosition);  // �ƶ���Ŀ��λ��
    this->runAction(moveAction);
}
//����ʱ�ε�
void animals::scheduleRandomMove(cocos2d::TMXTiledMap* tileMap) {
    // ÿ3������ƶ�һ��
    this->schedule([this, tileMap](float dt) {
        randmove(tileMap);
        }, 3.0f, "random_move_key");
}

//��һ��ĸ���
void animals::update_day(float deltaTime)
{
    if (timeSystem->getDay() != now_day)//���������
    {
        if (animals_name != "") {
            if (feed_today == 0)//˵������ι�������ﵽҪ��
            {
                feed_count++;
                //�鿴�Ƿ���Ҫ���³ɳ�״̬
                this->create_produce();
            }
        }
        now_day = timeSystem->getDay();
        feed_today = 1;
    }
}