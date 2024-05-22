#pragma once
#ifndef  HeroState_H
#define HeroState_H
#include "../Library/gameutil.h"
namespace game_framework {
	class HeroState {
	public:
		HeroState() = default;
		void SetHeroState() {
			
			_board.LoadBitmapByString({ "resources/stateboard.bmp" });
			_board.SetTopLeft(0, 0);
			
			_blood.LoadBitmapByString({ "resources/chest_ignore.bmp","resources/blood_1.bmp","resources/blood_2.bmp","resources/blood_3.bmp","resources/blood_4.bmp","resources/blood_5.bmp","resources/blood_6.bmp","resources/blood_7.bmp","resources/blood_8.bmp","resources/blood_9.bmp","resources/blood_10.bmp","resources/blood_11.bmp","resources/blood_12.bmp","resources/blood_13.bmp","resources/blood_14.bmp","resources/blood_15.bmp" },RGB(255,255,255));
			_blood.SetTopLeft(40, 12);
			_blood.SetFrameIndexOfBitmap(15);
			_shield.LoadBitmapByString({ "resources/chest_ignore.bmp","resources/shield_1.bmp","resources/shield_2.bmp","resources/shield_3.bmp","resources/shield_4.bmp","resources/shield_5.bmp","resources/shield_6.bmp","resources/shield_7.bmp","resources/shield_8.bmp","resources/shield_9.bmp","resources/shield_10.bmp","resources/shield_11.bmp","resources/shield_12.bmp","resources/shield_13.bmp","resources/shield_14.bmp","resources/shield_15.bmp" }, RGB(255, 255, 255));
			_shield.SetTopLeft(40, 34);
			_blood.SetFrameIndexOfBitmap(15);
			_mana.LoadBitmapByString({ "resources/chest_ignore.bmp","resources/mana_1.bmp","resources/mana_2.bmp","resources/mana_3.bmp","resources/mana_4.bmp","resources/mana_5.bmp","resources/mana_6.bmp","resources/mana_7.bmp","resources/mana_8.bmp","resources/mana_9.bmp","resources/mana_10.bmp","resources/mana_11.bmp","resources/mana_12.bmp","resources/mana_13.bmp","resources/mana_14.bmp","resources/mana_15.bmp" }, RGB(255, 255, 255));
			_mana.SetTopLeft(40, 60);
		}
		~HeroState() {};
		void SetValue(Hero &hero) {
			if (hero.get_blood() > hero.get_maxblood())
				_blood.SetFrameIndexOfBitmap(15);
			else
				_blood.SetFrameIndexOfBitmap((15* hero.get_blood())/hero.get_maxblood());
			_shield.SetFrameIndexOfBitmap((15 * hero.get_shield()) / hero.get_maxshield());
			_mana.SetFrameIndexOfBitmap(15);
		};
		void show() {
			_board.ShowBitmap();
			_blood.ShowBitmap();
			_shield.ShowBitmap();
			_mana.ShowBitmap();
		};
	private:
		CMovingBitmap _board;
		CMovingBitmap _blood;
		CMovingBitmap _shield;
		CMovingBitmap _mana;
	};
}
#endif // ! HeroState_H
