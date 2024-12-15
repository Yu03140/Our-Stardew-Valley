#pragma once
#ifndef TASKBARSCENE_H
#define TASKBARSCENE_H

#include "cocos2d.h"
#include "TaskBar.h"

/**
 * @brief TaskBarScene �����ڹ����������ĳ�����
 * ����̳��� cocos2d::Layer���ṩ��ʾ���������������񽻻��Ĺ��ܡ�
 */
class TaskBarScene : public cocos2d::Layer {
public:
    /**
     * @brief ����������������������
     * @return һ�������������� cocos2d::Scene ����
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief ��ʼ��������������
     * @return ��ʼ���Ƿ�ɹ���
     */
    virtual bool init();

    /**
     * @brief ���� CREATE_FUNC �꣬���ڼ򻯴�������Ĵ��롣
     * CREATE_FUNC ���Զ����ɾ�̬ create() ������
     */
    CREATE_FUNC(TaskBarScene);

private:
    // �ڴ˴�����κ���Ҫ��˽�г�Ա��������������
};

#endif // TASKBARSCENE_H
