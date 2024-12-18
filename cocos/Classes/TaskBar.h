#ifndef TASKBAR_H
#define TASKBAR_H

#include "cocos2d.h"
#include <string>

/**
 * @brief TaskBar 类用于实现游戏中的任务栏。
 * 包含任务文字说明、NPC名字、任务状态，以及完成任务后的回调处理。
 */
class TaskBar : public cocos2d::Node {
public:
    /**
     * @brief 创建任务栏对象。
     * @param taskDescription 任务的描述文字。
     * @param npcName 发布任务的NPC名字。
     * @param completeTaskCallback 完成任务后调用的回调函数。
     * @return 返回 TaskBar 对象。
     */
    static TaskBar* create(const std::string& taskDescription, const std::string& npcName,
        std::function<void()> completeTaskCallback);

    /**
     * @brief 初始化任务栏。
     * @param taskDescription 任务的描述文字。
     * @param npcName 发布任务的NPC名字。
     * @param completeTaskCallback 完成任务后调用的回调函数。
     * @return 初始化是否成功。
     */
    virtual bool init(const std::string& taskDescription, const std::string& npcName,
        std::function<void()> completeTaskCallback);

    /**
     * @brief 显示任务栏。
     */
    void show();

    /**
     * @brief 隐藏任务栏。
     */
    void hide();

private:
    std::string taskDescription; ///< 任务的描述文字。
    std::string npcName; ///< 发布任务的NPC名字。
    bool taskCompleted; ///< 任务是否完成的标志。
    cocos2d::Label* descriptionLabel; ///< 显示任务描述的标签。
    cocos2d::MenuItemImage* completeTaskButton; ///< “完成任务”按钮。
    cocos2d::MenuItemImage* closeButton; ///< “关闭”按钮。
    std::function<void()> completeTaskCallback; ///< 完成任务的回调函数。

    /**
     * @brief “完成任务”按钮的回调函数。
     */
    void onCompleteTask();

    /**
     * @brief “关闭”按钮的回调函数。
     */
    void onClose();
};

#endif // TASKBAR_H
