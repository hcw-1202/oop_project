#include "stdafx.h"
#include "Drops.h"
namespace game_framework {
	
	void Drops::Dropstype(int drop) {
		_dropstype = drop;
		CMovingBitmap temp;
		if (drop == RECOVERY) {
			if (_drop.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/recovery.bmp" },RGB(255,255,255));
				temp.SetTopLeft(_drop.GetLeft(), _drop.GetTop());
				
				_drop = temp;
				
			}
			else {
				_drop.LoadBitmapByString({ "resources/recovery.bmp" },RGB(255,255,255));
			}
			

		}
		else if (drop == MANA) {
			if (_drop.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/chest_ignore.bmp" });
				temp.SetTopLeft(_drop.GetLeft(), _drop.GetTop());
				_drop = temp;
			}
			else {
				_drop.LoadBitmapByString({ "resources/chest_ignore.bmp" });
			}
		}
		else {
			printf("dis\n");
			if (_drop.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
				temp.SetTopLeft(_drop.GetLeft(), _drop.GetTop());
				_drop = temp;
			}
			else {
				_drop.LoadBitmapByString({ "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
			}
			
		}
	}
	void Drops::Drops_position(int x, int y) {
		_drop.SetTopLeft(x, y);
	}
	void Drops::TF_GetDrop(Hero *hero, bool increase) {
		
		
			if (_dropstype == RECOVERY) {
				if (hero->get_left_pic().IsOverlap(hero->get_left_pic(), _drop) || hero->get_right_pic().IsOverlap(hero->get_right_pic(), _drop)) {
					printf("GetDrop!!\n");
					this->Dropstype(-1);
					if (hero->get_blood() < hero->get_maxblood()) {
						sounds.play_what(11, false);
						if (hero->get_maxblood() - hero->get_blood() == 1)
							hero->Set_blood(hero->get_maxblood());
						else {
							
							if(increase)
								hero->Set_blood(hero->get_blood() + 2);
							else
								hero->Set_blood(hero->get_blood() + 1);
						}

					}
				}
			}
			else if (_dropstype == MANA) {
				hero->Set_mana(hero->get_mana()+10);
			}
		
		
	}
	int Drops::GetTop() {
		return _drop.GetTop();
	}
	int Drops::GetHeight() {
		return _drop.GetHeight();
	}
	int Drops::GetWidth() {
		return _drop.GetHeight();
	}
	int Drops::GetLeft() {
		return _drop.GetLeft();
	}
	int Drops::Gettype() {
		return _dropstype;
	}
	void Drops::show() {
		_drop.ShowBitmap();
	}
}