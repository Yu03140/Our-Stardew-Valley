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
        // ��ʼ�����̼�����
        sprite_move->init_keyboardlistener();
        // ��ʱ���� update ���¾����λ��
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key");
    }
ʹ��Ҫ��plist�ļ������������ƶ��ĺ�׺�ֱ�Ϊ{"-back","-front","-left","-right"}������ÿ���������ĸ���·�Ķ�������׺Ϊ{"1","2","3","4"}
 ****************************************************************************/
#include "moveable_sprite_key.h"

// ��̬��Ա��������
std::string moveable_sprite_key::name = "";  // ��̬��Ա�����ĳ�ʼ��

//����һ��moveable_sprite_key��ʵ��
moveable_sprite_key* moveable_sprite_key::create(const std::string& plist_name, const std::string& sprite_framename)
{
    //����plist�ļ�
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //ͬ�������ͼ������
    name = sprite_framename;

    //����ʵ��
    std::string default_framename =name + "-front1.png";
    moveable_sprite_key* sprite = new moveable_sprite_key();

    // ��ȡָ������֡
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(default_framename);
    
    //�ж��Ƿ��ܳɹ�����
    if (frame)
    {
        sprite->initWithSpriteFrame(frame);
        sprite->autorelease();
        sprite->setScale(4.0f);  // ������Ŵ� 4 ��
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
    std::string default_framename = name + "-front1.png";
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

    // �ɿ�����ʱ���ָ���ʼ������ֹͣ���ж���
    this->setSpriteFrame(default_framename);
    this->stopAllActions();
    isAnimating = false;  // ��Ƕ���ֹͣ

}

//����λ��
void moveable_sprite_key::update(float deltaTime)
{
    //�����Ƿ񵽴�߽���жϽ��,�ֱ�Ϊ��������
    bool is_hit_edge[4] = { false,false, false, false };

    //��ȡ�����λ��
    cocos2d::Vec2 sprite_pos = this->getPosition();

    //��ȡ���ڵĴ�С��Ϣ
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // �жϾ����Ƿ񳬳��߽�
   if (sprite_pos.y + this->getContentSize().height / 2 >= origin.y + visibleSize.height) {
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
    else if (sprite_pos.x + this->getContentSize().width / 2 >= origin.x + visibleSize.width) {
        is_hit_edge[3] = true;
        CCLOG("Sprite hit the right edge");
    }


    for (int i = 0; i < 4; i++) {
        if (movement[i] && !is_hit_edge[i])
            move_act(i);
    }
}

//�����ƶ�ָ��
void moveable_sprite_key::move_act(int direction)
{
    //�������ӦͼƬ��׺
    std::string dic[4] = { "-back","-front","-left","-right" };

    //�����ƶ�����
    auto move_action = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2( move_vecx[direction], move_vecy[direction]));
    //��������
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "1.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "2.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "3.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "4.png"));
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
