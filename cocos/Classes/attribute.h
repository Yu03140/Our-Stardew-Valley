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


class PlayerPosition {//�����ʼ��Ӧ��Ϊ�м� ������һ�£�����������������������������
    int player_x = 1050;
    int player_y = 1050;
};




//��ұ������ԣ���һ�����Ϣ������ ID �ֻ����룩
class PlayerInformation {
public:
    // ���캯�������ڳ�ʼ���������
    PlayerInformation(const std::string& username, int playerId, const std::string& phoneNumber)
        : username(username), playerId(playerId), phoneNumber(phoneNumber) {
        std::cout << "Player created: " << username << ", ID: " << playerId << ", Phone: " << phoneNumber << std::endl;
    }





    // ��ȡ����û���
    std::string getUsername() const { return username; }

    // ��ȡ���ID
    int getPlayerId() const { return playerId; }

    // ��ȡ����ֻ���
    std::string getPhoneNumber() const { return phoneNumber; }

private:
    std::string username;  // ����û���
    int playerId;          // ���ID
    std::string phoneNumber; // ���ע���ֻ���
};







//��ҲƲ����ԣ�����ֵ�;���ȼ� Ǯ�� ���� ������
class PlayerProperty {

private:
    int experience;          // ����ֵ
    int level = experience / 100;              // ����ȼ�
    int money;               // Ǯ��
    int reputation;          // ����
    class Backpack;  // ������Ʒ

public:
    // ���캯��
    PlayerProperty(std::string name) : experience(0), money(0), reputation(0) {}

    // ���Ӿ���
    void addExperience(int exp);
    // ����Ǯ��
    void addMoney(int mon);
    void addReputation(int reputation_change);
    //��ȡ������Բ����  (����ĳ����)
    void displayPlayerInfo() const;

};


class Player {
public:
    PlayerPosition playerposition;
    PlayerInformation playerinformation;  // �����Ϣ
    PlayerProperty playerproperty;        // ��ҲƲ�����

};
