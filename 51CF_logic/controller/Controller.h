//#2021-1-19 <JYP> 熟悉代码，添加注释
#include "../logic/game.h"
#include "../logic/player_code.h"
#include <vector>
#include <string>
#include <fstream>
#include "../json/json.h"

namespace DAGAN
{
	class Controller
	{
	public:
		Controller(Game& g, std::vector<Player_Code>& p)
			: game_(g)
			, data(&(g.getData()))
			, silent_mode_(
#ifdef NO_SILENT_MODE
				false
#else
				true
#endif
			), file_output_enabled_(true)
			, isValid_(true), debug_mode(
#ifdef FC15_DEBUG
		true
#else
		false
#endif
			)
			, players_(p){ }

		void run(char* json_filename);

		inline void setSilentMode(bool flag) { silent_mode_ = flag; }
		inline void setFileOutputEnabled(bool flag) { file_output_enabled_ = flag; }
		inline bool isValid() const { return isValid_; }
		inline DATA::Data* getData() { return data; }

	protected:
		bool debug_mode;
		Game& game_;
		DATA::Data *data;
		std::ofstream ofs;
		std::vector<Player_Code>& players_;
		bool file_output_enabled_;
		bool silent_mode_; //silent_mode_为true会输出回合数信息和每个玩家的操作信息
		bool isValid_;
	};
}
