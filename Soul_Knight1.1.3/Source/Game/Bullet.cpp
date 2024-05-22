#include "stdafx.h"
#include "Bullet.h"
namespace game_framework {
	Bullet::~Bullet() {
	}
	void Bullet::shoot(Hero Hero, bool isright, Monster *Monster, bool *TF) {
		count_time = 0;
		flying = true;
		use_dir = false;
		bullet_y = 0;
		bullet_x = 0;
		if (TF[2] == true) {
			bullet_y = 5; printf("up\n"); use_dir = true;
		}
		else if (TF[0] == true) {
			bullet_y = -5; printf("down\n"); use_dir = true;
		}
		if (TF[1] == true) {
			bullet_x = 5; printf("right\n"); use_dir = true;
		}
		else if (TF[3] == true) {
			bullet_x = -5; printf("left\n"); use_dir = true;
		}
		if (!use_dir) {
			for (int i = 0; i < 4; i++) bullet_flag[i] = 0;
			if (Monster->take_x() < 0) bullet_flag[0] = 1;
			if (Monster->take_x() > 0) bullet_flag[1] = 1;
			if (Monster->take_y() < 0) bullet_flag[2] = 1;
			if (Monster->take_y() > 0) bullet_flag[3] = 1;
			if (isright) bullet_flag[4] = 1;
			else bullet_flag[4] = 0;
			int temp_x = abs(Monster->take_x());
			int temp_y = abs(Monster->take_y());
			int unit = sqrt(temp_x*temp_x + temp_y * temp_y);
			if (temp_y != 0) bullet_x = (temp_x * 5) / temp_y;
			else bullet_x = 5;
			if (bullet_x >= 100) bullet_x = 10;
			bullet_y = 5;
		}
	}
	void Bullet::shoot(Hero Hero, bool isright, bool *Is_press) {
		flying = true;
		count_time = 0;
		bullet_y = 0;
		bullet_x = 0;
		use_dir = false;
		if (Is_press[2] == true) { 
			bullet_y = 5; printf("up\n"); use_dir = true; 
			Hero.GunDir(Hero.GetLeft(), Hero.GetTop() - 1);
		}
		else if (Is_press[0] == true) { 
			bullet_y = -5; printf("down\n"); use_dir = true;
			Hero.GunDir(Hero.GetLeft(), Hero.GetTop() + 1);
		}
		if (Is_press[1] == true) {
			bullet_x = 5; printf("right\n"); use_dir = true; 
			Hero.GunDir(Hero.GetLeft()+1,Hero.GetTop());
		}
		else if (Is_press[3] == true) { 
			bullet_x = -5; printf("left\n"); use_dir = true; 
			Hero.GunDir(Hero.GetLeft() - 1, Hero.GetTop());
		}
		if (Is_press[0] == false && Is_press[1] == false && Is_press[2] == false && Is_press[3] == false) {
			if (isright) bullet_x = 5;
			else bullet_x = -5;
		}
		if (isright) bullet_flag[4] = 1;
		else bullet_flag[4] = 0;
	}
	void Bullet::mon_shoot(Hero *Hero, Monster *Monster) {
		flying = true;
		use_dir = false;
		for (int i = 0; i < 4; i++) bullet_flag[i] = 0;
		if (Monster->take_x() > 0) bullet_flag[0] = 1;
		if (Monster->take_x() < 0) bullet_flag[1] = 1;
		if (Monster->take_y() > 0) bullet_flag[2] = 1;
		if (Monster->take_y() < 0) bullet_flag[3] = 1;
		int temp_x = abs(Monster->take_x());
		int temp_y = abs(Monster->take_y());
		int unit = sqrt(temp_x*temp_x + temp_y * temp_y);
		if (temp_y != 0) bullet_x = (temp_x * 5) / temp_y;
		else bullet_x = 5;
		if (bullet_x >= 100) bullet_x = 10;
		bullet_y = 5;
	}
	void Bullet::boss_shot(int dir1, int dir2, int dir3, int dir4) {
		printf("dir = %d,%d,%d,%d\n", dir1, dir2, dir3, dir4);
		flying = true;
		use_dir = false;
		for (int i = 0; i < 4; i++) bullet_flag[i] = 0;
		bullet_flag[0] = dir1;
		bullet_flag[1] = dir2;
		bullet_flag[2] = dir3;
		bullet_flag[3] = dir4;
		bullet_x = 10;
		bullet_y = 10;
	}


