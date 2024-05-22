

#pragma once
#ifndef Distrubute_h
#define Distrubute_h


#include "monster_room.h"
#include "spawn_room.h"	
#include "RandForMapObject.h"
#include "room.h"
#include "bonus_room.h"
#include "teleport_room.h"
#include "Monster.h"
#include "Bullet.h"
#include "times.h"
#include "BossRoom.h"
#include <ctime>
#include <vector>
#include "music.h"

namespace game_framework {
	class DistributeMap{
		friend Room;
	public:
		
		DistributeMap();
		~DistributeMap();
		void OAODistributeMap(vector<Room*> *room, Hero *hero, int boss);
		void ControlRoom(int MOVE,int bullet_num,Bullet *bullet);
		void ControlGate();
		void Keep_detect_interaction();
		bool TF_interaction();
		void Monster_Move(Hero *hero, int bullet_num, Bullet *bullet,times time);
		void DeleteAll();
		
		int Where_is_Hero(Hero hero);
		Monster *get_mon();
		bool is_end();
		bool* get_TF_move();
		void show_mon_bullet();

		void near_attack();
		
	private:
		CMovingBitmap WaitingForChange;
		RandForAll _randforall;
		Hero *_hero;
		vector<Room*> _room;
		bool TF_move[4] = { false,false,false,false };
		bool TF_move_route[4] = { false,false,false,false };
		
		int In_which = -1;
		int dis_map[12][12] = { 0 };
		int _roomcount;
		vector<Bullet*> mon_bullet;

		Bullet boss_bullet[24];

		bool once = false;

		bool test = false;

		music sound;
		
	};
	
	
}


#endif // !Distrubute_h