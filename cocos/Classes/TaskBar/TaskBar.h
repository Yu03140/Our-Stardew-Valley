#ifndef TASKBAR_H
#define TASKBAR_H

#include "cocos2d.h"
#include <string>
#include <queue>
#include <functional>

class TaskBar : public cocos2d::Node {
public:
   
    static TaskBar* create();
    virtual bool init();
    void show();
    void hide();
    void addTask(const std::string& taskDescription, std::function<void()> completeTaskCallback);
    bool taskCompleted = false; ///< ��ǰ�����Ƿ���ɵı�־��

    void showNextTask();

private:
    struct Task {
        std::string description; ///< ������������֡�
        std::function<void()> completeCallback; ///< �������Ļص�������
    };

    std::queue<Task> taskQueue; ///< ������С�
    Task currentTask; ///< ��ǰ����


    cocos2d::Label* descriptionLabel; ///< ��ʾ���������ı�ǩ��
    cocos2d::MenuItemImage* completeTaskButton; ///< ��������񡱰�ť��
    cocos2d::MenuItemImage* closeButton; ///< ���رա���ť��
    void onCompleteTask();
    void onClose();
};

#endif // TASKBAR_H