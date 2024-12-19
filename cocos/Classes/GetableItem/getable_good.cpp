#include "getable_good.h"

getable_good* getable_good::create(const std::string& plist_name)
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