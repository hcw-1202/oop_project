#include "stdafx.h"
#include "times.h"
namespace game_framework {
	void times::hero_(Hero *Hero, clock_t invincible_end, clock_t hurt_start) {
		if ((invincible_end - hurt_start) / (double)(CLOCKS_PER_SEC) >= 0.8 && !Hero->get_tf_skill())  Hero->is_invincible(1);
	}
	bool times::add_shield_(Hero *Hero, clock_t hurt_end, clock_t hurt_start) {
		if ((hurt_end - hurt_start) / (double)(CLOCKS_PER_SEC) >= 4.0) {
			if (Hero->get_shield() < Hero->get_maxshield()) {
				Hero->add_shield();
				return true;
			}
		}
		return false;
	}
	void times::monster_(Monster *monster, clock_t monster_start, clock_t monster_stop) {
		if ((monster_start - monster_stop) / (double)(CLOCKS_PER_SEC) >= 0.5) {
			monster->start_move();
		}
	}
	bool times::skillCD(Hero *Hero, clock_t skill_end, clock_t skill_start,double CD) {
		if ((skill_end - skill_start) / (double)(CLOCKS_PER_SEC) >= CD) {
			return true;
		}
		return false;
	}
	bool times::appearfailorsuccess(clock_t start,clock_t temp) {
		if ((start - temp) / double(CLOCKS_PER_SEC) >= 2.0) {
			return true;
		}
		return false;
	}
}