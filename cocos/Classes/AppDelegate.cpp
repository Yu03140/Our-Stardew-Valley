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

// �����ϣ���޸� OpenGL �����ĵ����ã������޸� glContextAttrs ��ֵ��
// ��Щ���û�Ӱ������ƽ̨����Ⱦ���������á�
void AppDelegate::initGLContextAttrs()
{
    // ���� OpenGL ���������ԣ���ɫ����ɫ����ɫ��͸���ȣ�Alpha������ȡ�ģ�建�塢���ز���������
    // GLContextAttrs ���캯���Ĳ������α�ʾ��
    // ��ɫͨ����λ������ɫͨ����λ������ɫͨ����λ����͸����ͨ����λ������Ȼ����λ����ģ�建���λ�������ز���������
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    // ���� OpenGL �����ĵ����ԡ����ﴫ�� glContextAttrs������Щ����Ӧ�õ���ǰ�� OpenGL �����������С�
    GLView::setGLContextAttrs(glContextAttrs);
}


// �����ϣ��ʹ�ð���������װ����İ���  
// ��Ҫ�޸Ļ�ɾ�����������
static int register_all_packages()
{
    // ���ﷵ��0����Ϊ���������ı�־
    return 0; // ���������ı�־
}


bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ�� Director��Director �� Cocos2d-x ����ĺ��Ķ��󣬸��������Ϸ����Ⱦѭ���������л��ȡ�
    auto director = Director::getInstance();

    // ��ȡ��ǰ�� OpenGL ��Ⱦ��ͼ
    auto glview = director->getOpenGLView();

    // �����ǰû�� OpenGL ��ͼ���򴴽�һ���µ���ͼ
    if (!glview) {
        // ����ƽ̨������ͬ���͵� OpenGL ��Ⱦ��ͼ
        // ���Ŀ��ƽ̨�� Windows��Mac �� Linux����ʹ�� createWithRect ����һ��ָ���������ͼ
        // ��������ͼ�����ƺ���ͼ�ľ������򣬾�������Ĵ�С�� designResolutionSize ����
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("XLG", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
    // ����ʹ�� create ��������Ĭ�ϵ���ͼ
        glview = GLViewImpl::create("XLG");
#endif

        // ���� Director ʹ���´����� OpenGL ��Ⱦ��ͼ
        director->setOpenGLView(glview);
}

    // ���� FPS��֡�ʣ���ʾ
    director->setDisplayStats(true);

    // ����ÿ���֡����FPS������������ã�Ĭ���� 1/60��ÿ�� 60 ֡����
    director->setAnimationInterval(1.0f / 60);

    // ������Ʒֱ��ʣ�Design Resolution��
    // ��Ʒֱ��ʶ�������Ϸ����ʱ��Ƶķֱ��ʣ�ͨ����һ���̶�ֵ����������Ϊ designResolutionSize��
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // ��ȡʵ�ʵ���Ļ�ֱ��ʣ���ܴ�С��
    auto frameSize = glview->getFrameSize();

    // �����豸��ʵ�ʷֱ�����������Ϸ�����ű���
    // ���ʵ����Ļ�ĸ߶ȴ����еȷֱ��ʵĸ߶ȣ���ʹ�ô�ֱ��ʵı���
    if (frameSize.height > mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height,
            largeResolutionSize.width / designResolutionSize.width));
    }
    // ���ʵ����Ļ�ĸ߶ȴ���С�ֱ��ʵĸ߶ȣ���С���еȷֱ��ʵĸ߶ȣ���ʹ���еȷֱ��ʵı���
    else if (frameSize.height > smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height,
            mediumResolutionSize.width / designResolutionSize.width));
    }
    // ���ʵ����Ļ�ĸ߶�С��С�ֱ��ʵĸ߶ȣ���ʹ��С�ֱ��ʵı���
    else {
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height,
            smallResolutionSize.width / designResolutionSize.width));
    }

    // ע�����еİ����˺���ͨ�����ڰ��������������ⲿ��Դ���������ļ���
    register_all_packages();

    // ������Ϸ���������ﴴ��һ�� NPCScene ��������
    // NPCScene ��һ����Ϸ���������ᱻ�Զ������ڴ棨�Զ��ͷţ���


    // ���г��������� Director ���иó�����
    //auto scene = cocos2d::Scene::create(); // ����һ���ճ���
    auto scene = ChristmasScene::create(); // ������Ĳ�
    //scene->addChild(layer);               // ������ӵ�����


    //z�����������µģ�������������������




    cocos2d::Director::getInstance()->runWithScene(scene); // ���г���


    return true;
}


// ��Ӧ�ó�������̨ʱ�����ô˺�����ע�⣬���ӵ��绰ʱ���ú���Ҳ�ᱻ���á�
void AppDelegate::applicationDidEnterBackground() {
    // ֹͣ Director�����ݣ��Ķ�����Director �ǹ�����Ϸ�����Ͷ����ĺ��Ķ���
    // ��Ӧ�ý����̨ʱ������ֹͣ�����Լ�����Դ�����ģ����ⲻ��Ҫ�ļ������Ⱦ��
    Director::getInstance()->stopAnimation();

    // �����������Ƶ���棨USE_AUDIO_ENGINE ������Ϊ true��������ͣ������Ƶ���š�
    // ���������Ӧ�ô��ں�̨ʱ��Ȼ������Ƶ����ʡ��Դ����������û���
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// ��Ӧ�ó������±�Ϊ��Ծ״̬ʱ������Ӻ�̨����ǰ̨�������ô˺�����
void AppDelegate::applicationWillEnterForeground() {
    // �ָ� Director�����ݣ��Ķ�����
    // Director �� Cocos2d-x ����ĺ��Ĺ�����󣬸�����������������Ⱦ��
    // ���� startAnimation ����������������֡���£�ʹ��Ϸ�������С�
    Director::getInstance()->startAnimation();

    // �����������Ƶ���棨USE_AUDIO_ENGINE ������Ϊ true�����ָ����б���ͣ����Ƶ��
#if USE_AUDIO_ENGINE
    // �ָ�������Ƶ���ţ����米�����ֺ���Ч��
    // ����Ӧ�ó���ص�ǰ̨ʱ��Ҫ������Ҫ������ȷ���û���������������
    AudioEngine::resumeAll();
#endif
}

