#ifndef BLOCK
#define BLOCK
#include "../Library/gameutil.h"
#include <string>
#include "Character.h"
#include "Drops.h"
#include "times.h"
#include "EnumLibrary.h"
#include <ctime>
#include "music.h"
namespace game_framework {
	

	class Block{
	public:
		Block()=default;
		~Block() = default;
		void blocktype(int type);
		bool is_obstacle();
		int GetTop();
		int GetHeight();
		int GetLeft();
		int GetWidth();
		int Gettype();
		bool CanBeBroken();
		bool TF_ContainPosition();
		void starttrap(Hero *hero,bool avoid);
		
		void GetDrop(Hero *,bool increase);
		void block_gethurt();
		void block_position(int, int);
		void ContainPotion(bool,DROP);
		void AppearDrop(bool);
		
		int  block_blood();
		
		void show();
		
		CMovingBitmap get_block();
		
	private:
		bool block_or_object;
		bool _TF_potion;
		bool _TF_Appear_drop;
		int _type;
		int _BlockBlood;
		DROP _potiontype;
		Drops _drops;
		times _clk;
		clock_t temp;
		bool _TF_trap;
		CMovingBitmap _block;
		CMovingBitmap _object;
		music sounds;
	};
}
#endif