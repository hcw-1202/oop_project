#include "stdafx.h"
#include "../Library/gameutil.h"
#ifndef _CHARACTER_H_
#define _CHARACTER_H_


namespace game_framework {
	
	class Character{
	public:
		Character();
		int get_blood();
		void set_right_pic(int who);
		void set_left_pic(int who);
		virtual void set_pos(int x, int y);
		int GetLeft();
		int GetTop();
		int GetHeight();
		int GetWidth();

		virtual void anime(bool,int);
		virtual void TF_startanime(bool);
		CMovingBitmap get_right_pic();
		CMovingBitmap get_left_pic();
		Character operator=(const Character&);
		int Get_type();
		void set_power(int p);
		int get_power();
	protected:
		int type;
		bool TF_anime;
		CMovingBitmap _deter;
		CMovingBitmap right;
		CMovingBitmap left;
		int blood;
		int _left;
		int _top;
		int power;
	private:
		
	};
}
#endif // !_CHARACTER_H_