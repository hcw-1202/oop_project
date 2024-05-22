#pragma once
#ifndef Drops_h
#define Drops_h
#include "../Library/gameutil.h"
#include "Hero.h"
#include <string>
#include "music.h"
namespace game_framework {
	enum DROP {
		RECOVERY,
		MANA,
		
	};
	class Drops {
		
	public:
		Drops()=default;
		~Drops()=default;
		int GetTop();
		int GetHeight();
		int GetLeft();
		int GetWidth();
		int Gettype();
		void Dropstype(int);
		void TF_GetDrop(Hero *,bool increase);
		void Drops_position(int, int);
		void show();
	protected:
		Hero _hero;
		int _dropstype;
		music sounds;
		CMovingBitmap _drop;
		
	};
}
#endif // !Drops_h
