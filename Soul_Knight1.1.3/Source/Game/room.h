#include "stdafx.h"


#ifndef _ROOM_H_
#define _ROOM_H_
#include"Block.h"
#include "Hero.h"
#include "Drops.h"
#include "Monster.h"
#include "../Library/gameutil.h"
#include <map>
#include "ReadCSV.h"
#include "Boss.h"
#include "HeroSkill.h"
#include "EnumLibrary.h"
namespace game_framework {
	
	
	
	
	class Room{
		
	public:
		static HeroSkill Hero_talent;
		Room()=default;
		Room(int size,Hero *hero);
		virtual ~Room();

		virtual void Move_room(int room_move);
		
		virtual void show();
		virtual bool TF_interaction();
		virtual void Keep_detect_interact();
		virtual void Gate(blocktype) = 0;
		
		void Set_gate(vector<POSITION_OAO>);
		void Set_route();
		virtual void Set_position(int, int);//left top
		
		void RefreshMapXY();
		void Now_Level(int);
		ROOMTYPE Get_roomtype();
	
		int GetLeft();
		int GetTop();
		int GetWidth();
		int GetHeight();
		int GetGateNum();
		
		bool Is_crash(Character, int, bool);
		bool TF_entry();
		bool TF_inner_room();
		bool TF_in_route();
		bool is_crash_with_bullet(CMovingBitmap bullet, int mode);
		
		virtual Monster* get_which_mon(int x);
		virtual int get_small_dis(Hero Hero);
		virtual bool take_is_fight_end();
		virtual void set_Monster_place();
		virtual int get_Monster_num();
		virtual void kill_all_mon();

		virtual Boss* take_boss();
		virtual void rand_boss_pos(Hero hero);
		virtual void delete_boss();
		virtual bool get_boss_delete();
		
		

		
	protected:
		//Block **Creat_map;
		//Block ** Creat_map_floor;
		vector<vector<Block>> Creat_map;
		vector<vector<Block>> Creat_map_floor;
		vector<Block> route[4][5];
		vector<Block> route_floor[4][5];
		vector<vector<int>> _obstacle_type;
		ROOMTYPE _type;
		times _clk;
		Hero *_hero;
		
		vector<POSITION_OAO> _gate;
		
		int gap;
		int mid_x;
		int mid_y;
		int _left=0;
		int _top=0;
		int _width;
		int _height;
		int _size;
		bool gate_close;
		int gateleft;
		int gateright;
		int path_lenght;
		int _Level;
		int TF_avoid_trap;
		int _movemode;
	private:
		
		

		
		
	};
	
}

#endif
	
	
	




