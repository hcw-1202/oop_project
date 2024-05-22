#pragma once
#include "../Library/gameutil.h"
#include "EnumLibrary.h"
namespace game_framework {
	
	struct GunData {
		GunType type;
		int freq;
		int speed;
		int damage;

	};
	class Gun {
	public:
		Gun()=default;
		~Gun()=default;
		void Set_Gun(GunType type, int freq, int speed, int damage) {
			_data.type = type;
			_data.freq = freq;
			_data.speed = speed;
			_data.damage = damage;
			
			if(type==P2020)
				_gun.LoadBitmapByString({"resources/old_pistol_0.bmp","resources/old_pistol_45.bmp","resources/old_pistol_90.bmp","resources/old_pistol_135.bmp","resources/old_pistol_180.bmp","resources/old_pistol_225.bmp","resources/old_pistol_270.bmp", "resources/old_pistol_315.bmp" }, RGB(255, 255, 255));
			//_gun.SetFrameIndexOfBitmap(2);
		};
		void Set_Gun_Place(int x, int y) {
			_gun.SetTopLeft(x,y);
		};
		void Set_Gun_dir(int heroX, int heroY, int targetX, int targetY) {
			int dx = targetX - heroX;
			int dy = targetY - heroY;
			//float theta = atan(static_cast<float>(dy / dx));
			if (dx == 0) {
				if (dy == 1) {
					
					_gun.SetFrameIndexOfBitmap(2);					
				}
				else if (dy == -1) {
					_gun.SetFrameIndexOfBitmap(5);
					
				}
			}
			printf("gunindex=%d\n", _gun.GetFrameIndexOfBitmap());
			//printf("dx=%d,dy=%d\n", dx, dy);
			//printf("theta=%f\n", theta);
		};
		void show() {
			//printf("gunindex=%d\n", _gun.GetFrameIndexOfBitmap());
			
			_gun.ShowBitmap();
		};
		GunData GetGunDate(){
			return _data;
		}
		
		
	protected:
		CMovingBitmap _gun;
		GunData _data;
		int _bullet_type[5][5];
			
	};
}