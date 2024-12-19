#include "getable_good.h"

getable_good* getable_good::create(const std::string& plist_name)
{
    //加载plist文件
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    crop_size.width = width;
    crop_size.height = height;

    //创建实例
    crop* crop_sprite = new crop();

    // 创建透明的内存块，设置为全透明 (RGBA8888 格式)
    int dataSize = width * height * 4;  // 每个像素 4 字节（RGBA 格式）
    unsigned char* transparentData = new unsigned char[dataSize];

    // 填充透明数据 (每个像素的 4 个通道值都为 0)
    memset(transparentData, 0, dataSize);

    // 创建透明纹理
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, width, height, cocos2d::Size(width, height));
    transparent_texture = transparentTexture;

    // 释放内存
    delete[] transparentData;


    //判断是否能成功创建
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