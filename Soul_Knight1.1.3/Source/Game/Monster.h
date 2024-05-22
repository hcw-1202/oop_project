#include "stdafx.h"
#include "Character.h"
#include <windows.h>
#include "Hero.h"
#ifndef _MONSTER_H_
#define _MONSTER_H_


namespace game_framework {
	class Monster :public  Character {
	public:
		Monster();
		~Monster() = default;
		void set_blood(int bl);
		void stay(int act, int sp);
		void stay();
		bool detect_range(CMovingBitmap Hero);
		bool detect_shoot(CMovingBitmap Hero);
		bool is_alive();
		void lose_blood(int damage);
		void pause();
		void start_move();
		bool get_isstop();
		bool* detect(Hero * Hero);
		void set_range(Hero Hero);
		int take_x();
		int take_y();
		int take_dis();
		void hurt_time();
		clock_t get_hurt_time();
		void set_right();
		void set_left();
		bool get_dir();
		void is_crush_block();
		bool get_crush_block();
		void reset_crush_block();
		void set_loading();
		bool is_loading();
		void reset_loading();
		void show();
		void anime(bool,int) override;
		clock_t get_shot_time();
		void kill();
		void set_speed(int sp);
		int get_speed();
		CMovingBitmap *show_notice();
		bool get_inrange();

	protected:
		bool alive = true;
		bool stop = false;
		int x_range;
		int y_range;
		int distance;
		clock_t hurt;
		bool dir = true;
		bool crush_block = false;
		bool loading = false;
		clock_t shot;
		int speed;
		CMovingBitmap notice;
		bool inrange;
	private:
		
	};
}
#endif // !_MONSTER_H_