#include "stdafx.h"
#include "../Library/gameutil.h"
#include <ctime>
#include "Monster.h"
#include "Hero.h"

#ifndef _TIMES_H_
#define _TIMES_H_




namespace game_framework {
	class times {
	public:
		times() = default;
		void hero_(Hero *Hero,clock_t invincible_end,clock_t hurt_start);
		bool add_shield_(Hero *Hero, clock_t hurt_end, clock_t hurt_start);
		void monster_(Monster *monster, clock_t monster_start, clock_t monster_stop);
		bool skillCD(Hero *Hero, clock_t skill_end, clock_t skill_start,double CD);
		bool appearfailorsuccess(clock_t start,clock_t temp);
		
	protected:
	private:
		clock_t temp;
	};
}
#endif
