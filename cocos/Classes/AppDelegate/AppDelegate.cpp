#include "AppDelegate.h"   // ����Ӧ�ó���ί����ͷ�ļ�
#include "Scene/MenuScene.h"  // ���볡����ͷ�ļ�
#include "Scene/FarmGround.h"

// �Ƿ�������Ƶ����
// #define USE_AUDIO_ENGINE 1
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

// ʹ��cocos2d��ȫ�������ռ䣬����ÿ�ζ�дCocos2d::
USING_NS_CC;  

// ����������Ʒֱ���
static cocos2d::Size designResolutionSize = cocos2d::Size(3200, 2000);  //��Ʒֱ���
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);     //С�ֱ���
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1280, 800);	//�зֱ���
static cocos2d::Size largeResolutionSize = cocos2d::Size(2560, 1600);	//��ֱ���


// ��������
AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();   // �����������Ƶ���棬�ͷ���Դ
#endif
}

// ��ʼ��OpenGL����������
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

//���ʹ�õ������⣬��Ҫ������ע��
static int register_all_packages()
{
    return 0; // ��ʾû���ⲿ����Ҫע��
}

// Ӧ�ó������������׼��������ѭ��ʱ����
bool AppDelegate::applicationDidFinishLaunching() {

    // ��ȡ������ʵ���������ฺ��������л���֡�ʿ���
    auto director = Director::getInstance();

	// ��ȡOpenGL��ͼ
    auto glview = director->getOpenGLView();

	// ���OpenGL��ͼΪ��,����һ���µ���ͼ
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("cocos", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("cocos");
#endif
        director->setOpenGLView(glview);
    }


    // �� FPS ��ʾ�����ڵ���
    director->setDisplayStats(true);

    // ����֡�ʣ�Ĭ��ֵΪ 1.0/60����ÿ�� 60 ֡
    director->setAnimationInterval(1.0f / 60);

    // ������Ʒֱ���
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    // ��ȡ�豸��ʵ�ʷֱ���
    auto frameSize = glview->getFrameSize();
    // �����豸�ֱ��ʵ����������ű���
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    // ע�������ⲿ������ʱû�У�
    register_all_packages();

    // ����һ���������󣬲�����
    auto scene = FarmScene::createScene();
    director->runWithScene(scene);

    return true;
}

// ��Ӧ�ó�������̨ʱ���ã���ӵ��绰���û����� Home ����
void AppDelegate::applicationDidEnterBackground() {
    // ֹͣ��������ͣ��Ϸ
    Director::getInstance()->stopAnimation();

// ��Ƶ�������
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// ��Ӧ�ó������½���ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground() {
    // �ָ�������������Ϸ
    Director::getInstance()->startAnimation();

// ��Ƶ�������
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
