#include "stdafx.h"
#include "bonus_room.h"

namespace game_framework {
	BonusRoom::BonusRoom(int size, Hero *hero) :Room(size, hero) {
		_type = BONUS_Room;
		int mid = ((_size + 1) / 2) - 1;
		_chestX = mid;
		_chestY = mid;
		_trigger = true;
		Creat_map[_chestX][_chestY].blocktype(CHEST_CLOSE);



	};
	BonusRoom::~BonusRoom() {

	}
	bool BonusRoom::TF_interaction() {
		if (_trigger && TF_inner_room()) {

			Creat_map[_chestX][_chestY].ContainPotion(true, RECOVERY);
			Creat_map[_chestX][_chestY].AppearDrop(true);
			_trigger = false;
		}

		
		
		

		if (Creat_map[_chestX][_chestY].Gettype() == CHEST_OPEN && Creat_map[_chestX][_chestY].TF_ContainPosition())
			Creat_map[_chestX][_chestY].GetDrop(_hero, Hero_talent.Increase_potion_healing());


		if (Creat_map[_chestX][_chestY].get_block().IsOverlap(Creat_map[_chestX][_chestY].get_block(), _hero->get_deter_area()) && Creat_map[_chestX][_chestY].Gettype() == CHEST_CLOSE) {
			sounds.play_what(12, false);
			Creat_map[_chestX][_chestY].blocktype(CHEST_OPEN);

			return false;
		}


		
		return false;

	}
	void BonusRoom::Gate(blocktype gate_condition) {

	}





}