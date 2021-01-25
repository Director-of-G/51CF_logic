//#2021-1-19 <JYP> 熟悉代码，添加注释
#include "game.h"
#include "player_code.h"
#include "../controller/Controller.h"
#include <time.h>

using namespace DAGAN;
void outputResult(Game& game, vector<Player_Code>& players) {
	ofstream ofs("../log_txt/result.txt");

	vector<TPlayerID> rank = game.getRank();   //游戏结果排名(vector)
	for (size_t i = 0; i < rank.size(); ++i) {
		ofs << players[rank[i]].getName() << endl;   //按排名输出每个名次的玩家name
	}
}

int main(int argc, char** argv)
{
	char buffer[1024];
	time_t t = time(0);
	strftime(buffer, sizeof(buffer), "../log_txt/log_%Y%m%d_%H%M%S.txt", localtime(&t));
#ifdef FC15_DEBUG
	freopen(buffer, "w", stdout);
#endif // FC15_DEBUG
	char json_filename[1024];
	strftime(json_filename, sizeof(json_filename), "../log_json/log_%Y%m%d_%H%M%S.json", localtime(&t));
	string  config_filename =
#ifdef _MSC_VER
		"../config_msvc.ini";
#endif
#ifdef __GNUC__
	"../config_gnu.ini";
#endif

	if (argc == 2) {
		config_filename = argv[1];
	}
	else if (argc >= 2) {
		cout << "usage:												" << endl
			<< "DAGAN						Load config file	" << endl;
	}


	vector<Player_Code>  players;
	string          map_filename;
	vector<string>  players_filename;
	int player_size;

	// load config file
	ifstream ifs(config_filename.c_str());
	if (!ifs.is_open()) {
		cout << "Failed to load \"" << config_filename << "\". Aborted. " << endl;
		return 1;
	}

	// read config file
	//配置文件
	//第一行：地图文件路径
	//第二行：玩家数量
	//第三行：每个玩家的ai路径
	ifs >> map_filename >> player_size;
	int cnt = 0;
	while (!ifs.eof() && cnt < player_size) {
		string player_filename;
		ifs >> player_filename;
		if (!player_filename.empty()) players_filename.push_back(player_filename);
		cnt++;
	}
	if (players_filename.size() == 0) {
		cout << "[Error] player_ai file names expected." << endl;
		return 2;
	}
	else if (players_filename.size() != player_size)
	{
		cout << "[Error]" << player_size << " player_ai file required." << endl;
		return 3;
	}
	// load map
	//初始化地图、玩家的势力区域、防御塔、兵团的作战关系表等等
	//添加注释1
	//添加注释2
	//添加注释3
	//添加注释4
	//添加注释5
	//添加注释666
	//添加注释8 int comment = 10; //添加注释7
	Game G;
	if (!G.init(map_filename, json_filename)) {
		cout << "[Error] failed to load " << map_filename << endl;
		return 4;
	}

	// load players
	//读入玩家AI代码，应该也不需要修改
	int valid_cnt = 0; //有效ai的数量
	for (size_t i = 0; i < players_filename.size(); ++i) {
		Player_Code player(players_filename[i], i);
		string player_name;
		if (ifs >> player_name && !player_name.empty())
			player.setName(player_name);
		if (player.isValid())
		{
			players.push_back(player);
			valid_cnt++;
		}
		else {
			players.push_back(player); //压进去充数
			cout << "[Warning] failed to load player_ai " << players_filename[i] << endl;
			player.setName(player.getName() + "//NOT_VALID");
#if (defined _MSC_VER && defined _DEBUG)
			system("pause");
#endif
		}
	}
	if (players.size() <= 1) {
		cout << "[Error] Not enough player_ais to start the game." << endl;
		return 5;
	}
	cout << "[Info] " << valid_cnt << " players loaded." << endl;

	// game and controller

	Controller controller(G, players);

	for (int i = 0; i < players.size(); i++)
	{
		controller.getData()->root["head"]["playerInfo"][i]["name"] = players[i].getName();
	}
	// main
	//一个回合一个回合的跑
	while (controller.isValid())
	{
		controller.run(json_filename);
	}


	// output the result
	//add comments 1
	//add comments 2
	//add comments 3
	//add comments 4
	//add comments 5
	//add comments 6
	int zhushi = 27;  //add comments 7
	int zhushier = 32; //add comments 8
	outputResult(G, players);

	return 0;

}
