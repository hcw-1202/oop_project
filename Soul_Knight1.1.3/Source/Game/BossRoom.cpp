
#include "stdafx.h"
#include "BossRoom.h"
namespace game_framework {
	BossRoom::BossRoom(int size, Hero *hero, int power, int blood, int type) :Room(size, hero) {
		_type = BOSS_Room;
		
		final_boss = new Boss();
		final_boss->set_left_pic(type);
		final_boss->set_right_pic(type);

		final_boss->set_blood(blood);

		final_boss->set_init();
		if (type == 100) final_boss->set_power(power);
		else if (type == 200) final_boss->set_speed(power);
		_obstacle_type = rand.RandForObstacle(size);
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {

				if (x > 0 && x < size - 1 && y>0 && y < size - 1) {
					if (_obstacle_type[x - 1][y - 1] == TRAP) {
						Creat_map_floor[x][y].blocktype(_obstacle_type[x - 1][y - 1]);
					}
					else
						Creat_map[x][y].blocktype(_obstacle_type[x - 1][y - 1]);


				}

			}
		}
		_teleportX = _size /2-1;
		_teleportY = _size /2-1;
		printf("testX=%d",_teleportX);
		printf("testY=%d", _teleportY);
		is_delete = false;
		count = 0;
	};
	BossRoom::~BossRoom() {
		if(!is_delete)
			delete final_boss;
	}
	bool BossRoom::TF_interaction() {

		if (Creat_map[_teleportX][_teleportY].get_block().IsOverlap(Creat_map[_teleportX][_teleportY].get_block(), _hero->get_deter_area()) && !final_boss->is_alive()) {
			printf("teleport!\n");
			return true;
		}
		return false;
	}
	void BossRoom::Gate(blocktype gate_condition) {
		gate_condition = GATE_CLOSE;
		if (this->take_is_fight_end()) {
			Creat_map[_teleportX][_teleportY].blocktype(TELEPORT);
			gate_condition = GATE_OPEN;
		}
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

	bool BossRoom::take_is_fight_end() {
		if (!final_boss->is_alive()) return true;
		return false;
	}

	Boss* BossRoom::take_boss() {
		return final_boss;
	}

	void BossRoom::show() {

		//printf("yeahhhh\n");

		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				if (TF_entry())
					Creat_map_floor[x][y].starttrap(_hero,Hero_talent.Avoid_TrapDamage());
				Creat_map_floor[x][y].show();


			}
		}
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {

				Creat_map[x][y].show();

			}
		}

		for (int place = 0; place < _gate.size(); place++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {

					route_floor[place][i][j].show();

				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {

					route[place][i][j].show();
				}
			}

		}
		if(!is_delete && this->TF_inner_room()) final_boss->show_boss();
		_hero->show();
	};

	void BossRoom::rand_boss_pos(Hero hero) {
		if (count == 1) {
			final_boss->set_pos(hero.GetLeft() + 50, hero.GetTop() - 50);
		}
		else {
			pos = rand.RandForMon(this->Creat_map, _size);
			final_boss->set_pos(Creat_map[pos.x][pos.y].GetLeft(), Creat_map[pos.x][pos.y].GetTop() + 20);
		}
		printf("count = %d\n", count);
		count += 1;
		if (count == 2) count = 0;
	}

	void BossRoom::delete_boss() {
		delete final_boss;
		is_delete = true;
	}
	bool BossRoom::get_boss_delete() {
		return is_delete;
	}

}