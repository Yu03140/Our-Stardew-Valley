#ifndef __MAIN_H__
#define __MAIN_H__

// �ú궨���ų� Windows ͷ�ļ��в����õĲ���
#define WIN32_LEAN_AND_MEAN             

#include <windows.h>
#include <tchar.h>  // ͨ���ַ�����
#include "platform/CCStdC.h"

#endif    

#include "AppDelegate/AppDelegate.h"

// �ú궨���ų� Windows ͷ�ļ��в����õĲ���
#define WIN32_LEAN_AND_MEAN          

USING_NS_CC;

/*
 * Function Name:    _tWinMain
 * Function:         ��Ϸ������ڵ�
 * Input Parameters: HINSTANCE hInstance: ��ǰʵ���ľ��
 *                   HINSTANCE hPrevInstance: ǰһ��ʵ���ľ��
 *                   LPTSTR lpCmdLine: �����в������ַ���
 *                   int nCmdShow: ���ƴ��ڵ���ʾ״̬
 * Return Value:     �����˳�״̬
 */


int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AppDelegate app;
    return Application::getInstance()->run(); 
}
