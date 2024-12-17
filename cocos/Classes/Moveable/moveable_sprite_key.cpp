/****************************************************************************
�����ص㣺���¼��̷���������շ����ƶ���ִ���ƶ�������������߽�ʱ���ƶ�
ʹ�÷�ʽ��
    auto sprite_move = moveable_sprite_key::create("name.plist","name");
    if (sprite_move)
    {
        // ���ó�ʼλ��
        sprite_move->setPosition());
        // ��������ӵ�������
        this->addChild(sprite_move);
        // ��ʱ���� update ���¾����λ��
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key");
    }
ʹ��Ҫ��plist�ļ������������ƶ��ĺ�׺�ֱ�Ϊ{"-back","-front","-left","-right"}������ÿ���������ĸ���·�Ķ�������׺Ϊ{"1","2","3","4"}
 ****************************************************************************/
//void moveable_sprite_key_tool::update(float deltaTime) �貹�䣡

#include "moveable_sprite_key.h"
// ��̬��Ա��������
std::string moveable_sprite_key::sprite_name = ""; 
std::string moveable_sprite_key_walk::sprite_name_walk = "";
std::string moveable_sprite_key_tool::sprite_name_tool = "";
cocos2d::Texture2D* moveable_sprite_key_tool::transparent_texture = nullptr;
cocos2d::Texture2D* moveable_sprite_key::transparent_texture = nullptr;

//����һ��moveable_sprite_key��ʵ��
moveable_sprite_key* moveable_sprite_key::create(const std::string& plist_name, float width, float height)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //����ʵ��
    moveable_sprite_key* sprite = new moveable_sprite_key();

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
        sprite->initWithTexture(transparentTexture);
        sprite->autorelease();
        sprite->init_keyboardlistener();
        CCLOG("Creation moveable_sprite_key successfully!");
        return sprite;
    }
    CCLOG("Creation moveable_sprite_key unsuccessfully!");
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

//���̼�����
void moveable_sprite_key::init_keyboardlistener()
{
    // �������̼�����
    auto listener = cocos2d::EventListenerKeyboard::create();

    // ��������ʱ�Ļص�
    listener->onKeyPressed = CC_CALLBACK_2(moveable_sprite_key::onKeyPressed, this);

    // �����ͷ�ʱ�Ļص�
    listener->onKeyReleased = CC_CALLBACK_2(moveable_sprite_key::onKeyReleased, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//���¼���ʱ������Ӧ��������޸�Ϊtrue
void moveable_sprite_key::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        movement[0] = true; // ��
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        movement[1] = true; // ��
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        movement[2] = true; // ��
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        movement[3] = true; // ��
    }
}

//�ɿ����̺󣬽���Ӧ��������޸Ļ�false
void moveable_sprite_key::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    std::string default_framename = sprite_name + "-front1.png";
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        movement[0] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        movement[1] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        movement[2] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        movement[3] = false;
    }

    // �ɿ�����ʱ��ֹͣ���ж���
    this->stopAllActions();
    CCLOG("STOP");
    isAnimating = false;  // ��Ƕ���ֹͣ

}


//����λ��
void moveable_sprite_key::update(float deltaTime)
{
    //�����Ƿ񵽴�߽���жϽ��,�ֱ�Ϊ��������
    bool is_hit_edge[4] = { false,false, false, false };

    //��ȡ�����λ��
    sprite_pos = this->getPosition();

    //��ȡ���ڵĴ�С��Ϣ
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // �жϾ����Ƿ񳬳��߽�
   if (sprite_pos.y + this->getContentSize().height / 2 >= SceneHeight) {
       is_hit_edge[0] = true;
       CCLOG("Sprite hit the top edge");
    }
    else  if (sprite_pos.y - this->getContentSize().height / 2 <= origin.y) {
       is_hit_edge[1] = true;
       CCLOG("Sprite hit the bottom edge");
    }
    if (sprite_pos.x - this->getContentSize().width / 2 <= origin.x) {
        is_hit_edge[2] = true;
        CCLOG("Sprite hit the left edge");
    }
    else if (sprite_pos.x + this->getContentSize().width / 2 >= SceneWidth) {
        is_hit_edge[3] = true;
        CCLOG("Sprite hit the right edge");
    }

    for (int i = 0; i < 4; i++) {
        if (movement[i] && !is_hit_edge[i] && is_passable)
            move_act(i);
    }

    //��ȡ�����λ��
    sprite_pos = this->getPosition();
}

//�����ƶ�ָ��
void moveable_sprite_key::move_act(int direction)
{
    //�������ӦͼƬ��׺
    std::string dic[4] = { "-back","-front","-left","-right" };
    this->setSpriteFrame(sprite_name + dic[direction] + ".png");
    //�����ƶ�����
    auto move_action = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2(move_vecx[direction], move_vecy[direction]));
    this->runAction(move_action);
}

