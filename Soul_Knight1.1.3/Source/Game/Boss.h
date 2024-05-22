#include "stdafx.h"
#include "../Library/gameutil.h"

#ifndef _BOSS_H_
#define _BOSS_H_
#include "Monster.h"
#include "Hero.h"
#include <time.h>

namespace game_framework {
	class Boss :public Monster {
	public:
		Boss() = default;
		void set_init();
		bool check_is_shot_end();
		void set_phase(int x);
		void set_time();
		bool get_phase(int x);
		clock_t get_time();
		void show_boss();
		void set_boss_loading(int type);
		bool get_boss_loading();

		void set_xy(int x, int y);
		int get_boss_x();
		int get_boss_y();
		void set_stop(int x);
		bool get_stopping();

	protected:
		bool phase1 = false;
		bool phase2 = false;
		bool phase3 = false;
		clock_t phase_time;
		bool boss_loading;

		bool is_running;
		int boss_x, boss_y;
		bool stopping;
	private:
	};
}
#endif