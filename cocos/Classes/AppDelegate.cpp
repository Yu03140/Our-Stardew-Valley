/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "ChristmasScene.h"
//#include "UI_Scene.h"

// #define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(2560, 1600);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

// 如果你希望修改 OpenGL 上下文的设置，可以修改 glContextAttrs 的值。
// 这些设置会影响所有平台的渲染上下文配置。
void AppDelegate::initGLContextAttrs()
{
    // 设置 OpenGL 上下文属性：红色、绿色、蓝色、透明度（Alpha）、深度、模板缓冲、多重采样的数量
    // GLContextAttrs 构造函数的参数依次表示：
    // 红色通道的位数，绿色通道的位数，蓝色通道的位数，透明度通道的位数，深度缓冲的位数，模板缓冲的位数，多重采样的数量
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    // 设置 OpenGL 上下文的属性。这里传入 glContextAttrs，将这些属性应用到当前的 OpenGL 上下文配置中。
    GLView::setGLContextAttrs(glContextAttrs);
}


// 如果你希望使用包管理器安装更多的包，  
// 不要修改或删除这个函数。
static int register_all_packages()
{
    // 这里返回0，作为包管理器的标志
    return 0; // 包管理器的标志
}


bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化 Director。Director 是 Cocos2d-x 引擎的核心对象，负责管理游戏的渲染循环、场景切换等。
    auto director = Director::getInstance();

    // 获取当前的 OpenGL 渲染视图
    auto glview = director->getOpenGLView();

    // 如果当前没有 OpenGL 视图，则创建一个新的视图
    if (!glview) {
        // 根据平台创建不同类型的 OpenGL 渲染视图
        // 如果目标平台是 Windows、Mac 或 Linux，则使用 createWithRect 创建一个指定区域的视图
        // 参数是视图的名称和视图的矩形区域，矩形区域的大小由 designResolutionSize 决定
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("XLG", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
    // 否则，使用 create 方法创建默认的视图
        glview = GLViewImpl::create("XLG");
#endif

        // 设置 Director 使用新创建的 OpenGL 渲染视图
        director->setOpenGLView(glview);
}

    // 开启 FPS（帧率）显示
    director->setDisplayStats(true);

    // 设置每秒的帧数（FPS）。如果不设置，默认是 1/60（每秒 60 帧）。
    director->setAnimationInterval(1.0f / 60);

    // 设置设计分辨率（Design Resolution）
    // 设计分辨率定义了游戏开发时设计的分辨率，通常是一个固定值。这里设置为 designResolutionSize。
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // 获取实际的屏幕分辨率（框架大小）
    auto frameSize = glview->getFrameSize();

    // 根据设备的实际分辨率来调整游戏的缩放比例
    // 如果实际屏幕的高度大于中等分辨率的高度，则使用大分辨率的比例
    if (frameSize.height > mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height,
            largeResolutionSize.width / designResolutionSize.width));
    }
    // 如果实际屏幕的高度大于小分辨率的高度，但小于中等分辨率的高度，则使用中等分辨率的比例
    else if (frameSize.height > smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height,
            mediumResolutionSize.width / designResolutionSize.width));
    }
    // 如果实际屏幕的高度小于小分辨率的高度，则使用小分辨率的比例
    else {
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height,
            smallResolutionSize.width / designResolutionSize.width));
    }

    // 注册所有的包。此函数通常用于包管理器，处理外部资源或第三方库的加载
    register_all_packages();

    // 创建游戏场景。这里创建一个 NPCScene 场景对象。
    // NPCScene 是一个游戏场景，它会被自动管理内存（自动释放）。


    // 运行场景。设置 Director 运行该场景。
    //auto scene = cocos2d::Scene::create(); // 创建一个空场景
    auto scene = ChristmasScene::create(); // 创建你的层
    //scene->addChild(layer);               // 将层添加到场景


    //z这里用来加新的！！！！！！！！！！




    cocos2d::Director::getInstance()->runWithScene(scene); // 运行场景


    return true;
}


// 当应用程序进入后台时，调用此函数。注意，当接到电话时，该函数也会被调用。
void AppDelegate::applicationDidEnterBackground() {
    // 停止 Director（导演）的动画。Director 是管理游戏场景和动画的核心对象。
    // 当应用进入后台时，我们停止动画以减少资源的消耗，避免不必要的计算和渲染。
    Director::getInstance()->stopAnimation();

    // 如果启用了音频引擎（USE_AUDIO_ENGINE 被定义为 true），则暂停所有音频播放。
    // 这避免了在应用处于后台时仍然播放音频，节省资源并避免干扰用户。
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// 当应用程序重新变为活跃状态时（例如从后台返回前台），调用此函数。
void AppDelegate::applicationWillEnterForeground() {
    // 恢复 Director（导演）的动画。
    // Director 是 Cocos2d-x 引擎的核心管理对象，负责处理场景、动画和渲染。
    // 调用 startAnimation 会重新启动动画和帧更新，使游戏继续运行。
    Director::getInstance()->startAnimation();

    // 如果启用了音频引擎（USE_AUDIO_ENGINE 被定义为 true），恢复所有被暂停的音频。
#if USE_AUDIO_ENGINE
    // 恢复所有音频播放，例如背景音乐和音效。
    // 这是应用程序回到前台时需要做的重要操作，确保用户继续听到声音。
    AudioEngine::resumeAll();
#endif
}

