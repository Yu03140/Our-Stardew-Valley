#ifndef TASKBAR_H
#define TASKBAR_H

#include "cocos2d.h"
#include <string>
#include <queue>
#include <functional>

/**
 * @brief TaskBar 类用于实现游戏中的任务栏。
 * 包含任务文字说明、NPC名字、任务状态，以及完成任务后的回调处理。
 */
class TaskBar : public cocos2d::Node {
public:
    /**
     * @brief 创建任务栏对象。
     * @return 返回 TaskBar 对象。
     */
    static TaskBar* create();

    /**
     * @brief 初始化任务栏。
     * @return 初始化是否成功。
     */
    virtual bool init();

    /**
     * @brief 显示任务栏。
     */
    void show();

    /**
     * @brief 隐藏任务栏。
     */
    void hide();

    /**
     * @brief 添加任务到任务队列。
     * @param taskDescription 任务的描述文字。
     * @param completeTaskCallback 完成任务后调用的回调函数。
     */
    void addTask(const std::string& taskDescription, std::function<void()> completeTaskCallback);

    bool taskCompleted=false; ///< 当前任务是否完成的标志。

    void showNextTask();

private:
    struct Task {
        std::string description; ///< 任务的描述文字。
        std::function<void()> completeCallback; ///< 完成任务的回调函数。
    };

    std::queue<Task> taskQueue; ///< 任务队列。
    Task currentTask; ///< 当前任务。


    cocos2d::Label* descriptionLabel; ///< 显示任务描述的标签。
    cocos2d::MenuItemImage* completeTaskButton; ///< “完成任务”按钮。
    cocos2d::MenuItemImage* closeButton; ///< “关闭”按钮。

    /**
     * @brief 显示下一个任务。
     */


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
