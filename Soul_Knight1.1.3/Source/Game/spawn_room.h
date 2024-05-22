#pragma once
#ifndef SPAWN_H
#define SPAWN_H

#include "RandForMapObject.h"
#include "Room.h"
#include "HeroSkill.h"
namespace game_framework {
	class SpawnRoom:public Room {
	public:
		SpawnRoom(int size, Hero *hero,int Level);
		~SpawnRoom() override;
		void Set_position(int, int) override;
		void Gate(blocktype) override;
		void show() override;
		bool TF_interaction() override;
		
		
	private:
		RandForAll _randforall;
		
		
		
		
	};
}
#endif // ! SPAWN