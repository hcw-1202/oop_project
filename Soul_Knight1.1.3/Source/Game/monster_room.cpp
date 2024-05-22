#include "stdafx.h"
#include "../Library/gameutil.h"
#include "monster_room.h"

namespace game_framework {
	MonsterRoom::MonsterRoom(int roomsize, Hero *hero,int quantity,int speed,int power) :Room(roomsize,hero){

		_type = MONSTER_Room;
		_trigger = true;
		_trigger2 = true;
		TF_avoid_trap = false;
		_monster_quantity =quantity;
		pass.LoadBitmapByString({ "resources/devastmonster.bmp" }, RGB(255, 255, 255));
		
		_obstacle_type = _randforall.RandForObstacle(roomsize);
		
		for (int x = 0; x < roomsize; x++) {
			for (int y = 0; y < roomsize; y++) {
				
				if (x > 0 && x < roomsize - 1 && y>0 && y < roomsize - 1) {
					if (_obstacle_type[x - 1][y - 1] == TRAP) {
						Creat_map_floor[x][y].blocktype(_obstacle_type[x - 1][y - 1]);

					}
					else
						Creat_map[x][y].blocktype(_obstacle_type[x - 1][y - 1]);
					
					
				}
				
			}
		}
		_chest = _randforall.RandForChest(Creat_map, _size);
		for (int i = 0; i <quantity; i++) {
			int num = rand() % (2 - 1 + 1) + 1;
			//int num = 1;
			//printf("num = %d\n",num);

			monster.push_back(new Monster());
			monster[i]->set_left_pic(num);
			monster[i]->set_right_pic(num);
			monster[i]->set_blood(20);
			if (monster[i]->Get_type() == 1) {

				monster[i]->set_speed(speed);
				monster[i]->set_power(power);
			}
			else if (monster[i]->Get_type() == 2) {
				monster[i]->set_power(power);
			}
		}

	}
	MonsterRoom::~MonsterRoom() {

		for (int i = monster.size() - 1; i >= 0; i--) {

			delete monster[i];
		}
		monster.clear();
	}
	bool MonsterRoom::TF_interaction() {
		
		
		
		
		if (_trigger && TF_inner_room()) {
			
			Creat_map[_chest.x][_chest.y].ContainPotion(_randforall.TF_contain_potion(), RECOVERY);
			Creat_map[_chest.x][_chest.y].AppearDrop(false);
			_trigger = false;
		}
		
		if (this->take_is_fight_end()) {
			printf("end\n");
			Creat_map[_chest.x][_chest.y].AppearDrop(true);
			
			if(Creat_map[_chest.x][_chest.y].Gettype()==CHEST_OPEN && Creat_map[_chest.x][_chest.y].TF_ContainPosition())
				Creat_map[_chest.x][_chest.y].GetDrop(_hero,Hero_talent.Increase_potion_healing());
			
			
			if (Creat_map[_chest.x][_chest.y].get_block().IsOverlap(Creat_map[_chest.x][_chest.y].get_block(), _hero->get_deter_area())&& Creat_map[_chest.x][_chest.y].Gettype()==CHEST_CLOSE) {
				sounds.play_what(12,false);
				Creat_map[_chest.x][_chest.y].blocktype(CHEST_OPEN);
				
				return false;
			}
			
			
		}
		return false;
	}
	
