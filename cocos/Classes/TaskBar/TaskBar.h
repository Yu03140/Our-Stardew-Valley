#ifndef TASKBAR_H
#define TASKBAR_H

#include "cocos2d.h"
#include <string>
#include <queue>
#include <functional>

/**
 * @brief TaskBar ������ʵ����Ϸ�е���������
 * ������������˵����NPC���֡�����״̬���Լ���������Ļص�����
 */
class TaskBar : public cocos2d::Node {
public:
    /**
     * @brief ��������������
     * @return ���� TaskBar ����
     */
    static TaskBar* create();

    /**
     * @brief ��ʼ����������
     * @return ��ʼ���Ƿ�ɹ���
     */
    virtual bool init();

    /**
     * @brief ��ʾ��������
     */
    void show();

    /**
     * @brief ������������
     */
    void hide();

    /**
     * @brief �������������С�
     * @param taskDescription ������������֡�
     * @param completeTaskCallback ����������õĻص�������
     */
    void addTask(const std::string& taskDescription, std::function<void()> completeTaskCallback);

    bool taskCompleted=false; ///< ��ǰ�����Ƿ���ɵı�־��

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

    /**
     * @brief ��ʾ��һ������
     */


    /**
     * @brief ��������񡱰�ť�Ļص�������
     */
    void onCompleteTask();

    /**
     * @brief ���رա���ť�Ļص�������
     */
    void onClose();
};

#endif // TASKBAR_H