moveable_sprite_key_walk* moveable_sprite_key_walk::create(const std::string& plist_name, const std::string& sprite_framename)

{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //ͬ�������ͼ������
    sprite_name_walk = sprite_framename;

    //����ʵ��
    std::string default_framename = sprite_name_walk + "-front.png";
    moveable_sprite_key_walk* sprite = new moveable_sprite_key_walk();

    // ��ȡָ������֡
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(default_framename);

    //�ж��Ƿ��ܳɹ�����
    if (frame)
    {
        sprite->initWithSpriteFrame(frame);
        sprite->autorelease();
        sprite->setScale(4.0f);  // ������Ŵ� 4 ��
        sprite->init_keyboardlistener();
        CCLOG("Creation moveable_sprite_key_walk successfully!");
        return sprite;
    }
    CCLOG("Creation moveable_sprite_key_walk unsuccessfully!");
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

//���ɴ����ƶ��������ƶ�ָ��
void moveable_sprite_key_walk :: move_act(int direction)
{
    //�������ӦͼƬ��׺
    std::string dic[4] = { "-back","-front","-left","-right" };

    //�����ƶ�����
    auto move_action = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2( move_vecx[direction], move_vecy[direction]));
    //��������
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name_walk + dic[direction] + ".png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name_walk + dic[direction] + "2.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name_walk + dic[direction] + "3.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name_walk + dic[direction] + "4.png"));
    // ������������
    auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡��� 0.1s
    auto animate = cocos2d::Animate::create(animation);
    auto repeat = cocos2d::RepeatForever::create(animate);

    this->runAction(move_action);
    // �����û���ڲ��Ŷ������ſ�ʼ����
    if (!isAnimating) {
        // ִ���ƶ��Ͷ���
        this->runAction(repeat);
        isAnimating = true;  // ��Ƕ������ڲ���
    }
}



//����moveable_sprite_key_toolʵ��
moveable_sprite_key_tool* moveable_sprite_key_tool::create(const std::string& plist_name, float width, float height)

{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //����ʵ��
    moveable_sprite_key_tool* sprite = new moveable_sprite_key_tool();

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
        sprite->initWithTexture(transparentTexture);
        sprite->autorelease();
        sprite->setScale(3.0f);  // ������Ŵ� 3 ��
        sprite->init_keyboardlistener();
        CCLOG("Creation moveable_sprite_key_tool successfully!");
        return sprite;
    }
    CCLOG("Creation moveable_sprite_key_tool unsuccessfully!");
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void moveable_sprite_key_tool::update(float deltaTime){
    // �ȵ��ø���� update
    moveable_sprite_key::update(deltaTime);

    if (/*�������ϵ���Ʒ���ƣ�= sprite_name_tool*/true) {
        if (/*�������ϵ���Ʒ���� ���ڹ��� */true) {
            sprite_name_tool = "�������ϵ���Ʒ����";
            this->setSpriteFrame(sprite_name_tool + direc + ".png");
        }
        else{
            sprite_name_tool = "";
            this->setTexture(transparent_texture);
        }
    }
}

//�����ƶ�ָ��
void moveable_sprite_key_tool::move_act(int direction)
{
    std::string dic[4] = { "-back","-front","-left","-right" };
    if(sprite_name_tool != "") {
        //�������ӦͼƬ��׺
        this->setSpriteFrame(sprite_name_tool + dic[direction] + ".png");
    }
    direc = dic[direction];

    //�����ƶ�����
    auto move_action = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2(move_vecx[direction], move_vecy[direction]));
    this->runAction(move_action);
}

// ��ʼ����������
void moveable_sprite_key_tool::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ��갴��ʱ�Ļص�
    listener->onMouseDown = CC_CALLBACK_1(moveable_sprite_key_tool::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ��갴��ʱ�Ļص�
void moveable_sprite_key_tool::on_mouse_click(cocos2d::Event* event)
{
    CCLOG("tool click!");
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto tool_pos = this->getPosition();
    auto tool_size = this->getContentSize();

    if (mouse_pos.x > tool_pos.x - range &&
        mouse_pos.x < tool_pos.x + range &&
        mouse_pos.y > tool_pos.y - range &&
        mouse_pos.y < tool_pos.y + range)
    {
        // �л�����
        this->setSpriteFrame(sprite_name_tool + direc + "-clicked.png");

        // �� 0.2 ���ָ�ԭͼ
        this->scheduleOnce([this](float dt) {
            this->setSpriteFrame(sprite_name_tool + direc + ".png");
            }, 0.2f, "reset_texture_key");
        CCLOG("Mouse Position: (%f, %f)", mouse_pos.x, mouse_pos.y);
        click_pos = mouse_pos;
    }

}

