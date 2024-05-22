
#pragma once
#ifndef BOSSROOM_H
#define BOSSROOM_H

#include "room.h"
#include "Boss.h"
#include "Bullet.h"
#include "RandForMapObject.h"

namespace game_framework {
	class BossRoom : public Room {
	public:
		BossRoom(int size, Hero *, int power, int bloood, int type);
		~BossRoom();
		void Gate(blocktype) override;
		bool take_is_fight_end() override;
		bool TF_interaction() override;
		Boss *take_boss();
		void show() override;
		void rand_boss_pos(Hero hero) override;
		void delete_boss() override;
		bool get_boss_delete() override;

	protected:

		int count;
		Boss *final_boss;
		RandForAll rand;
		ReturnXY pos;
		bool is_delete;

	private:
		int _teleportX;
		int _teleportY;
	};
}
#endif