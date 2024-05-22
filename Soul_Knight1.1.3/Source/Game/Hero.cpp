
#include "stdafx.h"
#include "Hero.h"
namespace game_framework {
	Hero::Hero() {
		
	}
	void Hero::Hero_init(int bl, int sh, int ma) {
		_gun.Set_Gun(P2020,10,5,1);
		max_bl = bl;
		max_sh = sh;
		blood = bl;
		shield = sh;
		mana = ma;
		TF_nearatt = false;
		_deter.LoadBitmapByString({ "resources/deter.bmp" }, RGB(255, 255, 255));
		_nearatt.LoadBitmapByString({ "resources/nearattack_1.bmp","resources/nearattack_2.bmp","resources/nearattack_3.bmp","resources/nearattack_4.bmp" }, RGB(255, 255, 255));
		_nearatt.SetAnimation(100,false);
	}
	int Hero::get_mana() {
		return mana;
	}
	int Hero::get_shield() {
		return shield;
	}
	int Hero::get_speed() {
		return speed;
	}
	void Hero::set_speed(int sp) {
		speed = sp;
	}
	bool Hero::get_dir() {
		return isright;
	}
	void Hero::Set_blood(int bl) {
		blood = bl;
	}
	void Hero::Set_mana(int ma) {
		mana = ma;
	}
	void Hero::set_right() {
		isright = true;
	}
	void Hero::set_left() {
		isright = false;
	}

	void Hero::hurt(int damage) {
		//printf("shield = %d, damage = %d,", shield, damage);
		
		if (shield - damage >= 0) {
			//printf("sit1,");
			shield -= damage;
			
		}
		else if (shield - damage < 0) {
			//printf("sit2,");
			damage = damage - shield;
			shield = 0;
			blood = blood - damage;
		}

		if (blood < 0)
			blood = 0;

	}
	void Hero::set_pos(int x, int y) {
		
		_left = x;
		_top = y;
		left.SetTopLeft(x, y);
		right.SetTopLeft(x, y);
		_gun.Set_Gun_Place(x, y);
		_nearatt.SetTopLeft(x,y);
		if (_deter.IsBitmapLoaded())
			_deter.SetTopLeft(x, y + this->GetHeight() / 2);
	}
	void Hero::GunDir(int targetx, int targety) {
		_gun.Set_Gun_dir(_left, _top, targetx, targety);
	}
	
	bool Hero::isalive() {
		if (blood == 0) {
			if (this->get_dir()) {
				//printf("right\n");
				right.SetFrameIndexOfBitmap(right.GetFrameSizeOfBitmap()-5);
			}
			else {
				//printf("left\n");
				left.SetFrameIndexOfBitmap(right.GetFrameSizeOfBitmap() - 5);
			}
			return false;
		}
		return true;
	}
	void Hero::add_shield() {
		shield += 1;
	}
	void Hero::is_invincible(int what) {
		//printf("%d invincible\n", what);
		if(what == 0) invincible = true;
		else invincible = false;
	}
	bool Hero::get_invincible() {
		return invincible;
	}
	bool Hero::get_tf_skill() {
		return TF_skill;
	}
	
	void Hero::hurt_time() {
		hurt_t = clock();
	}
	clock_t Hero::get_hurt_time() {
		return hurt_t;
	}
	
	void Hero::show() {
		
		if (this->get_dir()) {
			//printf("right\n");
			right.ShowBitmap();
			
			//_gun.show();
		}
		else {
			//printf("left\n");
			left.ShowBitmap();
			
			//_gun.show();
		}
		if(TF_nearatt)
			_nearatt.ShowBitmap();
		
		
	};

	void Hero::startskill() {
		TF_anime = false;
		if (this->get_dir() == 1) {
			
			right.ToggleAnimation();
			right.SetFrameIndexOfBitmap(right.GetFrameSizeOfBitmap() - 4);
			
			printf("start\n");
		}
		else {
			left.ToggleAnimation();
			left.SetFrameIndexOfBitmap(right.GetFrameSizeOfBitmap() - 4);
			
			printf("start\n");
		}
	}
	bool Hero::skill() {
		
		
		
		if (this->get_dir() == 1) {
			TF_anime = false;
			right.SetAnimation(100, true);


			TF_skill = !right.IsAnimationDone();


			return TF_skill;

		}
		else {
			TF_anime = false;
			left.SetAnimation(100, true);

			TF_skill = !left.IsAnimationDone();


			return TF_skill;
		}		
	}
	CMovingBitmap Hero::get_deter_area() {
		return _deter;
	}
}