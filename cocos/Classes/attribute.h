#pragma once
#include <string>      // ���� std::string ����
#include <vector>      // ���� std::vector
#include <iostream>    // �������������
#include <ctime>       // ����ʱ��������������ںͼ��ڹ���
#include "cocos2d.h"  // Cocos2d ��Ҫͷ�ļ����������к�����
#include "2d/CCSprite.h"   // ����ͼ��;�����Ⱦ
#include "ui/UIButton.h"    // ���ڰ�ť�ࣨ�����Ҫ������ť��
#include "base/CCEventListener.h"   // �����¼�����
#include <cmath>           // ������ѧ���㣨���������������ٵȣ�
#include <cstdlib>         // ������������ɣ��������������Ʒ��
#include <algorithm>       // ����һЩ�����㷨���� std::find
#include "ui/CocosGUI.h"// ���� UI ��ť
#include <fstream>// �����ļ���д
#include <windows.h> // ���� Windows ͷ�ļ���ʹ�� MessageBoxW
#include <memory>// ��������ָ��




class PlayerInformation;//��ұ������ԣ���һ�����Ϣ������ ID �ֻ����룩
#define ExperienceOfLevel 100
class PlayerProperty;//��ҲƲ����ԣ�����ֵ�;���ȼ� Ǯ�� ���� ������

class Backpack;// �����࣬���ڹ���������Ʒ

class Item;// ������Ʒ�࣬������Ʒ�Ļ���
class Tool;// �����࣬�̳��� Item �࣬��ʾ�����еĹ���
class Seed;// �����࣬�̳��� Item �࣬��ʾ�����е�����
class Material;// �����࣬�̳��� Item �࣬��ʾ�����еĲ���
class Crop;// ũ�����࣬�̳��� Item �࣬��ʾ�����е�ũ����
class Fertilizer;// �����࣬�̳��� Item �࣬��ʾ�����еķ���
class NPC;// NPC �࣬��ʾ��Ϸ�е� NPC������Farmer��ũ�񣩵�
class NPCtalk;// NPC �Ի��࣬���ڹ��� NPC �Ի