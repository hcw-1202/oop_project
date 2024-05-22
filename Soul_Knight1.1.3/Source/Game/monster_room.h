#ifndef MONSTER_H
#define MONSTER_H

#include "room.h"
#include "Monster.h"
#include "Bullet.h"
#include "RandForMapObject.h"
namespace game_framework {
	class MonsterRoom :public Room {
	public:
		MonsterRoom(int size, Hero *,int quantity,int speed,int power) ;
		~MonsterRoom() override;
		
		void Gate(blocktype) override;
		
		bool TF_interaction() override;
		void show() override;

		Monster* get_which_mon(int x) override;
		int get_small_dis(Hero Hero) override;
		bool take_is_fight_end() override;
		void set_Monster_place() override;
		int get_Monster_num() override;
		void kill_all_mon() override;
		void Keep_detect_interact() override;
	private:
		RandForAll _randforall;
		ReturnXY _chest;
		ReturnXY _Monst;
		vector<Monster*> monster;
		CMovingBitmap pass;
		clock_t t;
		music sounds;
		bool is_defeat;
		bool _trigger;
		bool _trigger2;
		int _monster_quantity;
	};
}
#endif