	bool Bullet::bullet_fly(Monster* Monster, Room *room, Hero *Hero, int type,int damage) {
		count_time += bullet_x;
		if (count_time >= 1000) {
			flying = false;
			count_time = 0;
		}

		if (use_dir) this->SetTopLeft(this->GetLeft() + bullet_x, this->GetTop() + bullet_y);

		else {
			if (this->bullet_flag[0] == 1 && Monster->is_alive()) {
				this->SetTopLeft(this->GetLeft() - bullet_x, this->GetTop());
			}
			if (this->bullet_flag[1] == 1 && Monster->is_alive()) {
				this->SetTopLeft(this->GetLeft() + bullet_x , this->GetTop());
			}
			if (this->bullet_flag[2] == 1 && Monster->is_alive()) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() - bullet_y );
			}
			if (this->bullet_flag[3] == 1 && Monster->is_alive()) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() + bullet_y );
			}
			if (this->bullet_flag[0] == 0 && this->bullet_flag[1] == 0 && this->bullet_flag[2] == 0 && this->bullet_flag[3] == 0 || !Monster->is_alive()) {
				if (this->bullet_flag[4] == 1) this->SetTopLeft(this->GetLeft() + 5, this->GetTop());
				else this->SetTopLeft(this->GetLeft() - 5, this->GetTop());
			}
		}
		if (flying) {
			if (room->is_crash_with_bullet(*this, 0)) flying = false;
			else if (Monster->is_alive() && flying && type == 0) {
				if (this->IsOverlap(*this, Monster->get_left_pic())) {//查看是否與怪物碰撞
					flying = false;
					return true;
				}
			}
			else if (type == 1 && this->IsOverlap(*this, Hero->get_left_pic())) {
				flying = false;
				Hero->hurt(damage);
			}
		}
		return false;
	}
	void Bullet::bullet_fly(Room *room, int mode) {
		count_time += 5;
		if (count_time >= 1000) {
			flying = false;
			count_time = 0;
		}
		if (use_dir) this->SetTopLeft(this->GetLeft() + bullet_x, this->GetTop() + bullet_y);
		else {
			if (this->bullet_flag[0] == 1) {
				this->SetTopLeft(this->GetLeft() - bullet_x, this->GetTop());
			}
			if (this->bullet_flag[1] == 1) {
				this->SetTopLeft(this->GetLeft() + bullet_x, this->GetTop());
			}
			if (this->bullet_flag[2] == 1) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() - bullet_y);
			}
			if (this->bullet_flag[3] == 1) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() + bullet_y);
			}
			if (this->bullet_flag[0] == 0 && this->bullet_flag[1] == 0 && this->bullet_flag[2] == 0 && this->bullet_flag[3] == 0) {
				if (this->bullet_flag[4] == 1) this->SetTopLeft(this->GetLeft() + 5, this->GetTop());
				else this->SetTopLeft(this->GetLeft() - 5, this->GetTop());
			}
		}
		if (flying) if (room->is_crash_with_bullet(*this, mode)) flying = false;
	}
	void Bullet::bullet_fly() {
		count_time += 5;
		if (count_time >= 1000) {
			flying = false;
			count_time = 0;
		}
		if (use_dir) this->SetTopLeft(this->GetLeft() + bullet_x, this->GetTop() + bullet_y);
		else {
			if (this->bullet_flag[0] == 1) {
				this->SetTopLeft(this->GetLeft() - bullet_x, this->GetTop());
			}
			if (this->bullet_flag[1] == 1) {
				this->SetTopLeft(this->GetLeft() + bullet_x, this->GetTop());
			}
			if (this->bullet_flag[2] == 1) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() - bullet_y);
			}
			if (this->bullet_flag[3] == 1) {
				this->SetTopLeft(this->GetLeft(), this->GetTop() + bullet_y);
			}
			if (this->bullet_flag[0] == 0 && this->bullet_flag[1] == 0 && this->bullet_flag[2] == 0 && this->bullet_flag[3] == 0) {
				if (this->bullet_flag[4] == 1) this->SetTopLeft(this->GetLeft() + 5, this->GetTop());
				else this->SetTopLeft(this->GetLeft() - 5, this->GetTop());
			}
		}

	}
	void Bullet::bullet_stay(int act, int sp) {
		if (act == 0) {
			this->SetTopLeft(this->GetLeft(), this->GetTop() + sp);
		}
		if (act == 1) {
			this->SetTopLeft(this->GetLeft() - sp, this->GetTop());
		}
		if (act == 2) {
			this->SetTopLeft(this->GetLeft(), this->GetTop() - sp);
		}
		if (act == 3) {
			this->SetTopLeft(this->GetLeft() + sp, this->GetTop());
		}
	}
	bool Bullet::is_flying() {
		return flying;
	}
	void Bullet::bullet_crash() {
		flying = false;
	}
	void Bullet::set_closet_mon(int x) {
		closet_mon = x;
	}
	bool Bullet::shoot_mon(Room *room, Monster *monster, Hero *Hero,int damage) {
		//if (flying) {
		if (this->bullet_fly(monster, room, Hero, 0, damage)) {
			monster->lose_blood(damage);
			monster->pause();
			return true;
		}
		//}
		return false;
	}
	void Bullet::reset_flying() {
		flying = true;
	}
}