#pragma once
#include <string>
#include <cocos2d.h>

/*
BagManage.h
������
��Ա��
�������ŵĶ��������� string
�������ŵĶ����ĵȼ� int 1/2
vector n�������񣨾���ĵ�ַ��������ʾ��ͼƬ plist
        //�ʼ��Ƭ��ͼ�����ʱ�� �������е�bag_room ��ʼ�����飨����Ϊ�գ�
vector n����Ӧ������
������
������Ʒ��������name�����û�У���������

������ʲô
���ı�����Ķ�����������Ʒ������ ������

��ң�
��Ա��
��ҵ�λ��
���ּ��ܵľ���ֵ����ֲ�����������㡢�ڿ�����
��npc�Ļ����øжȣ���ϵ��������

ʱ�䣺
���ڡ���ǰ��������
�ɺ��ա����գ�
�µ�һ�죺һ���������������

����
*/

extern int TODAY;
struct GOODS_INHAND {
    std::string goods_name;
};

extern struct GOODS_INHAND goods_inhand;
