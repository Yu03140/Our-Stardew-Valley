#ifndef __MAIN_H__
#define __MAIN_H__

// 该宏定义排除 Windows 头文件中不常用的部分
#define WIN32_LEAN_AND_MEAN             

#include <windows.h>
#include <tchar.h>  // 通用字符定义
#include "platform/CCStdC.h"

#endif    

#include "AppDelegate/AppDelegate.h"

// 该宏定义排除 Windows 头文件中不常用的部分
#define WIN32_LEAN_AND_MEAN          

USING_NS_CC;

/*
 * Function Name:    _tWinMain
 * Function:         游戏程序入口点
 * Input Parameters: HINSTANCE hInstance: 当前实例的句柄
 *                   HINSTANCE hPrevInstance: 前一个实例的句柄
 *                   LPTSTR lpCmdLine: 命令行参数的字符串
 *                   int nCmdShow: 控制窗口的显示状态
 * Return Value:     程序退出状态
 */


int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AppDelegate app;
    return Application::getInstance()->run(); 
}
