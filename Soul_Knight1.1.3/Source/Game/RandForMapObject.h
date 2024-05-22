#pragma once
#include "../Library/gameutil.h"
#include <numeric>
#include "times.h"
#include "Block.h"
#include "ReadCSV.h"
#include <vector>
#include <cstdlib>
#include <random>
#include "EnumLibrary.h"
namespace game_framework {
	struct ReturnXY {
		int x ;
		int y ;
	};
	
	
	class RandForAll {
	public:
		RandForAll() = default;
		~RandForAll() = default;
		void RandForMap(int dis_map[12][12],bool);
		int GetLenght();
		int RandForMonsterNum();
		void Resetvector();
		int RandForSize();
		vector<int> RandForThreeTalent(int AllTalentSize,vector<int>);
		bool TF_contain_potion();
		ReturnXY RandForMon(vector<vector<Block>>, int);
		ReturnXY RandForChest(vector<vector<Block>>,int);
		vector<vector<int >> RandForObstacle(int);

	private:
		std::random_device rd;
		ReturnXY _position;
		vector<vector<int>> temp;
		vector<int> orange;
		int _lenght;
	};
}