//Git bashed file
#ifndef GAME_H
#define GAME_H

#include "definition.h"
#include "data.h"
#include "player.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using std::vector;
using std::string;
using std::size_t;
using std::cout;
using std::cin;
using std::endl;

class Game
{
public:
	Game() {}
	vector<time_t> roundTime; //#json
	bool init(string filename, char* json_filename);//��ʼ����Ϣ
	DATA::Data& getData() { return data; } //#json
	vector<TPlayerID> getRank() { return Rank; }
	int getPlayerSize() { return data.PlayerNum; }
	TRound getRound() { return currentRound; }
	void DebugPhase();
	vector<Info> generateInfo();
	bool isValid();//�ж��Ƿ����
	void regeneratePhase();    //�ָ��׶�
	void movePhase();          //�����ƶ�
	void transPhase();         //����/�����׶�
	void beginPhase();      //��С���ֻغ���
	void endPhase();  //ɾ�����ô���
	void commandPhase(vector<CommandList>& command_list); //�������ָ��
	void killPlayer(TPlayerID id); //ɱ����� 
	bool isAlive(TPlayerID id) { return data.players[id].isAlive(); }
	void saveJson(DATA::Data & dataLastRound, DataSupplement & dataSuppleMent);
	void addRound() { currentRound++; }
protected:
	void takeEffect(TransEffect& te); //��teʩ�õ�Ŀ����
	void handleExtending(TransEffect& t);
	std::ofstream LogFile;
	DATA::Data data;      //���е����ݴ�Ŵ�
	TRound currentRound;  //��ǰ�غ���
	size_t playerSize;    //��Ϸ��ģ
	size_t playerAlive;   //�������
	vector<TPlayerID> Rank;//��������Դ������
	TResourceI _MAX_RESOURCE_;//ÿ���ض��������Դ
	TRound _MAX_ROUND_;
	vector<int> controlCount; //��¼������
	void OwnerChange(TransEffect** TE);
};

#endif // !GAME_H