#include "stdafx.h"
#include "Distribute_room.h"
#include <numeric>
namespace game_framework {
	DistributeMap::DistributeMap() {
		In_which = -1;
	}
	DistributeMap::~DistributeMap() {
		for (int i = 0; i < _room.size(); i++) {
			if (_room[i]->Get_roomtype() == BOSS_Room) _room[i]->delete_boss();
			delete _room[i];
		}
		_room.clear();
		for (int i = mon_bullet.size() - 1; i >= 0; i--) {
			delete mon_bullet[i];
		}
		mon_bullet.clear();
	}
	void DistributeMap::OAODistributeMap(vector<Room*> *room,Hero *hero,int Level) {
		//WaitingForChange.LoadBitmapByString({ "resources/change_level_background.bmp" });
		_hero = hero;
		
		for (int i = mon_bullet.size() - 1; i >= 0; i--) {
			delete mon_bullet[i];
		}
		mon_bullet.clear();

		vector<POSITION_OAO> temp;
		int tmpx = 0;
		int	tmpy =0;
		//printf("boss=%d\n", boss);
		_randforall.RandForMap(dis_map,(Level==4 || Level==9));
		_roomcount = _randforall.GetLenght();
		//printf("map=\n");
		/*for (int i = 0; i <12 ; i++) {
			for (int j = 0; j < 12; j++) {
				printf("%d,", dis_map[i][j]);
			}
			printf("\n");
		}*/
		printf("%d\n", _roomcount);
		
		int clk = 0;
			for (int x = 1; x < 11; x++) {
				for (int y = 1; y < 11; y++) {
					
					if (dis_map[x][y] == SPAWN_Room) {	

						_room.push_back(new SpawnRoom(MEDIUM, _hero,Level));
						
						//_room.push_back(new MonsterRoom(MEDIUM, _hero, _randforall.RandForMonsterNum()));
						//_room.push_back(new TeleportRoom(MEDIUM, _hero));
					}
					else if (dis_map[x][y] == MONSTER_Room) {
						if(Level <= 4) _room.push_back(new MonsterRoom(MEDIUM, _hero, _randforall.RandForMonsterNum(),3,2));
						else if(Level > 4) _room.push_back(new MonsterRoom(MEDIUM, _hero, _randforall.RandForMonsterNum(), 5, 3));
					}
					else if (dis_map[x][y] == BONUS_Room) {
						_room.push_back(new BonusRoom(SMALL, _hero));
					}
					else if (dis_map[x][y] == BOSS_Room) {


						if (Level == 4) {
							_room.push_back(new BossRoom(BIG, _hero, 4, 100, 100));
							once = false;
						}
						else if (Level == 9) {
							_room.push_back(new BossRoom(BIG, _hero, 10, 200, 200));
							once = false;
						}


					}
					else if (dis_map[x][y] == TELEPORT_Room) {
						_room.push_back(new TeleportRoom(MEDIUM, _hero));
					}
					
					if (clk != _roomcount) {
						
						if (dis_map[x][y] >0) {
							dis_map[x][y] = -1;
							temp.clear();
							if (_room[clk]->Get_roomtype() == SPAWN_Room) {
								_room[clk]->Set_position(700, 500);
								
								
								if (dis_map[x][y + 1] != 0 && dis_map[x][y+1]!=TELEPORT_Room && dis_map[x][y + 1] != BOSS_Room) {
									temp.push_back(RIGHT);
								}
								if (dis_map[x + 1][y] != 0 && dis_map[x+1][y] != TELEPORT_Room && dis_map[x+1][y] != BOSS_Room) {
									temp.push_back(DOWN);
								}
								
							}
							else if (_room[clk]->Get_roomtype() == MONSTER_Room) {
								_room[clk]->Set_position(1980 * y-1280, 1980 * x - 1480);//1280
								_room[clk]->set_Monster_place();
								
								if (dis_map[x][y + 1] != 0) {
									temp.push_back(RIGHT);
								}
								if (dis_map[x + 1][y] != 0) {
									temp.push_back(DOWN);
								}
								if (dis_map[x - 1][y] != 0) {
									temp.push_back(TOP);
								}
								if (dis_map[x][y - 1] != 0) {
									temp.push_back(LEFT);
								}
							}

							else if (_room[clk]->Get_roomtype() == BONUS_Room) {
								_room[clk]->Set_position(1980 * y - 1280, 1980 * x - 1480);
								
								if (dis_map[x][y + 1] != 0) {
									temp.push_back(RIGHT);
								}
								if (dis_map[x + 1][y] != 0) {
									temp.push_back(DOWN);
								}
								if (dis_map[x - 1][y] != 0) {
									temp.push_back(TOP);
								}
								if (dis_map[x][y - 1] != 0) {
									temp.push_back(LEFT);
								}
							}
							else if (_room[clk]->Get_roomtype() == TELEPORT_Room) {
								_room[clk]->Set_position(1980 * y - 1280, 1980 * x - 1480);
								
								if (dis_map[x][y + 1] != 0 && dis_map[x][y+1] != SPAWN_Room && dis_map[x][y+1] != BOSS_Room) {
									temp.push_back(RIGHT);
								}
								if (dis_map[x + 1][y] != 0 && dis_map[x +1][y] != SPAWN_Room && dis_map[x + 1][y] != BOSS_Room) {
									temp.push_back(DOWN);
								}
								if (dis_map[x - 1][y] != 0 && dis_map[x - 1][y] != SPAWN_Room && dis_map[x - 1][y] != BOSS_Room) {
									temp.push_back(TOP);
								}
								if (dis_map[x][y - 1] != 0 && dis_map[x ][y-1] != SPAWN_Room && dis_map[x][y-1] != BOSS_Room) {
									temp.push_back(LEFT);
								}
							}
							else if (_room[clk]->Get_roomtype() == BOSS_Room) {
								_room[clk]->Set_position(1980 * y - 1280, 1980 * x - 1480);
								if (dis_map[x][y + 1] != 0) {
									temp.push_back(RIGHT);
								}
								if (dis_map[x + 1][y] != 0) {
									temp.push_back(DOWN);
								}
								if (dis_map[x - 1][y] != 0) {
									temp.push_back(TOP);
								}
								if (dis_map[x][y - 1] != 0) {
									temp.push_back(LEFT);
								}
							}
							_room[clk]->Set_gate(temp);
							//printf("H=%d", 1980 * y, 1980 *x);
							
							
							clk++;
					}
					
					}

				}
			
		}
		*room = _room;
		for (int k = 0; k < _room.size(); k++) {
			if (_room[k]->Get_roomtype() == BOSS_Room) {
				_room[k]->take_boss()->set_pos((_room[k]->GetLeft() + _room[k]->GetWidth()) / 2, (_room[k]->GetTop() + _room[k]->GetHeight()) / 2);
				printf("bosspos = %d,%d\n", (_room[k]->GetLeft() + _room[k]->GetWidth()) / 2, (_room[k]->GetTop() + _room[k]->GetHeight()) / 2);
			}
		}
}
	void DistributeMap::Keep_detect_interaction() {
		for (int count = 0; count < _roomcount; count++) {
			_room[count]->Keep_detect_interact();
		}
		
	}
	void DistributeMap::ControlRoom(int MOVE, int bullet_num, Bullet *bullet) {
		bool mv = false;
		bool flag = false;
		test = true;
		for (int count = 0; count < _roomcount; count++) {
			_room[count]->RefreshMapXY();
			mv |= _room[count]->Is_crash(*_hero, MOVE, false);
		}
		
		for (int count = 0; count < _roomcount; count++) {
			_room[count]->RefreshMapXY();
			
			if (!mv) {
				flag = true;
				_room[count]->Move_room(MOVE);
				//printf("Move = %d\n", MOVE);

				if (_room[count]->Get_roomtype() == BOSS_Room) {
					//printf("bossdown\n");
					_room[count]->take_boss()->stay(MOVE, _hero->get_speed());
					for (int i = 0; i < 24; i++) {
						if (boss_bullet[i].is_flying()) boss_bullet[i].bullet_stay(MOVE, _hero->get_speed());
					}
				}
				if (_room[count]->Get_roomtype() == MONSTER_Room) {
					for (int i = 0; i < _room[count]->get_Monster_num(); i++)
						_room[count]->get_which_mon(i)->stay(MOVE, _hero->get_speed());
				}	

			}
			else {
				break;
			}
				

		}
		if (flag) {
			for (int i = 0; i <= bullet_num; i++) {
				if (bullet[i].is_flying()) {
					bullet[i].bullet_stay(MOVE, _hero->get_speed());
				}
			}
		}
		
		
	}
	void DistributeMap::ControlGate() {
		for (int count = 0; count < _roomcount; count++) {
			if (_room[count]->TF_entry()) {
				if(_room[count]->Get_roomtype()== MONSTER_Room || _room[count]->Get_roomtype() == BOSS_Room)
					_room[count]->Gate(GATE_CLOSE);
				else {
					_room[count]->Gate(GATE_OPEN);
				}
				
			}
		}
	}
	bool DistributeMap::TF_interaction() {
		for (int count = 0; count < _roomcount; count++) {
			if (_room[count]->TF_interaction() && (_room[count]->Get_roomtype()==TELEPORT || _room[count]->Get_roomtype() == BOSS_Room)) {
				return true;
			}
		}
		return false;
	}
	void DistributeMap::DeleteAll() {
		
		for (int i = 0; i < _room.size(); i++) {
			delete _room[i];
		}
		_room.clear();
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				dis_map[i][j] = 0;
			}
		}
	}
	void DistributeMap::Monster_Move(Hero *hero, int bullet_num, Bullet *bullet, times time) {
		//printf("size = %d\n", mon_bullet.size());
		int room = this->Where_is_Hero(*hero);
		int tempx, tempy;
		bool *tf;
		if (room == 100) {
			for (int i = 0; i <= bullet_num; i++) bullet[i].bullet_crash();
			for (int i = 0; i < _room.size(); i++) {
				if (_room[i]->Get_roomtype() == MONSTER_Room) {
					for (int j = 0; j < _room[i]->get_Monster_num(); j++)
						_room[i]->get_which_mon(j)->anime(false, LEFT);
				}
			}
		}
		if (room != 100) {

			if (_room[room]->Get_roomtype() == BOSS_Room && _room[room]->take_boss()->get_blood()>0) {
				if (_room[room]->take_boss()->Get_type() == 100) {
					if (!once) {
						printf("once\n");
						printf("test=%d", _room[room]->GetLeft());
						_room[room]->take_boss()->set_pos((_room[room]->GetLeft() + _room[room]->GetWidth()) / 2, (_room[room]->GetTop() + _room[room]->GetHeight()) / 2);
						for (int i = 0; i < 24; i++) {
							boss_bullet[i].LoadBitmapByString({ "resources/purple_boss.bmp" }, RGB(255, 255, 255));
							boss_bullet[i].SetTopLeft(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop());
						}
						for (int i = 0; i < 3; i++) {
							boss_bullet[0 + i * 8].boss_shot(0, 0, 0, 1); //���W
							boss_bullet[1 + i * 8].boss_shot(0, 1, 0, 1); //���k�W
							boss_bullet[2 + i * 8].boss_shot(0, 1, 0, 0); //���k
							boss_bullet[3 + i * 8].boss_shot(0, 1, 1, 0); //���k�U
							boss_bullet[4 + i * 8].boss_shot(0, 0, 1, 0); //���U
							boss_bullet[5 + i * 8].boss_shot(1, 0, 1, 0); //�����U
							boss_bullet[6 + i * 8].boss_shot(1, 0, 0, 0); //����
							boss_bullet[7 + i * 8].boss_shot(1, 0, 0, 1); //�����W
						}
						once = true;
					}
					if (!_room[room]->take_boss()->get_phase(1) && !_room[room]->take_boss()->get_boss_loading()) {
						_room[room]->take_boss()->set_time();
						_room[room]->take_boss()->set_phase(1);
					}
					else if (_room[room]->take_boss()->get_phase(1) && !_room[room]->take_boss()->get_boss_loading()) {
						if ((clock() - _room[room]->take_boss()->get_time()) / (double)(CLOCKS_PER_SEC) >= 1.0) {
							_room[room]->take_boss()->set_time();
							if (_room[room]->take_boss()->get_phase(1) && _room[room]->take_boss()->get_phase(2)) _room[room]->take_boss()->set_phase(3);
							else if (_room[room]->take_boss()->get_phase(1) && !_room[room]->take_boss()->get_phase(2)) _room[room]->take_boss()->set_phase(2);
						}
					}
					if (_room[room]->take_boss()->get_phase(3)) {
						//printf("here1\n");
						bool temp = false;
						for (int i = 0; i < 24; i++) {
							if (boss_bullet[i].is_flying()) temp = true;
						}
						if (!temp) {
							//printf("here2\n");
							_room[room]->take_boss()->check_is_shot_end();
							_room[room]->take_boss()->set_boss_loading(0);
							//int x = rand() % (max - min + 1) + min;
							_room[room]->rand_boss_pos(*_hero);
							for (int i = 0; i < 24; i++) {
								boss_bullet[i].reset_flying();
								boss_bullet[i].SetTopLeft(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop());
							}
							_room[room]->take_boss()->set_time();
						}

					}
					else if (clock() - _room[room]->take_boss()->get_time() / (double)(CLOCKS_PER_SEC) >= 1.5 && !_room[room]->take_boss()->get_phase(1)) {
						_room[room]->take_boss()->set_boss_loading(1);
					}

					if (_room[room]->take_boss()->get_phase(1)) {
						for (int i = 0; i < 8; i++) {
							boss_bullet[i].bullet_fly(_room[room]->take_boss(), _room[room], hero, 1, _room[room]->take_boss()->get_power());
						}
					}
					if (_room[room]->take_boss()->get_phase(2)) {
						for (int i = 8; i < 16; i++) {
							boss_bullet[i].bullet_fly(_room[room]->take_boss(), _room[room], hero, 1, _room[room]->take_boss()->get_power());
						}
					}
					if (_room[room]->take_boss()->get_phase(3)) {
						for (int i = 16; i < 24; i++) {
							boss_bullet[i].bullet_fly(_room[room]->take_boss(), _room[room], hero, 1, _room[room]->take_boss()->get_power());
						}
					}
					for (int i = 0; i <= bullet_num; i++) bullet[i].shoot_mon(_room[room], _room[room]->take_boss(), hero, hero->get_power());
					if (_room[room]->take_boss()->get_blood() <= 0) for (int i = 0; i < 24; i++) boss_bullet[i].bullet_crash();
				}
				else if (_room[room]->take_boss()->Get_type() == 200) {
					if (!once) {
						_room[room]->take_boss()->set_pos((_room[room]->GetLeft() + _room[room]->GetWidth()) / 2, (_room[room]->GetTop() + _room[room]->GetHeight() / 2) / 2);
						printf("once\n");
						once = true;
					}
					if (!_room[room]->take_boss()->get_phase(200) && test) {
						printf("rooml = %d,roomw = %d,roomt = %d,roomh = %d\n", _room[room]->GetLeft()+_room[room]->take_boss()->get_left_pic().GetWidth(), _room[room]->GetLeft()+_room[room]->GetWidth() - _room[room]->take_boss()->get_left_pic().GetWidth(), _room[room]->GetTop() + _room[room]->take_boss()->get_left_pic().GetHeight(), _room[room]->GetTop() + _room[room]->GetTop()+_room[room]->GetHeight() - _room[room]->take_boss()->get_left_pic().GetHeight());
						printf("monpos = %d,%d\n", _room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop());
						_room[room]->take_boss()->set_range(*_hero);
						int temp_x = abs(_room[room]->take_boss()->take_x());
						int temp_y = abs(_room[room]->take_boss()->take_y());
						int temp_final;
						if(temp_y != 0) temp_final = (_room[room]->take_boss()->take_x() * _room[room]->take_boss()->get_speed()) / temp_y;
						int final_x, final_y;
						bool final_flag[2] = { false,false };
						if (temp_y != 0) {
							if (abs(temp_final) > 50) {
								final_flag[0] = true;
								if (temp_final > 0) final_x = -50;
								else final_x = 50;
							}
							else if (temp_y > 50) {
								final_flag[1] = true;
								if (_room[room]->take_boss()->take_y() > 0) final_y = -50;
								else final_y = 50;
							}
							if (!final_flag[0]) final_x = -temp_final;
							if (!final_flag[1]) final_y = -_room[room]->take_boss()->take_y();
							_room[room]->take_boss()->set_xy(final_x,final_y);
						}
						else if(temp_y == 0 && _room[room]->take_boss()->take_x() > 0) _room[room]->take_boss()->set_xy(-_room[room]->take_boss()->get_speed(), 0);
						else if(temp_y == 0 && _room[room]->take_boss()->take_x() < 0)_room[room]->take_boss()->set_xy(_room[room]->take_boss()->get_speed(), 0);
						_room[room]->take_boss()->set_phase(200);
						if (_room[room]->Is_crash(*_room[room]->take_boss(), LEFT, true)) _room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft() + _room[room]->take_boss()->get_speed() * 3, _room[room]->take_boss()->GetTop());
						if (_room[room]->Is_crash(*_room[room]->take_boss(), RIGHT, true)) _room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft() - _room[room]->take_boss()->get_speed() * 3, _room[room]->take_boss()->GetTop());
						if (_room[room]->Is_crash(*_room[room]->take_boss(), TOP, true)) _room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop() + _room[room]->take_boss()->get_speed() * 3);
						if (_room[room]->Is_crash(*_room[room]->take_boss(), DOWN, true)) _room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop() - _room[room]->take_boss()->get_speed() * 3);
						printf("x = %d, y = %d\n", _room[room]->take_boss()->get_boss_x(), _room[room]->take_boss()->get_boss_y());
					}
					if (_room[room]->take_boss()->get_phase(200)) {
						if (!_room[room]->take_boss()->get_stopping()) {
							int temp_x = _room[room]->take_boss()->GetLeft();
							int temp_y = _room[room]->take_boss()->GetTop();
							if (temp_x - hero->get_deter_area().GetLeft() >= 0) {
								if (!_room[room]->Is_crash(*_room[room]->take_boss(), LEFT, true)) {
									_room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft() + _room[room]->take_boss()->get_boss_x(), _room[room]->take_boss()->GetTop());
									printf("mon1 = %d,%d,bound = %d\n", _room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop(), _room[room]->GetLeft());
								}
							}
							else {
								if (!_room[room]->Is_crash(*_room[room]->take_boss(), RIGHT, true)) {

									_room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft() + _room[room]->take_boss()->get_boss_x(), _room[room]->take_boss()->GetTop());
									printf("mon2 = %d,%d,bound = %d\n", _room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop(), _room[room]->GetLeft() + _room[room]->GetWidth());
								}
							}
							if (tempy - hero->get_deter_area().GetTop() >= 0) {
								if (!_room[room]->Is_crash(*_room[room]->take_boss(), TOP, true)) {
									_room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop() + _room[room]->take_boss()->get_boss_y());
									printf("mon3 = %d,%d,bound = %d\n", _room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop(), _room[room]->GetTop() + _room[room]->GetHeight());
								}
							}
							else {
								if (!_room[room]->Is_crash(*_room[room]->take_boss(), DOWN, true)) {
									_room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop() + _room[room]->take_boss()->get_boss_y());
									printf("mon4 = %d,%d,bound = %d\n", _room[room]->take_boss()->GetLeft(), _room[room]->take_boss()->GetTop(), _room[room]->GetHeight());
								}
							}
							if (_room[room]->take_boss()->get_left_pic().IsOverlap(_room[room]->take_boss()->get_left_pic(), _hero->get_left_pic()) && !_hero->get_invincible()) {
								_hero->hurt(3);
								hero->hurt_time();
								hero->is_invincible(0);
							}
							if (_room[room]->take_boss()->GetTop() > (_room[room]->GetTop() + _room[room]->GetTop() + _room[room]->GetHeight() - _room[room]->take_boss()->get_left_pic().GetHeight())) {
								_room[room]->take_boss()->set_pos(_room[room]->take_boss()->GetLeft(), _room[room]->GetTop() + _room[room]->GetTop() + _room[room]->GetHeight() - _room[room]->take_boss()->get_left_pic().GetHeight());
								_room[room]->take_boss()->set_phase(201);
								_room[room]->take_boss()->set_boss_loading(1);
								_room[room]->take_boss()->set_stop(1);
							}
						}
					
						if(_room[room]->Is_crash(*_room[room]->take_boss(),TOP,true)|| _room[room]->Is_crash(*_room[room]->take_boss(), LEFT, true)|| _room[room]->Is_crash(*_room[room]->take_boss(), RIGHT, true)|| _room[room]->Is_crash(*_room[room]->take_boss(), DOWN, true)){
							if (!_room[room]->take_boss()->get_boss_loading()) {
								_room[room]->take_boss()->set_time();
								_room[room]->take_boss()->set_boss_loading(0);
								_room[room]->take_boss()->set_stop(0);
							}
						}
						if ((clock() - _room[room]->take_boss()->get_time()) / (double)(CLOCKS_PER_SEC) >= 0.5 && _room[room]->take_boss()->get_stopping()) {
							printf("continue\n");
							_room[room]->take_boss()->set_phase(201);
							_room[room]->take_boss()->set_boss_loading(1);
							_room[room]->take_boss()->set_stop(1);
						}
					}
					for (int i = 0; i <= bullet_num; i++) bullet[i].shoot_mon(_room[room], _room[room]->take_boss(), hero, hero->get_power());
				}	
				else {
					for (int i = 0; i < bullet_num; i++) {
						if (bullet[i].is_flying()) bullet[i].bullet_fly(_room[room], 0);
					}
				}
				time.hero_(hero, clock(), hero->get_hurt_time());
			}
			else if (_room[room]->Get_roomtype() == BOSS_Room) {
				for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_fly(_room[room], 0);
			}
			if (_room[room]->Get_roomtype() == MONSTER_Room && !_room[room]->take_is_fight_end()) {
				//printf("TF=%d\n",setroom[0]->TF_monster_defeat());

				int small_mon;
				for (int i = 0; i < _room[room]->get_Monster_num(); i++) {
					tf = _room[room]->get_which_mon(i)->detect(hero);
					if (!tf[0]) {
						if (!_room[room]->get_which_mon(i)->get_dir()) {
							_room[room]->get_which_mon(i)->set_right();
							_room[room]->get_which_mon(i)->anime(false, RIGHT);
						}
						else {
							_room[room]->get_which_mon(i)->set_left();
							_room[room]->get_which_mon(i)->anime(false, LEFT);
						}
						
					}
					
					tempx = _room[room]->get_which_mon(i)->GetLeft();
					tempy = _room[room]->get_which_mon(i)->GetTop();
					
					//pig
					if (tf[0] && _room[room]->get_which_mon(i)->Get_type() == 1) {
						
						if (tempx - hero->get_deter_area().GetLeft() >= 0 ) {
							_room[room]->get_which_mon(i)->set_left();
							_room[room]->get_which_mon(i)->anime(true, LEFT);
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), LEFT, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft()- _room[room]->get_which_mon(i)->get_speed(), _room[room]->get_which_mon(i)->get_right_pic().GetTop());
							}
						}
						else {
							_room[room]->get_which_mon(i)->set_right();
							_room[room]->get_which_mon(i)->anime(true, RIGHT);
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), RIGHT, true)) {
								
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft()+ _room[room]->get_which_mon(i)->get_speed(), _room[room]->get_which_mon(i)->get_right_pic().GetTop());
							}
						}
						if (tempy - hero->get_deter_area().GetTop() >= 0 ) {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), TOP, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft(), _room[room]->get_which_mon(i)->get_right_pic().GetTop() - _room[room]->get_which_mon(i)->get_speed());
							}
						}
						else {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), DOWN, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft(), _room[room]->get_which_mon(i)->get_right_pic().GetTop() + _room[room]->get_which_mon(i)->get_speed());
							}
						}
						
						
					}
					
					//if (tf[1]) hero->hurt_time();
					//goblin
					if (tf[0] && _room[room]->get_which_mon(i)->Get_type() == 2) {
						if (tempx - hero->get_deter_area().GetLeft() >= 0) {
							_room[room]->get_which_mon(i)->set_left();
							_room[room]->get_which_mon(i)->anime(false, LEFT);
						}
						else {
							_room[room]->get_which_mon(i)->set_right();
							_room[room]->get_which_mon(i)->anime(false, RIGHT);
						}
					}
					if (_room[room]->get_which_mon(i)->Get_type() == 2  && !_room[room]->get_which_mon(i)->is_loading() && _room[room]->get_which_mon(i)->is_alive()) {
						
						Bullet *bull = new Bullet;
						bull->LoadBitmapByString({ "resources/purple.bmp" }, RGB(255, 255, 255));
						bull->SetTopLeft(_room[room]->get_which_mon(i)->GetLeft(), _room[room]->get_which_mon(i)->GetTop());
						_room[room]->get_which_mon(i)->set_loading();
						mon_bullet.push_back(bull);
						mon_bullet[mon_bullet.size()-1]->mon_shoot(hero,_room[room]->get_which_mon(i));
						_room[room]->get_which_mon(i)->set_loading();
						//printf("%d = shooooooooooot\n",i);
					}
					for (int j = 0; j < mon_bullet.size(); j++) {
						if (mon_bullet[j]->is_flying()) {
							mon_bullet[j]->bullet_fly(_room[room]->get_which_mon(i), _room[room], hero,1, _room[room]->get_which_mon(i)->get_power());
							//printf("%d = shooting\n", j);
						}
					}
					if (_room[room]->get_which_mon(i)->is_loading() && _room[room]->get_which_mon(i)->take_dis() > 200) {
						tempx = _room[room]->get_which_mon(i)->GetLeft();
						tempy = _room[room]->get_which_mon(i)->GetTop();

						if (tempx - hero->get_deter_area().GetLeft() >= 0) {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), LEFT, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft() - 1, _room[room]->get_which_mon(i)->get_right_pic().GetTop());
							}
						}
						else {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), RIGHT, true)) {

								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft() + 1, _room[room]->get_which_mon(i)->get_right_pic().GetTop());
							}
						}
						if (tempy - hero->get_deter_area().GetTop() >= 0) {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), TOP, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft(), _room[room]->get_which_mon(i)->get_right_pic().GetTop() - 1);
							}
						}
						else {
							if (!_room[room]->Is_crash(*_room[room]->get_which_mon(i), DOWN, true)) {
								_room[room]->get_which_mon(i)->set_pos(_room[room]->get_which_mon(i)->get_right_pic().GetLeft(), _room[room]->get_which_mon(i)->get_right_pic().GetTop() + 1);
							}
						}


					}
					if ((clock() - _room[room]->get_which_mon(i)->get_shot_time()) / (double)(CLOCKS_PER_SEC) >= 1.0) {
						_room[room]->get_which_mon(i)->reset_loading();
					}
				}
				small_mon = _room[room]->get_small_dis(*hero);
				for (int i = 0; i <= bullet_num; i++) if (bullet[i].shoot_mon(_room[room], _room[room]->get_which_mon(small_mon),hero,hero->get_power())) _room[room]->get_which_mon(small_mon)->hurt_time();
			}
			else if(_room[room]->Get_roomtype() == MONSTER_Room && _room[room]->take_is_fight_end()){
				for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_fly(_room[room],0);
			}
			if (_room[room]->Get_roomtype() == MONSTER_Room && !_room[room]->take_is_fight_end()) for (int i = 0; i < _room[room]->get_Monster_num(); i++) time.monster_(_room[room]->get_which_mon(i), clock(), _room[room]->get_which_mon(i)->get_hurt_time());
			if (_room[room]->Get_roomtype() == MONSTER_Room && _room[room]->take_is_fight_end()) {
				for (int i = mon_bullet.size() - 1; i >= 0; i--) {
					delete mon_bullet[i];
				}
				mon_bullet.clear();
			}
			for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_fly(_room[room], 0);
		}
		else {
			int temp = 0;
			int gate = 0;
			for (int count = 0; count < _roomcount; count++) {
				if (_room[count]->TF_in_route()) {
					temp = count;
					gate = _room[count]->GetGateNum();
				}
			}
			for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_fly(_room[temp], gate);
		}
		time.hero_(hero, clock(), hero->get_hurt_time());
		if (time.add_shield_(hero, clock(), hero->get_hurt_time()) ) hero->hurt_time();


	}
	int DistributeMap::Where_is_Hero(Hero hero) {
		int temp = 100;
		for (int i = 0; i < _roomcount; i++) {
			if (_room[i]->TF_entry()) {
				
				temp = i;
			}
			
				
		}
		return temp;
	}
	Monster *DistributeMap::get_mon() {
		int mon = _room[this->Where_is_Hero(*_hero)]->get_small_dis(*_hero);
		return _room[this->Where_is_Hero(*_hero)]->get_which_mon(mon);
	}
	bool DistributeMap::is_end() {
		if (this->Where_is_Hero(*_hero) == 100) return false;
		if (_room[this->Where_is_Hero(*_hero)]->Get_roomtype() == MONSTER_Room && !_room[this->Where_is_Hero(*_hero)]->take_is_fight_end()) return true;
		else if (_room[this->Where_is_Hero(*_hero)]->Get_roomtype() == BOSS_Room) return true;
		else return false;
	}
	bool* DistributeMap::get_TF_move() {
		return TF_move;
	}
	void DistributeMap::show_mon_bullet() {
		if (Where_is_Hero(*_hero) != 100) {
			for (int i = 0; i < mon_bullet.size(); i++) {
				if (mon_bullet[i]->is_flying()) mon_bullet[i]->ShowBitmap();
			}
			if (_room[Where_is_Hero(*_hero)]->Get_roomtype() == BOSS_Room && _room[Where_is_Hero(*_hero)]->take_boss()->is_alive()) {
				for (int i = 0; i < 24; i++) {
					if (boss_bullet[i].is_flying()) boss_bullet[i].ShowBitmap();
				}
			}
		}
	}
	void DistributeMap::near_attack() {
		if (this->Where_is_Hero(*_hero) != 100 && _room[Where_is_Hero(*_hero)]->Get_roomtype() == MONSTER_Room) {
			for (int i = 0; i < _room[this->Where_is_Hero(*_hero)]->get_Monster_num(); i++) {
				if ((_hero->GetLeft() + 70) >= _room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->GetLeft() && _room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->GetLeft() >= (_hero->GetLeft() - 70)) {
					if (_hero->GetTop() + 70 >= _room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->GetTop() && _room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->GetTop() >= _hero->GetTop() - 70) {
						if (_room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->is_alive()) _room[this->Where_is_Hero(*_hero)]->get_which_mon(i)->lose_blood(_hero->get_power() + 1);
					}
				}
			}
		}
		if (this->Where_is_Hero(*_hero) != 100 && _room[Where_is_Hero(*_hero)]->Get_roomtype() == BOSS_Room && _room[Where_is_Hero(*_hero)]->take_boss()->get_blood()>0) {
			if ((_hero->GetLeft() + 70) >= _room[this->Where_is_Hero(*_hero)]->take_boss()->GetLeft() && _room[this->Where_is_Hero(*_hero)]->take_boss()->GetLeft() >= (_hero->GetLeft() - 70)) {
				if (_hero->GetTop() + 70 >= _room[this->Where_is_Hero(*_hero)]->take_boss()->GetTop() && _room[this->Where_is_Hero(*_hero)]->take_boss()->GetTop() >= _hero->GetTop() - 70) {
					if (_room[this->Where_is_Hero(*_hero)]->take_boss()->is_alive()) _room[this->Where_is_Hero(*_hero)]->take_boss()->lose_blood(_hero->get_power() + 1);
				}
			}
		}
	}
}