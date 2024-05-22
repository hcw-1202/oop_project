#include "stdafx.h"


#ifndef _HERO_H_
#define _HERO_H_
#include "Character.h"
#include "Gun.h"

namespace game_framework {
	class Hero:public  Character {
	public:
		Hero();
		void Hero_init(int bl, int sh, int ma);
		int get_shield();
		
		int get_mana();
		int get_speed();
		void set_maxblood(int max) { max_bl = max; }
		void set_maxshield(int max) { max_sh = max; }
		int get_maxblood() { return max_bl; }
		int get_maxshield() { return max_sh; }
		bool get_dir();
		void set_right();
		void set_left();
		void set_speed(int);
		void hurt(int damage);
		void startskill();
		bool skill();
		
		void Set_blood(int);
		void Set_mana(int);
		void add_shield();
		void is_invincible(int what);
		bool get_tf_skill();
		bool get_invincible();
		void hurt_time();
		bool isalive();
		void show();
		void TF_nearattack(bool tf) { TF_nearatt = tf; if (tf) _nearatt.ToggleAnimation(); };
		void set_skillCD(float cd) { CD = cd; };
		float get_skillCD() { return CD; }
		void set_pos(int x, int y) override;
		void GunDir(int targetx, int targety);
		clock_t get_hurt_time();
		CMovingBitmap get_deter_area();
		//Hero &operator=(const Hero&);
		

	protected:
	private:
		CMovingBitmap _nearatt;
		Gun _gun;
		int max_bl;
		int max_sh;
		float CD;
		int speed;
		int shield;
		int mana;
		bool TF_skill;
		bool isright = false;
		bool invincible = false;
		bool TF_nearatt;
		
		clock_t hurt_t;
		
	};
}
#endif // !_HERO_H_