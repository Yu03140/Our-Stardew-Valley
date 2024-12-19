#pragma once
#ifndef TASKBARSCENE_H
#define TASKBARSCENE_H

#include "cocos2d.h"
#include "TaskBar.h"
#include "Attribute/attribute.h" 
/**
 * @brief TaskBarScene �����ڹ����������ĳ�����
 * ����̳��� cocos2d::Layer���ṩ��ʾ���������������񽻻��Ĺ��ܡ�
 */
class TaskBarLayer : public cocos2d::Layer {
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
    CREATE_FUNC(TaskBarLayer);

private:
    // �ڴ˴�����κ���Ҫ��˽�г�Ա��������������
};

#endif // TASKBARSCENE_H
