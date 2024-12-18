#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"

#include <string>      // ���� std::string ����
// ��һ�����Ϣ�����û�����ID���ֻ��ŵȣ�
class PlayerInformation {
public:
    PlayerInformation(const std::string& username, int playerId, const std::string& phoneNumber)
        : username(username), playerId(playerId), phoneNumber(phoneNumber) {}

    // ��ȡ�����Ϣ
    std::string getUsername() const { return username; }
    int getPlayerId() const { return playerId; }
    std::string getPhoneNumber() const { return phoneNumber; }

private:
    std::string username;    // ����û���
    int playerId;            // ���ID
    std::string phoneNumber; // ����ֻ���
};

// ��ҲƲ����ԣ����顢Ǯ�ơ������ȣ�
class PlayerProperty {
public:
    // ���캯��
    PlayerProperty(const std::string& playerName)
        : experience(0), money(0), reputation(0) {}

    // ���Ӿ��顢Ǯ�ƺ�����
    void addExperience(int exp);
    void addMoney(int mon);
    void addReputation(int reputation_change);

    // ��ȡ�Ʋ�����
    int getExperience() const { return experience; }
    int getMoney() const { return money; }
    int getReputation() const { return reputation; }

private:
    int experience;   // ����ֵ
    int money;        // Ǯ��
    int reputation;   // ����
};

// ����ࣺ������ҵĲƲ����Ժ���Ϣ
class Player {
public:
    // ��ȡ Player �ĵ���ʵ��
    static Player* getInstance(const std::string& username = "");

    // ɾ���������캯���͸�ֵ��������ȷ��������������
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    // ��ҲƲ�����
    PlayerProperty playerproperty;

private:
    // ˽�й��캯������ֹ�ⲿֱ�Ӵ���ʵ��
    Player(const std::string& username);

    // ��̬��Ա���������ڱ���Ψһ�� Player ʵ��
    static Player* player;

};

#endif // __PLAYER_H__
