#ifndef  BONUS_H
#define  BONUS_H


#include "Room.h"
#include"Hero.h"
namespace game_framework {
	enum ChestCondition {
		CLOSE,
		OPEN
	};
	class BonusRoom :public Room {
	public:
		BonusRoom(int size,Hero *);
		~BonusRoom() override;
		void Gate(blocktype) override;
		bool TF_interaction() override;
		
	
	private:
		ChestCondition _chest;
		int _chestX;
		int _chestY;
		music sounds;
		bool _trigger;
	};
}
#endif // ! BONUS_H