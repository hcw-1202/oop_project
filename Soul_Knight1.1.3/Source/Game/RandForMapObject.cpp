
#include "stdafx.h"
#include "RandForMapObject.h"

namespace game_framework{
	
	void RandForAll::RandForMap(int dis_map[12][12],bool boss) {
		//srand(time(NULL));
		std::default_random_engine gen = std::default_random_engine(rd());
		
		// 初始化地圖
		orange.clear();
		orange.push_back(SPAWN_Room);
		int max = 5;
		int min = 3;
		std::uniform_int_distribution<int> dis(3, 5);
		
		int _volumn = dis(gen);
		int tmp_count = 1;
		for (int count = 0; count < _volumn; count++) {
			orange.push_back(MONSTER_Room);
			if (count == _volumn - 2) {
				orange.push_back(BONUS_Room);
			}
		}
		printf("bossnum=%d\n", boss);
		if (boss) {
			orange.push_back(BOSS_Room);
		}
		else {
			orange.push_back(TELEPORT_Room);
		}
		
		printf("value=");
		for (int i = 0; i < orange.size(); i++)
			printf("%d,", orange[i]);
		// up right down
		printf("\n");
		max = 2;
		min = 0;
		
		int now_x = 1;
		int now_y = 1;
		dis_map[now_y][now_x] = 1;
		int rd = 0;
		//權重max=100 min=0
		vector <int> Weights{50,50,50};//up right down
		for (int count = 1; count < orange.size(); count++) {
			Weights[0] = 50;
			Weights[1] = 50;
			Weights[2] = 50;
			
			

			if (dis_map[now_y][now_x + 1] != 0 || now_x + 1 == 12)
				Weights[0] = 0;
			if (dis_map[now_y + 1][now_x] != 0 || now_y + 1 == 12)
				Weights[1] = 0;
			if (dis_map[now_y - 1][now_x] != 0 || now_y - 1 == 0) {
				Weights[2] = 0;
			}
				
			std::uniform_int_distribution<int> map(1, Weights[0] + Weights[1] + Weights[2]);
			rd = ( map(gen));
			
			//printf("test=%d\n", rd);
			
			if (rd <= Weights[0]) {
				printf("right\n");
				now_x++;
			}
			else if (Weights[0] < rd && rd <= Weights[0]+Weights[1]) {
				printf("down\n");
				now_y++;
			}
			else if (Weights[0] + Weights[1] < rd && rd <= Weights[0] + Weights[1] + Weights[2]) {
				printf("up\n");
				now_y--;
			}
			else {
				
			}
			
			dis_map[now_y][now_x] = orange[count];
		}
		
	}
	bool RandForAll::TF_contain_potion() {
		std::default_random_engine gen = std::default_random_engine(rd());
		
		int max = 100;
		int min = 1;
		std::uniform_int_distribution<int> potion(min, max);
		int value = potion(gen);
		
		if (value < 50) {//10/100
			
			return true;
		}
		return false;
	}
	int RandForAll::GetLenght() {
		return orange.size();
	}
	ReturnXY RandForAll::RandForChest(vector<vector<Block>> room_object,int _size) {
		std::default_random_engine gen = std::default_random_engine(rd());
		
		int max = _size-3;
		int min = 2;
		std::uniform_int_distribution<int> place(min, max);
		int broke = 0;
		while (1) {

			int place_x = place(gen);
			int place_y = place(gen);
			if (!room_object[place_x][place_y].is_obstacle() && room_object[place_x][place_y].Gettype()!=TRAP) {
				_position.x = place_x;
				_position.y = place_y;
				return _position;
			}
				
			broke++;
			if (broke == 1000) {
				printf("!\n");
				_position.x = 3;
				_position.y = 3;
				return _position;
			}
				
		}
		
		
	}
	int RandForAll::RandForSize() {
		int temp=0;
		int max = 2;
		int min = 1;
		
		std::default_random_engine gen = std::default_random_engine(rd());
		std::uniform_int_distribution<int> sz(min, max);
		temp = sz(gen);
		if (temp == 1)
			return MEDIUM;
		else if (temp == 2)
			return BIG;
		
		
		
	}

