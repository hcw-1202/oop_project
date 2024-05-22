#include "stdafx.h"
#include "teleport_room.h"
namespace game_framework {
	TeleportRoom::TeleportRoom(SIZEOAO size, Hero *hero) :Room(size, hero) {
		_type = TELEPORT_Room;
		_teleportX = _size / 2 - 1;
		_teleportY = _size / 2 - 1;
		Creat_map[_teleportX][_teleportY].blocktype(TELEPORT);

	}
	TeleportRoom::~TeleportRoom() {

	}
	bool TeleportRoom::TF_interaction() {

		if (Creat_map[_teleportX][_teleportY].get_block().IsOverlap(Creat_map[_teleportX][_teleportY].get_block(), _hero->get_deter_area())) {
			printf("teleport!\n");
			return true;
		}
		return false;
	}

	void TeleportRoom::Gate(blocktype gate_condition) {

	}
}