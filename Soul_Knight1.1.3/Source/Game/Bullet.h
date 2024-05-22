#include "stdafx.h"
#include "../Library/gameutil.h"
#include "Monster.h"
#include "room.h"
#ifndef _BULLET_H_
#define _BULLET_H_


namespace game_framework {
	class Bullet :public CMovingBitmap {
	public:
		Bullet() = default;
		~Bullet();
		void shoot(Hero Hero,bool isright, Monster *Monster, bool *TF);
		void mon_shoot(Hero *Hero, Monster *Monster);
		void boss_shot(int dir1, int dir2, int dir3, int dir4);
		void shoot(Hero Hero, bool isright, bool *Is_press);
		bool bullet_fly(Monster* Monster,Room* room,Hero *Hero,int type,int damage);
		void bullet_fly(Room *room, int mode);
		void bullet_fly();
		void bullet_stay(int act, int sp);
		bool is_flying();
		void bullet_crash();
		void set_closet_mon(int x);
		bool shoot_mon(Room *room, Monster *monster,Hero *Hero,int damage);
		void reset_flying();

	protected:
	private:
		bool flying = false;
		int bullet_flag[5] = { 0,0,0,0,0 };
		int closet_mon;
		int bullet_x;
		int bullet_y;
		int count_time;
		bool use_dir = false;
	};
}
#endif // !_BULLET_H_