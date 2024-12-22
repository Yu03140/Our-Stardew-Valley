#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>     
#include "cocos2d.h"  

// ��һ�����Ϣ
class PlayerInformation {
public:
    PlayerInformation(const std::string& username, int playerId, const std::string& phoneNumber)
        : username(username), playerId(playerId), phoneNumber(phoneNumber) {}

	std::string getUsername() const { return username; }         // ��ȡ����û���
	int getPlayerId() const { return playerId; }				 // ��ȡ���ID
	std::string getPhoneNumber() const { return phoneNumber; }   // ��ȡ����ֻ���

private:
    std::string username;                                        // ����û���
    int playerId;                                                // ���ID
    std::string phoneNumber;                                     // ����ֻ���
};

// ��ҲƲ�����
class PlayerProperty {
public:
    PlayerProperty(const std::string& playerName)
        : experience(0), money(0), reputation(0) {}

    // ���Ӿ��顢Ǯ�ƺ�����
	void addExperience(int exp);                                 // ���Ӿ���
	void addMoney(int mon);									     // ����Ǯ��
	void addReputation(int reputation_change);				     // �������� 

    // ��ȡ�Ʋ�����
    int getExperience() const { return experience; }
    int getMoney() const { return money; }
    int getReputation() const { return reputation; }

private:
    int experience;                                              // ����ֵ
    int money;                                                   // Ǯ��
    int reputation;                                              // ����
};

// ����ࣺ������ҵĲƲ����Ժ���Ϣ
class Player {
public:
    static Player* getInstance(const std::string& username = "");// ��ȡ Player �ĵ���ʵ�� 
    Player(const Player&) = delete;                              // ɾ���������캯���͸�ֵ��������ȷ��������������
    Player& operator=(const Player&) = delete;                      
    PlayerProperty playerproperty;                               // ��ҲƲ�����

private:
    Player(const std::string& username);                         
    static Player* player;                                       // Ψһ�� Player ʵ��

};

#endif // __PLAYER_H__
