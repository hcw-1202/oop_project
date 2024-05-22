#include "stdafx.h"
#include "Monster.h"
namespace game_framework {
	Monster::Monster() {
		notice.LoadBitmapByString({ "resources/notice.bmp" }, RGB(255, 255, 255));
		inrange = false;
	}
	void Monster::stay(int act, int speed) {

		if (act == 0) {
			this->set_pos(this->get_right_pic().GetLeft(), this->get_right_pic().GetTop() + speed);
		}
		if (act == 1 ) {
			this->set_pos(this->get_right_pic().GetLeft() - speed, this->get_right_pic().GetTop());
		}
		if (act == 2 ) {
			this->set_pos(this->get_right_pic().GetLeft(), this->get_right_pic().GetTop() - speed);
		}
		if (act == 3) {
			this->set_pos(this->get_right_pic().GetLeft() + speed, this->get_right_pic().GetTop());
		}
	}
	void Monster::set_blood(int bl) {
		blood = bl;
	}
	bool Monster::detect_range(CMovingBitmap Hero) {
		if (this->get_right_pic().GetTop() - 100 <= Hero.GetTop() && this->get_right_pic().GetTop() + 100 >= Hero.GetTop()) {
			if (this->get_right_pic().GetLeft() - 100 <= Hero.GetLeft() && this->get_right_pic().GetLeft() + 100 >= Hero.GetLeft()) {
				return true;
			}
		}
		else
			return false;
	}
	bool Monster::detect_shoot(CMovingBitmap Hero) {
		if (this->get_right_pic().GetTop() - 500 <= Hero.GetTop() && this->get_right_pic().GetTop() + 500 >= Hero.GetTop()) {
			if (this->get_right_pic().GetLeft() - 500 <= Hero.GetLeft() && this->get_right_pic().GetLeft() + 500 >= Hero.GetLeft()) {
				return true;
			}
		}
		else
			return false;
	}
	bool Monster::is_alive() {
		if (!alive) {
			if (!this->get_dir()) {
				/*printf("right=%d\n", right.GetFrameIndexOfBitmap());*/
				if(this->Get_type()==1)
					right.SetFrameIndexOfBitmap(right.GetFrameSizeOfBitmap() - 1);
				else if(this->Get_type()==2)
					right.SetFrameIndexOfBitmap(4);
			}
			else {
				/*printf("left=%d\n", left.GetFrameIndexOfBitmap());*/
				if (this->Get_type() == 1)
					left.SetFrameIndexOfBitmap(left.GetFrameSizeOfBitmap() - 1);
				else if (this->Get_type() == 2)
					left.SetFrameIndexOfBitmap(4);
			}
		}
		
		return alive;
	}
	void Monster::lose_blood(int damage) {
		blood -= damage;
		if (blood <= 0) alive = false;
	}
	void Monster::stay() {
		this->set_pos(this->get_left_pic().GetLeft(), this->get_left_pic().GetTop());
	}
	void Monster::pause() {
		stop = true;
	}
	void Monster::start_move() {
		stop = false;
	}
	bool Monster::get_isstop() {
		return stop;
	}
	bool* Monster::detect(Hero * Hero) {
		bool temp[2] = {false,false};
		if (this->detect_range(Hero->get_deter_area()) && this->is_alive()) {
			if (!this->get_isstop()) temp[0] = true;//this->toward_hero(Hero->get_left_pic());
			if (this->get_left_pic().IsOverlap(this->get_left_pic(), Hero->get_left_pic()) && !Hero->get_invincible()) {
				Hero->hurt(power);
				Hero->is_invincible(0); //¶i¤JµL¼Ä
				Hero->hurt_time();
				temp[1] = true;
				return temp;
			}
		}
		temp[1] = false;
		return temp;
	}
	void Monster::set_range(Hero Hero) {
		x_range = this->GetLeft() - Hero.GetLeft();
		y_range = this->GetTop() - Hero.GetTop();
		distance = sqrt(x_range * x_range + y_range * y_range);
	}
	int Monster::take_x() {
		return x_range;
	}
	int Monster::take_y() {
		return y_range;
	}
	int Monster::take_dis() {
		return distance;
	}
	void Monster::hurt_time() {
		hurt = clock();
	}
	clock_t Monster::get_hurt_time() {
		return hurt;
	}
	void Monster::set_right() {
		dir = false;
	}
	void Monster::set_left() {
		dir = true;
	}
	bool Monster::get_dir() {
		return dir;
	}
	void Monster::is_crush_block() {
		crush_block = true;
	}
	bool Monster::get_crush_block() {
		return crush_block;
	}
	void Monster::reset_crush_block() {
		crush_block = false;
	}
	void Monster::set_loading() {
		loading = true;
		shot = clock();
	}
	bool Monster::is_loading() {
		return loading;
	}
	void Monster::reset_loading() {
		loading = false;
	}
	clock_t Monster::get_shot_time() {
		return shot;
	}
	void Monster::show() {
		if (!this->get_dir()) {
			//printf("right=%d\n", right.GetFrameIndexOfBitmap());
			right.ShowBitmap();
		}
		else {
			//printf("left=%d\n", left.GetFrameIndexOfBitmap());
			left.ShowBitmap();
		}
	}
	void Monster::anime(bool TF, int dirx) {


		
		if (Get_type() == 1) {
			if (TF) {
				if (dirx==1) {
					
					if (right.GetFrameIndexOfBitmap() <= 1) {
						right.SetFrameIndexOfBitmap(2);
					}
					right.SetFrameIndexOfBitmap(right.GetFrameIndexOfBitmap() % (right.GetFrameSizeOfBitmap() - 1));
				}
				else {
					if (left.GetFrameIndexOfBitmap() <= 1)
						left.SetFrameIndexOfBitmap(2);
					left.SetFrameIndexOfBitmap(left.GetFrameIndexOfBitmap() % (left.GetFrameSizeOfBitmap() -1));
				}
			}
			else {
				
				if (dirx == 1) {
					right.SetFrameIndexOfBitmap((right.GetFrameIndexOfBitmap()) % 2);
				}
				else {
					left.SetFrameIndexOfBitmap((left.GetFrameIndexOfBitmap()) % 2);
				}
					
			}
		}
		else if(Get_type() == 2){
			if (TF) {
				if (dirx == 1) {

					if (right.GetFrameIndexOfBitmap() <=3 ) {
						right.SetFrameIndexOfBitmap(5);
					}
					right.SetFrameIndexOfBitmap(right.GetFrameIndexOfBitmap() % (right.GetFrameSizeOfBitmap() - 1));
				}
				else {
					if (left.GetFrameIndexOfBitmap() <= 3)
						left.SetFrameIndexOfBitmap(5);
					left.SetFrameIndexOfBitmap(left.GetFrameIndexOfBitmap() % (left.GetFrameSizeOfBitmap() - 1));
				}
			}
			else {

				if (dirx == 1) {
					//printf("test\n");
					right.SetFrameIndexOfBitmap((right.GetFrameIndexOfBitmap()) % 3);
				}
				else {
					left.SetFrameIndexOfBitmap((left.GetFrameIndexOfBitmap()) % 3);
				}

			}
		}
			
			
		




	}
	void Monster::kill() {
		blood == 0;
		alive = false;
	}

	void Monster::set_speed(int sp) {
		speed = sp;
	}

	int Monster::get_speed() {
		return speed;
	}
	CMovingBitmap *Monster::show_notice() {
		return &notice;
	}
	bool Monster::get_inrange() {
		return inrange;
	}
}