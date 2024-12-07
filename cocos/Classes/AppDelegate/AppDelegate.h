#pragma once
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

 /*
  * Class Name:     AppDelegate
  * Class Function: Cocos2d-x Ӧ�ó�����
  */

class  AppDelegate : private cocos2d::Application
{
public:

    //��������
    virtual ~AppDelegate();

	//���ڳ�ʼ��OpenGL����������
    virtual void initGLContextAttrs();

    //Ӧ�ó������������׼��������ѭ��ʱ����
    virtual bool applicationDidFinishLaunching();

	//Ӧ�ó�������̨ʱ����
    virtual void applicationDidEnterBackground();

    //Ӧ�ó���Ӻ�̨���ص�ǰ̨ʱ����
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