	ReturnXY RandForAll::RandForMon(vector<vector<Block>> room_object, int _size) {
		
		for (int i = 0; i < room_object.size();i++) {
			vector<int> row;
			for (int j = 0; j < room_object[i].size(); j++) {
				row.push_back(room_object[i][j].is_obstacle());
			}
			temp.push_back(row);
		}
		//printf("test\n");
		//for (int i = 0; i < room_object.size(); i++) {
		//	
		//	for (int j = 0; j < room_object[i].size(); j++) {
		//		printf("%d, ", temp[i][j]);
		//	}
		//	printf("\n");
		//}
		
		int max = _size - 2;
		int min = 1;
		int broke = 0;
		std::default_random_engine gen = std::default_random_engine(rd());
		std::uniform_int_distribution<int> mon(min, max);
		while (1) {
			int place_x = mon(gen);
			int place_y = mon(gen);
			if (!room_object[place_x][place_y].is_obstacle() && temp[place_x][place_y]!=-1) {
				_position.x = place_x;
				_position.y = place_y;
				temp[place_x][place_y] = -1;
				
				return _position;
			}

			broke++;
			if (broke == 100000) {
				printf("!\n");
				_position.x = 3;
				_position.y = 3;
				return _position;
			}

		}


	}
	int RandForAll::RandForMonsterNum() {
		int max = 7;
		int min = 5;
		int broke = 0;
		std::default_random_engine gen = std::default_random_engine(rd());
		std::uniform_int_distribution<int> monnum(min, max);
		return monnum(gen);
	};
	vector<vector<int >> RandForAll::RandForObstacle(int _size) {
		std::default_random_engine gen = std::default_random_engine(rd());
		
		string obstacle_type[6]{
			"Source/MEDIUM1.csv",
			"Source/MEDIUM2.csv",
			"Source/MEDIUM3.csv",
			"Source/MEDIUM4.csv",
			"Source/Big1.csv",
			"Source/Big2.csv"
		};
		int temp = 0;
		int max = 3;
		int min = 0;
		
		if (_size == MEDIUM) {
			min = 0;
			max = 3;
			std::uniform_int_distribution<int> obs(min, max);
			temp = obs(gen);
		}
		else if(_size==BIG) {
			min = 4;
			max = 5;
			std::uniform_int_distribution<int> obs(min, max);
			temp = obs(gen);
		}
		ReadCSV _readcsv(obstacle_type[temp]);
		vector<vector<int>> orange = _readcsv.GetData();
		for (int i = 0; i < orange.size(); i++) {
			for (int j = 0; j < orange[0].size(); j++) {
				printf("%d, ", orange[i][j]);
			}
			printf("\n");
		}
		return orange;
	}
	void RandForAll::Resetvector() {
		for (int i = 0; i < temp.size(); i++) {
			temp[i].clear();
		}
		temp.clear();
		printf("OAO=%d\n", temp.empty());
	}
	vector<int> RandForAll::RandForThreeTalent(int AllTalentSize, vector<int> HeroChooseTalent) {
		vector<int> temp;
		int max = AllTalentSize-1;
		int min = 0;
		int temp3 = 0;
		std::default_random_engine gen = std::default_random_engine(rd());
		std::uniform_int_distribution<int> wh(min, max);
		int i = 0;
		while(1) {
			
			temp3 = wh(gen);
			vector<int> ::iterator temp2 = std::find(temp.begin(), temp.end(),temp3);
			if (temp2 != temp.end()) {
				vector<int> ::iterator temp4 = std::find(HeroChooseTalent.begin(), HeroChooseTalent.end(), temp3);
				if (temp4 != HeroChooseTalent.end()) {
					temp3 = wh(gen);
					temp[temp.size() - 1] = temp3;
				}
				
			}
			else {
				temp.push_back(temp3);
				i++;
			}
			if (i == 3) {
				return temp;
			}
		}
			
			
		
		return temp;
	}
}