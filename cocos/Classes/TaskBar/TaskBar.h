#ifndef TASKBAR_H
#define TASKBAR_H

#include "cocos2d.h"
#include <string>

/**
 * @brief TaskBar ������ʵ����Ϸ�е���������
 * ������������˵����NPC���֡�����״̬���Լ���������Ļص�����
 */
class TaskBar : public cocos2d::Node {
public:
    /**
     * @brief ��������������
     * @param taskDescription ������������֡�
     * @param npcName ���������NPC���֡�
     * @param completeTaskCallback ����������õĻص�������
     * @return ���� TaskBar ����
     */
    static TaskBar* create(const std::string& taskDescription, const std::string& npcName,
        std::function<void()> completeTaskCallback);

    /**
     * @brief ��ʼ����������
     * @param taskDescription ������������֡�
     * @param npcName ���������NPC���֡�
     * @param completeTaskCallback ����������õĻص�������
     * @return ��ʼ���Ƿ�ɹ���
     */
    virtual bool init(const std::string& taskDescription, const std::string& npcName,
        std::function<void()> completeTaskCallback);

    /**
     * @brief ��ʾ��������
     */
    void show();

    /**
     * @brief ������������
     */
    void hide();

private:
    std::string taskDescription; ///< ������������֡�
    std::string npcName; ///< ���������NPC���֡�
    bool taskCompleted; ///< �����Ƿ���ɵı�־��
    cocos2d::Label* descriptionLabel; ///< ��ʾ���������ı�ǩ��
    cocos2d::MenuItemImage* completeTaskButton; ///< ��������񡱰�ť��
    cocos2d::MenuItemImage* closeButton; ///< ���رա���ť��
    std::function<void()> completeTaskCallback; ///< �������Ļص�������

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
