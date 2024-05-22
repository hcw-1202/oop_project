#include "stdafx.h"
#include "../Library/gameutil.h"
#include "Detect_crash.h"
#include "room.h"

namespace game_framework {
	HeroSkill Room::Hero_talent;
	Room::Room(int size,Hero *hero) {
		_size = size;
		_hero = hero;
		mid_x = hero->GetWidth() / 2 + hero->GetLeft();
		mid_y = hero->GetHeight() / 2 + hero->GetTop();
		gap =15;
		_movemode = 0;
		path_lenght = (33 - _size)/2 ;
		vector<Block> temp1, temp2;
		for (int i = 0; i < size; i++) {
			temp1.push_back(Block());
			temp2.push_back(Block());
		}
		for (int i = 0; i < size; i++) {
			Creat_map.push_back(temp1);
			Creat_map_floor.push_back(temp2);
		}
		_height = 0;
		_width = 0;

		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				Creat_map_floor[x][y].blocktype(FLOOR);
				if (x == 0)
					Creat_map[x][y].blocktype(TOP_WALL);
				else if (x == size - 1)
					Creat_map[x][y].blocktype(DOWN_WALL);
				else if (y == 0)
					Creat_map[x][y].blocktype(LEFT_WALL);
				else if (y == size - 1)
					Creat_map[x][y].blocktype(RIGHT_WALL);
				else {
					Creat_map[x][y].blocktype(OTHER);
				}
			}
		}
		for (int x = 0; x < _size; x++) {
			_height += Creat_map_floor[x][0].GetHeight();
		}
		for (int y = 0; y < _size; y++) {
			_width += Creat_map_floor[0][y].GetWidth();
		}
	}
	void Room::Move_room(int room_move) {
		if (room_move == TOP) {
			for (int x = 0; x < _size; x++) {
				for (int y = 0; y < _size; y++) {
					Creat_map[x][y].block_position(Creat_map[x][y].GetLeft(), Creat_map[x][y].GetTop() + _hero->get_speed());
					Creat_map_floor[x][y].block_position(Creat_map_floor[x][y].GetLeft(), Creat_map_floor[x][y].GetTop() + _hero->get_speed());
				}
			}
			for (int place = 0; place < _gate.size(); place++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(route[place][i][j].GetLeft(), route[place][i][j].GetTop() + _hero->get_speed());
						route_floor[place][i][j].block_position(route_floor[place][i][j].GetLeft(), route_floor[place][i][j].GetTop() + _hero->get_speed());
					}
				}
			}
		}
		else if (room_move == DOWN) {
			for (int x = 0; x < _size; x++) {
				for (int y = 0; y < _size; y++) {
					Creat_map[x][y].block_position(Creat_map[x][y].GetLeft(), Creat_map[x][y].GetTop() - _hero->get_speed());
					Creat_map_floor[x][y].block_position(Creat_map_floor[x][y].GetLeft(), Creat_map_floor[x][y].GetTop() - _hero->get_speed());
				}
			}
			for (int place = 0; place < _gate.size(); place++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(route[place][i][j].GetLeft() , route[place][i][j].GetTop() - _hero->get_speed());
						route_floor[place][i][j].block_position(route_floor[place][i][j].GetLeft(), route_floor[place][i][j].GetTop() - _hero->get_speed());
					}
				}
			}
		}
		if (room_move == RIGHT) {
			for (int x = 0; x < _size; x++) {
				for (int y = 0; y < _size; y++) {
					Creat_map[x][y].block_position(Creat_map[x][y].GetLeft() - _hero->get_speed(), Creat_map[x][y].GetTop());
					Creat_map_floor[x][y].block_position(Creat_map_floor[x][y].GetLeft()-_hero->get_speed(), Creat_map_floor[x][y].GetTop() );
				}
			}
			for (int place = 0; place < _gate.size(); place++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(route[place][i][j].GetLeft() - _hero->get_speed(), route[place][i][j].GetTop());
						route_floor[place][i][j].block_position(route_floor[place][i][j].GetLeft() - _hero->get_speed(), route_floor[place][i][j].GetTop());
					}
				}
			}
		}
		else if (room_move == LEFT) {
			for (int x = 0; x < _size; x++) {
				for (int y = 0; y < _size; y++) {
					Creat_map[x][y].block_position(Creat_map[x][y].GetLeft() + _hero->get_speed(), Creat_map[x][y].GetTop());
					Creat_map_floor[x][y].block_position(Creat_map_floor[x][y].GetLeft()+_hero->get_speed(), Creat_map_floor[x][y].GetTop() );
				}
			}
			for (int place = 0; place < _gate.size(); place++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(route[place][i][j].GetLeft() + _hero->get_speed(), route[place][i][j].GetTop());
						route_floor[place][i][j].block_position(route_floor[place][i][j].GetLeft() + _hero->get_speed(), route_floor[place][i][j].GetTop());
					}
				}
			}
		}
		//Hero_talent
		if(_type==SPAWN_Room)
			Hero_talent.Set_Skill_block(Creat_map_floor[3][3].GetLeft() + (Creat_map_floor[3][3].GetWidth() - 40) / 2, Creat_map_floor[3][3].GetTop() + (Creat_map_floor[3][3].GetHeight() - 40) / 2, _Level);
	}
	void Room::RefreshMapXY() {
		_left = (Creat_map[0][0].GetLeft());
		_top = (Creat_map[0][0].GetTop());
	}
	void Room::Set_gate(vector <POSITION_OAO> gate_position) {
		_gate = gate_position;
		gateleft = ((_size + 1) / 2) - 3;
		gateright = ((_size + 1) / 2) + 1;
		for (int i = 0; i < gate_position.size(); i++) {
			if (gate_position[i] == TOP) {
				for (int i = gateleft +1; i < gateright; i++) {
					Creat_map[0][i].blocktype(OTHER);
					Creat_map_floor[0][i].blocktype(GATE_OPEN);
				}
			}
			if (gate_position[i] == RIGHT) {
				Creat_map[gateleft][_size - 1].blocktype(TOP_WALL);
				for (int i = gateleft +1; i < gateright; i++) {
					Creat_map[i][_size - 1].blocktype(OTHER);
					Creat_map_floor[i][_size - 1].blocktype(GATE_OPEN);
				}
			}
			if (gate_position[i] == DOWN) {
				Creat_map[_size-1][gateleft].blocktype(LEFT_WALL);
				Creat_map[_size-1][gateright].blocktype(RIGHT_WALL);
				Creat_map_floor[_size-1][gateleft].blocktype(OTHER);
				Creat_map_floor[_size-1][gateright].blocktype(OTHER);
				for (int i = gateleft +1; i < gateright; i++) {
					Creat_map[_size - 1][i].blocktype(OTHER);
					Creat_map_floor[_size - 1][i].blocktype(GATE_OPEN);
				}
			}
			if (gate_position[i] == LEFT) {
				Creat_map[gateleft][0].blocktype(TOP_WALL);
				for (int i = gateleft +1; i < gateright; i++) {
					Creat_map[i][0].blocktype(OTHER);
					Creat_map_floor[i][0].blocktype(GATE_OPEN);
				}
			}
		}
		this->Set_route();
	}
	void Room::Keep_detect_interact() {

	}
	void Room::Set_route() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				for (int x = 0; x < path_lenght; x++) {
					route[i][j].push_back(Block());
					route_floor[i][j].push_back(Block());
				}
			}
		}
		for (int place = 0; place < _gate.size(); place++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < path_lenght; j++) {
					route_floor[place][i][j].blocktype(FLOOR);
					if (i == 0) {
						if(_gate[place]==LEFT || _gate[place] == RIGHT)
							route[place][i][j].blocktype(TOP_WALL);
						else
							route[place][i][j].blocktype(LEFT_WALL);
					}
					else if (i == 4) {
						if (_gate[place] == LEFT || _gate[place] == RIGHT)
							route[place][i][j].blocktype(DOWN_WALL);
						else
							route[place][i][j].blocktype(RIGHT_WALL);
					}
					else {
						route[place][i][j].blocktype(OTHER);
					}
				}
			}
		}
		for (int place = 0; place < _gate.size(); place++) {
			if (_gate[place] == TOP) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(Creat_map[0][gateleft].GetLeft()+ route_floor[place][i][j].GetWidth()*i, Creat_map[0][gateleft].GetTop() - route_floor[place][i][j].GetHeight()*(j+1));
						route_floor[place][i][j].block_position(Creat_map_floor[0][gateleft].GetLeft() + route_floor[place][i][j].GetWidth()*i, Creat_map_floor[0][gateleft].GetTop() - route_floor[place][i][j].GetHeight()*(j + 1));
					}
				}
			}
			if (_gate[place] == RIGHT) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(Creat_map[gateleft][_size-1].GetLeft() + route_floor[place][i][j].GetWidth()*(j+1), Creat_map[gateleft][0].GetTop() + route_floor[place][i][j].GetHeight()*i);
						route_floor[place][i][j].block_position(Creat_map_floor[gateleft][_size-1].GetLeft() + route_floor[place][i][j].GetWidth()*(j + 1), Creat_map_floor[gateleft][0].GetTop() + route_floor[place][i][j].GetHeight()*i);
					}
				}
			}
			if (_gate[place] == DOWN) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(Creat_map[0][gateleft].GetLeft() + route_floor[place][i][j].GetWidth()*i, Creat_map[_size-1][gateleft].GetTop() + route_floor[place][i][j].GetHeight()*(j + 1));
						route_floor[place][i][j].block_position(Creat_map_floor[0][gateleft].GetLeft() + route_floor[place][i][j].GetWidth()*i, Creat_map_floor[_size - 1][gateleft].GetTop() + route_floor[place][i][j].GetHeight()*(j + 1));
					}
				}
			}
			if (_gate[place] == LEFT) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < path_lenght; j++) {
						route[place][i][j].block_position(Creat_map[gateleft][0].GetLeft() - route_floor[place][i][j].GetWidth()*(j + 1), Creat_map[gateleft][0].GetTop() + route_floor[place][i][j].GetHeight()*i);
						route_floor[place][i][j].block_position(Creat_map_floor[gateleft][0].GetLeft() - route_floor[place][i][j].GetWidth()*(j + 1), Creat_map_floor[gateleft][0].GetTop() + route_floor[place][i][j].GetHeight()*i);						
					}
				}
			}	
		}
	}
	void Room::Set_position(int x, int y) {
		_left = x;
		_top = y;
		for (int x = 0; x < _size; x++) {
			for (int y = 0; y < _size; y++) {
				Creat_map[x][y].block_position(_left + (y-_size/2) * Creat_map_floor[x][y].GetWidth(), _top + (x - _size / 2) * Creat_map_floor[x][y].GetHeight());
				Creat_map_floor[x][y].block_position(_left + (y - _size / 2) * Creat_map_floor[x][y].GetWidth(), _top + (x - _size / 2) * Creat_map_floor[x][y].GetHeight()+20);//+20
				if (Creat_map[x][y].Gettype() == CHEST_CLOSE) {
					Creat_map[x][y].block_position(_left + (y - _size / 2) * Creat_map[x][y].GetWidth()+(Creat_map_floor[x][y].GetWidth()- Creat_map[x][y].GetWidth())/2, _top + (x - _size / 2) * Creat_map[x][y].GetHeight()+ (Creat_map_floor[x][y].GetHeight() - Creat_map[x][y].GetHeight()) / 2+20);
				}
			}
		}
	}
	bool Room::TF_interaction() {
		return false;
	}
	ROOMTYPE Room::Get_roomtype() {
		return _type;
	}
	Room::~Room() {
	};
	void Room::show() {
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
				if (Creat_map[x][y].Gettype() == CHEST_CLOSE || Creat_map[x][y].Gettype() == CHEST_OPEN)
					Creat_map[x][y].show();
			}
		}
		
		if (TF_inner_room() || TF_in_route()) {
			_hero->show();
		}
			
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
		if (TF_inner_room() || TF_in_route()) {
			Hero_talent.show_hero_talent();
		}
		
	};
	void Room::Now_Level(int level) {
		_Level = level;
	}
	bool Room::Is_crash(Character character,int mode,bool TF_inroom) {
		
		int Xrelatity;
		int Yrelatity;
		_movemode = mode;
		if (this->TF_inner_room()) {
			
			
			if (mode == TOP) {
				Xrelatity = (character.GetLeft() + character.GetWidth() / 2) - (_left);
				Yrelatity = (character.GetTop() + character.GetHeight() / 2) - gap-20 - (_top);
				
				
			}
			else if (mode == RIGHT) {
				Xrelatity = (character.GetLeft() + character.GetWidth() / 2) + gap - (_left);
				Yrelatity = (character.GetTop() + character.GetHeight() / 2) - (_top);
				
			}
			else if (mode == DOWN) {
				Xrelatity = (character.GetLeft() + character.GetWidth() / 2) - (_left);
				Yrelatity = (character.GetTop() + character.GetHeight() / 2) +gap - (_top);
				
			}
			else if (mode ==LEFT) {
				Xrelatity = (character.GetLeft() + character.GetWidth() / 2) - gap- (_left);
				Yrelatity = (character.GetTop() + character.GetHeight() / 2) - (_top);
				
			}
			Xrelatity = round(static_cast<float>(Xrelatity / 60));
			Yrelatity = round(static_cast<float>(Yrelatity / 60));
			//printf("X=%d, Y=%d\n", Xrelatity, Yrelatity);
			if(Yrelatity >= _size)
				Yrelatity = _size - 1;
			else if (Yrelatity < 0)
				Yrelatity = 0;
			if (Xrelatity >= _size)
				Xrelatity = _size - 1;
			else if (Xrelatity < 0)
				Xrelatity = 0;
			
			
			return Creat_map[Yrelatity][Xrelatity].is_obstacle();
		}
		else if (TF_in_route()) {
			//--------------------------------------------------------------------------------------------------------------------------------------
			if (mode == TOP) {
				
				if ((character.GetLeft() + character.GetWidth() / 2) < _left) {
					//RoomLeft
					Xrelatity = (Creat_map[gateleft][0].GetLeft() )-(character.GetLeft() + character.GetWidth() / 2);
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) - gap - (Creat_map[gateleft][0].GetTop());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == LEFT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}

					
				}
				else if ((character.GetLeft() + character.GetWidth() / 2) > _left+_width){
					//RoomRight
					Xrelatity = (character.GetLeft() + character.GetWidth() / 2)  - (Creat_map[gateleft][_size - 1].GetLeft() + Creat_map[gateleft][_size - 1].GetWidth());
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) -gap- (Creat_map[gateleft][_size - 1].GetTop());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					
					
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == RIGHT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetTop() + character.GetHeight() / 2) - gap < _top) {
					//RoomTop
					Xrelatity = (Creat_map[0][gateleft].GetTop()-(character.GetTop() + character.GetHeight() / 2) - gap);
					Yrelatity =  (character.GetLeft() + character.GetWidth() / 2) - (Creat_map[0][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);


					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == TOP) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}

				}
				else if ((character.GetTop() + character.GetHeight() / 2) + gap > _top+_height) {
					//RoomDown
					Xrelatity = (character.GetTop() + character.GetHeight() / 2) - gap - (Creat_map[_size-1][gateleft].GetTop()+ Creat_map[_size - 1][gateleft].GetTop());
					Yrelatity = (character.GetLeft() + character.GetWidth() / 2) - (Creat_map[_size - 1][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);


					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == DOWN) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}


			}
			//--------------------------------------------------------------------------------------------------------------------------------------
			else if (mode == RIGHT) {
				if ((character.GetLeft() + character.GetWidth() / 2) < _left) {
					//RoomLeft
					Xrelatity = (Creat_map[gateleft][0].GetLeft()) +gap-(character.GetLeft() + character.GetWidth() / 2);
					Yrelatity = (character.GetTop() + character.GetHeight() / 2)  - (Creat_map[gateleft][0].GetTop());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);


					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == LEFT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetLeft() + character.GetWidth() / 2) > _left+_width) {
					//RoomRight
					
					Xrelatity = (character.GetLeft() + character.GetWidth() / 2) +gap -(Creat_map[gateleft][_size-1].GetLeft() + Creat_map[gateleft][_size - 1].GetWidth());
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) - Creat_map[gateleft][_size - 1].GetTop();
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght-1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] ==RIGHT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetTop() + character.GetHeight() / 2) - gap < _top) {
					//RoomTop
					Xrelatity = Creat_map[0][gateleft].GetTop()-(character.GetTop() + character.GetHeight() / 2) ;
					Yrelatity =  (character.GetLeft() + character.GetWidth() / 2) + gap - (Creat_map[0][gateleft].GetLeft() );
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == TOP) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}

				}
				else if ((character.GetTop() + character.GetHeight() / 2) + gap > _top+_height) {
					//RoomDown
					Xrelatity = (character.GetTop() + character.GetHeight() / 2) - (Creat_map[_size-1][gateleft].GetTop()+ Creat_map[_size - 1][gateleft].GetHeight());
					Yrelatity =  (character.GetLeft() + character.GetWidth() / 2) + gap - (Creat_map[_size - 1][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == DOWN) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				

			}
			//--------------------------------------------------------------------------------------------------------------------------------------
			else if (mode == DOWN) {
				if ((character.GetLeft() + character.GetWidth() / 2) < _left) {
					//RoomLeft
					Xrelatity = (Creat_map[gateleft][0].GetLeft()) - (character.GetLeft() + character.GetWidth() / 2);
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) + gap - (Creat_map[gateleft][0].GetTop());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);


					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == LEFT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetLeft() + character.GetWidth() / 2) > _left+_width) {
					//RoomRight
					
					Xrelatity = (character.GetLeft() + character.GetWidth() / 2) - (Creat_map[gateleft][_size-1].GetLeft() + Creat_map[gateleft][_size-1].GetWidth());
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) +gap- Creat_map[gateleft][_size-1].GetTop();
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght-1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == RIGHT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetTop() + character.GetHeight() / 2) - gap < _top) {
					//RoomTop
					Xrelatity = Creat_map[0][gateleft].GetTop()-(character.GetTop() + character.GetHeight() / 2) + gap ;
					Yrelatity = (character.GetLeft() + character.GetWidth() / 2) - (Creat_map[0][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == TOP) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}

				}
				else if ((character.GetTop() + character.GetHeight() / 2) + gap > _top+_height) {
					//RoomDown
					//printf("test\n");
					Xrelatity = (character.GetTop() + character.GetHeight() / 2) + gap - (Creat_map[_size - 1][gateleft].GetTop()+Creat_map[_size - 1][gateleft].GetHeight());
					Yrelatity =  (character.GetLeft() + character.GetWidth() / 2) - (Creat_map[_size - 1][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == DOWN) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				

			}
			//--------------------------------------------------------------------------------------------------------------------------------------
			else if (mode == LEFT) {
				if ((character.GetLeft() + character.GetWidth() / 2) < _left) {
					//RoomLeft
					Xrelatity = (Creat_map[gateleft][0].GetLeft()) -gap- (character.GetLeft() + character.GetWidth() / 2);
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) - (Creat_map[gateleft][0].GetTop());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);

					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == LEFT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetLeft() + character.GetWidth() / 2) > _left+_width) {
					//RoomRight
					
					Xrelatity = (character.GetLeft() + character.GetWidth() / 2) - gap - (Creat_map[gateleft][_size-1].GetLeft() + Creat_map[gateleft][_size-1].GetWidth());
					Yrelatity = (character.GetTop() + character.GetHeight() / 2) - Creat_map[gateleft][_size-1].GetTop();
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght-1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == RIGHT) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}
				else if ((character.GetTop() + character.GetHeight() / 2) - gap < _top) {
					//RoomTop
					Xrelatity = (Creat_map[0][gateleft].GetTop()-(character.GetTop() + character.GetHeight() / 2) );
					Yrelatity = (character.GetLeft() + character.GetWidth() / 2)-(Creat_map[0][gateleft].GetLeft()) - gap;

					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));

					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);

					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == TOP) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}

				}
				else if ((character.GetTop() + character.GetHeight() / 2) + gap > _top+_height) {
					//RoomDown
					Xrelatity = (character.GetTop() + character.GetHeight() / 2) - (Creat_map[_size-1][gateleft].GetTop()+ Creat_map[_size - 1][gateleft].GetHeight());
					Yrelatity =  (character.GetLeft() + character.GetWidth() / 2) - gap - (Creat_map[_size - 1][gateleft].GetLeft());
					Xrelatity = round(static_cast<float>(Xrelatity / 60));
					Yrelatity = round(static_cast<float>(Yrelatity / 60));
					if (Yrelatity >= 5)
						Yrelatity = 4;
					else if (Yrelatity < 0)
						Yrelatity = 0;
					if (Xrelatity >= path_lenght)
						Xrelatity = path_lenght - 1;
					else if (Xrelatity < 0)
						Xrelatity = 0;
					//printf("X=%d,Y=%d\n", Xrelatity, Yrelatity);
					for (int place = 0; place < _gate.size(); place++) {
						if (_gate[place] == DOWN) {
							return route[place][Yrelatity][Xrelatity].is_obstacle();
						}
					}
				}

			}
			

			return false;
			
			
			
		}
		
		return false;
		
	};
	int Room::GetGateNum() {
		return _gate.size();
	}
	int Room::GetLeft() {
		return _left;
	}
	int Room::GetTop() {
		return _top;
	}
	int Room::GetWidth() {
		return _width;
	}
	int Room::GetHeight() {
		return _height;
	}
	bool Room::TF_entry() {
		int room_top = Creat_map_floor[0][0].GetTop() + Creat_map_floor[0][0].GetHeight() ;
		int room_right = Creat_map_floor[0][_size - 1].GetLeft();
		int room_down = Creat_map_floor[_size - 1][0].GetTop();
		int room_left = Creat_map_floor[0][0].GetLeft()+ Creat_map_floor[0][0].GetWidth();
		return mid_x  <= room_right && room_left <= mid_x  && mid_y >= room_top && room_down >= mid_y;
	};
	bool Room::TF_inner_room() {
		int room_top = Creat_map_floor[0][0].GetTop();
		int room_right = Creat_map_floor[0][_size - 1].GetLeft() + Creat_map_floor[0][_size - 1].GetWidth() ;
		int room_down = Creat_map_floor[_size - 1][0].GetTop() + Creat_map_floor[_size - 1][0].GetHeight();
		int room_left = Creat_map_floor[0][0].GetLeft();
		return mid_x <= room_right && room_left <= mid_x && mid_y >= room_top && room_down >= mid_y;
	};
	bool Room::TF_in_route() {
		int L,R,T,D;
		int P;
		
		for (int place = 0; place < _gate.size(); place++) {
			if (_gate[place] == TOP) {
				
				L = route_floor[place][0][0].GetLeft();
				R = route_floor[place][4][0].GetLeft() + route_floor[place][4][0].GetWidth();
				T = route_floor[place][0][path_lenght - 1].GetTop()-30;
				D = route_floor[place][0][0].GetTop()+ route_floor[place][0][0].GetHeight();
			}
			else if (_gate[place] == RIGHT) {
				
				L = route_floor[place][0][0].GetLeft();
				R = route_floor[place][0][path_lenght - 1].GetLeft() + route_floor[place][0][path_lenght - 1].GetWidth()+30;
				T = route_floor[place][0][0].GetTop() ;
				D = route_floor[place][4][0].GetTop()+route_floor[place][4][0].GetHeight();
			}
			else if(_gate[place] == LEFT){
				
				R = route_floor[place][0][0].GetLeft() + route_floor[place][0][0].GetWidth();
				L = route_floor[place][0][path_lenght - 1].GetLeft()-30;
				T = route_floor[place][0][0].GetTop() ;
				D = route_floor[place][4][0].GetTop() + route_floor[place][4][0].GetHeight();
			}
			else if (_gate[place] == DOWN) {
				
				L = route_floor[place][0][0].GetLeft() ;
				R = route_floor[place][4][0].GetLeft()+ route_floor[place][4][0].GetWidth();
				T = route_floor[place][0][0].GetTop();
				D = route_floor[place][0][path_lenght - 1].GetTop()+ route_floor[place][0][path_lenght - 1].GetHeight()+30;
			}
			if (mid_x -L>=0  && 0<=R-mid_x && mid_y-T>=0&&0 <= D-mid_y) {
				//printf("OAO\n");
				return true;
			}
		}
		return false;
	};
	bool Room::is_crash_with_bullet(CMovingBitmap bullet, int mode) {
		int Xrelatity;
		int Yrelatity;

		if (this->TF_inner_room()) {


			if (mode == TOP) {
				Xrelatity = (bullet.GetLeft() + bullet.GetWidth() / 2) - (_left);
				Yrelatity = (bullet.GetTop() + bullet.GetHeight() / 2) - (_top);


			}
			else if (mode == RIGHT) {
				Xrelatity = (bullet.GetLeft() + bullet.GetWidth() / 2)  - (_left);
				Yrelatity = (bullet.GetTop() + bullet.GetHeight() / 2) - (_top);

			}
			else if (mode == DOWN) {
				Xrelatity = (bullet.GetLeft() + bullet.GetWidth() / 2) - (_left);
				Yrelatity = (bullet.GetTop() + bullet.GetHeight() / 2)  - (_top);

			}
			else if (mode == LEFT) {
				Xrelatity = (bullet.GetLeft() + bullet.GetWidth() / 2)  - (_left);
				Yrelatity = (bullet.GetTop() + bullet.GetHeight() / 2) - (_top);

			}
			Xrelatity = round(static_cast<float>(Xrelatity / 60));
			Yrelatity = round(static_cast<float>(Yrelatity / 60));
			if (Yrelatity >= _size)
				Yrelatity = _size - 1;
			else if (Yrelatity < 0)
				Yrelatity = 0;
			if (Xrelatity >= _size)
				Xrelatity = _size - 1;
			else if (Xrelatity < 0)
				Xrelatity = 0;

			if (Creat_map[Yrelatity][Xrelatity].CanBeBroken()) {
				Creat_map[Yrelatity][Xrelatity].block_gethurt();
			}
			return Creat_map[Yrelatity][Xrelatity].is_obstacle();
		}
	}
	Monster* Room::get_which_mon(int x) { return new Monster(); };
	int Room::get_small_dis(Hero Hero){ return 1; };
	bool Room::take_is_fight_end() { return false; };
	void Room::set_Monster_place() {};
	int Room::get_Monster_num() { return 1; };
	void Room::kill_all_mon() {};

	Boss* Room::take_boss() { return new Boss(); }

	void Room::rand_boss_pos(Hero hero) {};
	void Room::delete_boss() {};
	bool Room::get_boss_delete() { return true; }
}