	void MonsterRoom::Keep_detect_interact() {
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				Creat_map_floor[x][y].show();
				if (TF_entry()) {

					Creat_map_floor[x][y].starttrap(_hero,Hero_talent.Avoid_TrapDamage());
				}

				if (Creat_map[x][y].Gettype() == CHEST_CLOSE || Creat_map[x][y].Gettype() == CHEST_OPEN)
					Creat_map[x][y].show();

			}
		}
	}
	
	void MonsterRoom::Gate(blocktype gate_condition) {
		gate_condition = GATE_CLOSE;
		if (this->take_is_fight_end()) {
			gate_condition = GATE_OPEN;
		}
		if (gate_condition == GATE_CLOSE) {
			for (int i = 0; i < _gate.size(); i++) {
				if (_gate[i] == TOP) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[0][i].blocktype(gate_condition);

					}
				}
				if (_gate[i] == RIGHT) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[i][_size - 1].blocktype(gate_condition);
					}
				}
				if (_gate[i] == DOWN) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[_size - 1][i].blocktype(gate_condition);
					}
				}
				if (_gate[i] == LEFT) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[i][0].blocktype(gate_condition);
					}
				}

			}
		}
		else {
			for (int i = 0; i < _gate.size(); i++) {
				if (_gate[i] == TOP) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[0][i].blocktype(OTHER);

					}
				}
				if (_gate[i] == RIGHT) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[i][_size - 1].blocktype(OTHER);
					}
				}
				if (_gate[i] == DOWN) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[_size - 1][i].blocktype(OTHER);
					}
				}
				if (_gate[i] == LEFT) {
					for (int i = gateleft + 1; i < gateright; i++) {
						Creat_map[i][0].blocktype(OTHER);
					}
				}

			}
		}
			
			
		
	}
	
	void MonsterRoom::show() {

		
		
		for (int place = 0; place < _gate.size(); place++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {

					route_floor[place][i][j].show();

				}
			}
		}
		
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				Creat_map_floor[x][y].show();
				
					
				if (Creat_map[x][y].Gettype() == CHEST_CLOSE || Creat_map[x][y].Gettype() == CHEST_OPEN)
					Creat_map[x][y].show();

			}
		}

		
		
			
		for (int i = 0; i < _monster_quantity; i++) {
			monster[i]->is_alive();
			monster[i]->show();
			if (monster[i]->is_alive() &&  this->TF_inner_room()) {
				if(monster[i]->Get_type() == 2){
					monster[i]->show_notice()->SetTopLeft(monster[i]->GetLeft() - 10, monster[i]->GetTop() - 10);
					monster[i]->show_notice()->ShowBitmap();
				}
				if(monster[i]->Get_type() == 1){
					if (monster[i]->detect_range(_hero->get_left_pic())) {
						monster[i]->show_notice()->SetTopLeft(monster[i]->GetLeft() - 10, monster[i]->GetTop() - 10);
						monster[i]->show_notice()->ShowBitmap();
					}
				}
			}
		}
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
				if (Creat_map[x][y].Gettype() != CHEST_CLOSE && Creat_map[x][y].Gettype() != CHEST_OPEN)
					Creat_map[x][y].show();
			}
		}
		
		if (this->take_is_fight_end()) {
			pass.SetTopLeft(Creat_map[0][0].GetLeft() + (_width - pass.GetWidth()) / 2, Creat_map[0][0].GetTop() + (_height - pass.GetHeight() )/2);
			if (Creat_map[_chest.x][_chest.y].Gettype() != CHEST_OPEN && _trigger2) {
				Creat_map[_chest.x][_chest.y].blocktype(CHEST_CLOSE);
				Creat_map[_chest.x][_chest.y].block_position(Creat_map[_chest.x][_chest.y].GetLeft(), Creat_map[_chest.x][_chest.y].GetTop() + 20);
				_trigger2 = false;
			}
			if ((clock() - t) / (double)(CLOCKS_PER_SEC) <= 2)
				pass.ShowBitmap();
				

		}
		else {
			t = clock();
		}
		if (TF_inner_room() || TF_in_route()) {
			Hero_talent.show_hero_talent();
		}
		
	};
	Monster* MonsterRoom::get_which_mon(int x) {
		return monster[x];
	}
	int MonsterRoom::get_small_dis(Hero Hero) {
		int small_mon = 10000;
		int num = 10000;
		for (int i = 0; i < _monster_quantity; i++) {
			this->get_which_mon(i)->set_range(Hero);
			if (this->get_which_mon(i)->take_dis() < num && this->get_which_mon(i)->is_alive()) {
				num = this->get_which_mon(i)->take_dis();
				small_mon = i;
			}
		}
		return small_mon;
	}
	bool MonsterRoom::take_is_fight_end() {
		for (int i = 0; i < monster.size(); i++) {
			if (monster[i]->is_alive()) return false;
		}
		
		return true;
	}
	void MonsterRoom::set_Monster_place() {
		_randforall.Resetvector();
		for (int i = 0; i < _monster_quantity; i++) {
			_Monst=_randforall.RandForMon(Creat_map, _size);
			int pos_x = _Monst.x;
			int pos_y = _Monst.y;

			monster[i]->set_pos(Creat_map_floor[pos_x][pos_y].GetLeft()+(Creat_map_floor[pos_x][pos_y].GetWidth()-monster[i]->GetWidth())/2, Creat_map_floor[pos_x][pos_y].GetTop() + (Creat_map_floor[pos_x][pos_y].GetHeight() - monster[i]->GetHeight()) / 2);


			
			
		}

	}
	int MonsterRoom::get_Monster_num() {
		return _monster_quantity;
	}
	void MonsterRoom::kill_all_mon() {
		for (int i = 0; i < monster.size(); i++) {
			monster[i]->kill();
		}
	}
};