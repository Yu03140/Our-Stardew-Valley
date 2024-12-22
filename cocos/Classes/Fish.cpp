#include "Fish.h"
#define MAG_TIME_CROP 1.5f
// ���徲̬��Ա��������ʼ��
//cocos2d::Texture2D* crop::transparent_texture = nullptr;
//cocos2d::Size crop::crop_size = cocos2d::Size(0, 0);

Fish* Fish::create(const std::string& spriteName) {
    Fish* fish = new Fish();
    if (fish && fish->initWithFile(spriteName)) {
        fish->autorelease();
        CCLOG("Fishhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh created successfully.");

        return fish;
    }
    CCLOG("DELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETE.");

    CC_SAFE_DELETE(fish);
    return nullptr;
}

//// ���� barrier ��λ�úͳߴ�
//void Fish::setBarrierProperties(cocos2d::Vec2 pos, float width, float height) {
//    barrierPos = pos;
//    barrierWidth = width;
//    barrierHeight = height;
//}
//moveable_sprite_key_walk* sprite_move = nullptr;

//void Fish::finishFishing(cocos2d::Layer* parentLayer) {
//    // ��������Ƿ����
//    if (!sprite_move) {
//        CCLOG("Player is null. Cannot create fish sprite.");
//        return;
//    }
//
//    // ��ȡ����λ��
//    cocos2d::Vec2 playerPosition = sprite_move->getPosition();
//
//    // �����㾫��
//    auto fishSprite = cocos2d::Sprite::create("fish.png");
//    if (fishSprite) {
//        // ���þ���λ��Ϊ����λ��
//        fishSprite->setPosition(playerPosition);
//
//        // ��Ӿ��鵽����
//        parentLayer->addChild(fishSprite);
//
//        // ���Ŷ���Ч��
//        auto scaleUp = cocos2d::ScaleTo::create(0.3f, 1.5f);
//        auto scaleDown = cocos2d::ScaleTo::create(0.3f, 1.0f);
//        auto sequence = cocos2d::Sequence::create(scaleUp, scaleDown, nullptr);
//        fishSprite->runAction(sequence);
//
//        CCLOG("Fish sprite created at position: (%f, %f)", playerPosition.x, playerPosition.y);
//    }
//    else {
//        CCLOG("Failed to create fish sprite.");
//    }





//
//// ��ʼ����������
//void Fish::init_mouselistener()
//{
//    // ������������
//    auto listener = cocos2d::EventListenerMouse::create();
//
//    // ��갴��ʱ�Ļص�
//    listener->onMouseDown = CC_CALLBACK_1(Fish::on_mouse_click, this);
//    // ��ȡ�¼��ַ�������Ӽ�����
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
// ��갴��ʱ�Ļص�
//void Fish::on_mouse_click(cocos2d::Event* event)
//{
//
//    //��ȡ����ڴ����е�λ��,ת������ͼ����
//    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
//    Vec2 mousePosition = mouse_event->getLocationInView();
//    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 windowOrigin = camera->getPosition() - Vec2(visibleSize.width / 2, visibleSize.height / 2);
//    Vec2 mouse_pos = mousePosition + windowOrigin;
//    MOUSE_POS = mouse_pos;
//    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
//
//    checkForPoolClick(mouse_pos);
//
//
//    // 0.1��� MOUSE_POS ��Ϊ (0, 0)�����Ҳ�Ӱ��������������
//    this->scheduleOnce([this](float dt) {
//        MOUSE_POS = Vec2::ZERO;
//        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
//        }, 1.5f, "reset_mouse_pos_key");
//
//    
//}
//
void Fish::carry_fishing(Vec2 mousePosition)
{
    if (!this) {
        CCLOG("Fish object is nullptr. Cannot proceed.");
        return;
    }
    CCLOG("Mouse Positioncarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishing: (%f, %f)", mousePosition.x, mousePosition.y);

    // ִ�й��߼��Ͳ���
    if (backpackLayer->getSelectedItem().find("Can1") != std::string::npos) {
        CCLOG("Waterrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");
        this->takewater(backpackLayer->getSelectedItem());
    }
    else if (backpackLayer->getSelectedItem().find("Rod1") != std::string::npos) {
        CCLOG("Fishingggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg");
        Sprite* fish_sprite = Sprite::create("bluefish.png");
        fish_sprite->setPosition(mousePosition);  // �������λ��Ϊ���λ��
        this->addChild(fish_sprite);

        this->fishing(backpackLayer->getSelectedItem());
    }
    else {
        CCLOG("Couldn't do anything to the pool");
    }


}

//��ˮ
void Fish::takewater(std::string name)
{
        char last_char = name[name.size() - 1];
        int level = last_char - '0';
     //   watered_today = std::min(watered_today - level, 0);
        this->setSpriteFrame("water.png");

 //  // �� 0.2 ���ָ�ԭͼ
 //  this->scheduleOnce([this](float dt) {
 //      this->setSpriteFrame(crop_name + "-" + std::to_string(this->develop_level) + ".png");
 //      }, 0.2f, "reset_texture_crop");

        //����ˮ+1
        backpackLayer->addItem(name);
        CCLOG("take water successfully");
}

//����
void Fish::fishing(std::string name) {



    fish_name = name;
//  develop_level = 1;
//  develop_day = CROP_MAP.at(name).at("develop_day");
    std::string framename = "load1.png";//��ʾ��ͼƬ����ʾ����ɹ�
    this->setSpriteFrame(framename);
    this->setScale(MAG_TIME_CROP);

    //��������+1
    CCLOG("fish successfully");
}


//���գ�ÿ���ջ�����EXPERIENCE����ֵ
void Fish::harvest()
{
// CCLOG("%s", HARVEST_MAP.at(crop_name));
// backpackLayer->addItem(name);
// //���ﾭ������10
// Player* player = Player::getInstance("me");
// player->playerproperty.addExperience(EXPERIENCE);

}


