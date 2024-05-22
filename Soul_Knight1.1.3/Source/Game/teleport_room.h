#ifndef TELEPORT_H
#define TELEPORT_H
#include "room.h"
namespace game_framework {
	class TeleportRoom :public Room {
	public:
		TeleportRoom(SIZEOAO,Hero *);
		~TeleportRoom();
		void Gate(blocktype) override;
		bool TF_interaction() override;
		
	private:
		int _teleportX;
		int _teleportY;
	};
};
#endif // !TELEPORT_H

