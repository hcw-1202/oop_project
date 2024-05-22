#include "stdafx.h"
#include "Spawn_room.h"
namespace game_framework {
	SpawnRoom::SpawnRoom(int size, Hero *hero,int Level) :Room(size, hero) {
		_type = SPAWN_Room;
		_Level = Level;
		Hero_talent.Init_Talent();
		
	}

	SpawnRoom::~SpawnRoom() {

	}
	void SpawnRoom::Set_position(int x, int y) {
		_left = x;
		_top = y;
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				Creat_map[x][y].block_position(_left + (y - _size / 2) * Creat_map_floor[x][y].GetWidth(), _top + (x - _size / 2) * Creat_map_floor[x][y].GetHeight());
				Creat_map_floor[x][y].block_position(_left + (y - _size / 2) * Creat_map_floor[x][y].GetWidth(), _top + (x - _size / 2) * Creat_map_floor[x][y].GetHeight()+20);
				
			}
		}
		Hero_talent.Set_Skill_block(Creat_map_floor[3][3].GetLeft()+ (Creat_map_floor[3][3].GetWidth()-40)/2, Creat_map_floor[3][3].GetTop() + (Creat_map_floor[3][3].GetHeight()-40 ) / 2, _Level);
	}
	void SpawnRoom::Gate(blocktype gate_condition) {

	}
	bool SpawnRoom::TF_interaction() {
		
		Hero_talent.Select_Skill(_hero);
		return false;
		
	}
	void SpawnRoom::show() {
		for (int place = 0; place < _gate.size(); place++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {
					route_floor[place][i][j].show();
				}
			}
		};
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				Creat_map_floor[x][y].show();
				
			}
		}
		Hero_talent.show_skill(_hero);
		if (TF_inner_room() || TF_in_route())
			_hero->show();
		for (int place = 0; place < _gate.size(); place++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {
					route[place][i][j].show();
				}
			}
		}
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {

				Creat_map[x][y].show();
			}
		}
		if (TF_inner_room() || TF_in_route()) {
			Hero_talent.show_hero_talent();
		}
	}
}