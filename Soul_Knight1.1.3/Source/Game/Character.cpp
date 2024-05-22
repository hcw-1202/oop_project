#include "stdafx.h"
#include "Character.h"
namespace game_framework {
	Character::Character() {
		
	}
	int Character::get_blood() {
		return blood;
	}
	void Character::set_right_pic(int who) {
		if (who == 0) {
			right.LoadBitmapByString({ "Resources/2-1.bmp","Resources/2-2.bmp","Resources/2-3.bmp","Resources/2-4.bmp", "Resources/2-5.bmp","Resources/2-6.bmp","Resources/2-7.bmp","Resources/2-8.bmp" , "Resources/2-9.bmp","Resources/2-10.bmp","Resources/2-11.bmp","Resources/2-12.bmp" , "Resources/2-13.bmp","Resources/2-14.bmp","Resources/2-15.bmp","Resources/2-16.bmp", "Resources/2-17.bmp","Resources/1-1.bmp","Resources/1-2.bmp","Resources/1-3.bmp","Resources/1-4.bmp" }, RGB(255, 255, 255));
			right.SetAnimation(150, false);
			type = 0;
		}
		else if (who == 1) { //½Þ½Þ
			printf("pig\n");
			right.LoadBitmapByString({ "resources/boar_stand_1_right.bmp","resources/boar_stand_2_right.bmp","resources/boar_move_1_right.bmp","resources/boar_move_2_right.bmp","resources/boar_dead_right.bmp" }, RGB(255, 255, 255));
			right.SetAnimation(300, false);
			type = 1;
		}
		else if(who == 2){
			right.LoadBitmapByString({ "Resources/goblin_stand_1_right.bmp","Resources/goblin_stand_2_right.bmp", "Resources/goblin_stand_3_right.bmp","Resources/goblin_stand_4_right.bmp","Resources/goblin_dead_right.bmp", "Resources/goblin_move_1_right.bmp","Resources/goblin_move_2_right.bmp","Resources/goblin_move_3_right.bmp" }, RGB(255, 255, 255));
			right.SetAnimation(500, false);
			type = 2;
		}
		else if (who == 3) {
			//phase2 mon
		}
		else if (who == 100) { //boss
			right.LoadBitmapByString({ "resources/bossr1.bmp" }, RGB(255, 255, 255));
			type = 100;
			printf("type = %d\n", type);
		}
		else if(who == 200){
			right.LoadBitmapByString({ "resources/boss_pig.bmp" }, RGB(255, 255, 255));
			type = 200;
			printf("type = %d\n", type);
		}
	}
	void Character::anime(bool TF,int dir) {
		
		
		if (TF_anime) {
			if (TF) {
				if (dir == 1) {

					if (right.GetFrameIndexOfBitmap() <= 7)
						right.SetFrameIndexOfBitmap(8);
					right.SetAnimation(150, false);
					right.SetFrameIndexOfBitmap(right.GetFrameIndexOfBitmap() % (right.GetFrameSizeOfBitmap() - 6));

					//printf("OAOright=%d\n", right.GetFrameIndexOfBitmap());
				}
				else {
					if (left.GetFrameIndexOfBitmap() <= 7)
						left.SetFrameIndexOfBitmap(8);
					left.SetAnimation(150, false);
					left.SetFrameIndexOfBitmap(left.GetFrameIndexOfBitmap() % (left.GetFrameSizeOfBitmap() - 6));
					//printf("OAOleft=%d\n", left.GetFrameIndexOfBitmap());
				}


			}
			else {
				if (dir == 1)
					right.SetFrameIndexOfBitmap(((right.GetFrameIndexOfBitmap()) % 7));
				else
					left.SetFrameIndexOfBitmap(((left.GetFrameIndexOfBitmap()) % 7));


			}
		}
		
	
		
		
	}
	void Character::TF_startanime(bool TF) {
		TF_anime = TF;
	}
	void Character::set_left_pic(int who) {
		if (who == 0) {
			left.LoadBitmapByString({ "Resources/005.bmp","Resources/006.bmp","Resources/007.bmp","Resources/008.bmp","Resources/009.bmp","Resources/010.bmp","Resources/011.bmp","Resources/012.bmp","Resources/013.bmp","Resources/014.bmp","Resources/015.bmp","Resources/016.bmp", "Resources/017.bmp","Resources/018.bmp","Resources/019.bmp","Resources/020.bmp","Resources/021.bmp", "Resources/001.bmp","Resources/002.bmp","Resources/003.bmp","Resources/004.bmp" }, RGB(255, 255, 255));
			left.SetAnimation(150, false);
		}
		else if (who == 1) {
			left.LoadBitmapByString({ "resources/boar_stand_1_left.bmp","resources/boar_stand_2_left.bmp","resources/boar_move_1_left.bmp","resources/boar_move_2_left.bmp","resources/boar_dead_left.bmp" }, RGB(255, 255, 255));
			left.SetAnimation(300, false);
		}
		else if (who == 2) {
			left.LoadBitmapByString({ "Resources/goblin_stand_1_left.bmp","Resources/goblin_stand_2_left.bmp","Resources/goblin_stand_3_left.bmp","Resources/goblin_stand_4_left.bmp","Resources/goblin_dead_left.bmp", "Resources/goblin_move_1_left.bmp","Resources/goblin_move_2_left.bmp","Resources/goblin_move_3_left.bmp","Resources/goblin_move_4_left.bmp" }, RGB(255, 255, 255));
			left.SetAnimation(300, false);
		}
		else if (who == 3) {
			//phase2 mon
		}
		else if (who == 100) {
			printf("hellloooooo\n");
			left.LoadBitmapByString({ "resources/bossl.bmp" }, RGB(255, 255, 255));
		}
		else if (who == 200) {
			printf("hellloooooo\n");
			left.LoadBitmapByString({ "resources/boss_pig.bmp" }, RGB(255, 255, 255));
		}
	}
	void Character::set_pos(int x, int y) {
		_left = x;
		_top = y;
		left.SetTopLeft(x, y);
		right.SetTopLeft(x, y);
		if(_deter.IsBitmapLoaded())
			_deter.SetTopLeft(x, y+this->GetHeight()/2);
	}
	int Character::GetLeft() {
		
		return right.GetLeft();
	}
	int Character::GetTop(){
		return right.GetTop();
	}
	int Character::GetHeight() {
		return right.GetHeight();
	}
	int Character::GetWidth() {
		return right.GetWidth();
	}
	
	CMovingBitmap Character::get_right_pic() {
		return right;
	}
	CMovingBitmap Character::get_left_pic() {
		return left;
	}
	Character Character::operator=(const Character &chr) {
		this->blood = chr.blood;
		this->left = chr.left;
		this->right = chr.right;
		this->set_pos(chr._left, chr._top);

		return *this;
	}
	int Character::Get_type() {
		return type;
	}
	void Character::set_power(int p) {
		power = p;
	}
	int Character::get_power() {
		return power;
	}
}