#pragma once
#ifndef EnumLibrary_H
#define EnumLibrary_H
enum ROOMTYPE {
	SPAWN_Room = 1,
	MONSTER_Room,
	BONUS_Room,
	BOSS_Room,
	TELEPORT_Room
};
enum SIZEOAO {
	SMALL = 9,
	MEDIUM = 13,
	BIG = 19
};
enum POSITION_OAO {
	TOP,
	RIGHT,
	DOWN,
	LEFT
};
enum blocktype {
	TOP_WALL = 1,
	RIGHT_WALL,
	DOWN_WALL,
	LEFT_WALL,
	TELEPORT,
	CHEST_OPEN,
	CHEST_CLOSE,
	FIRE,
	OBSTACLE,
	FLOOR,
	WOOD,
	TRAP,
	CUTEANIME,
	GATE_OPEN,
	GATE_CLOSE,
	OTHER
};
enum GunType {
	P2020,
	Mo3peko,
	R301
};
enum SkillNum {
	POTION_BUFF,
	INCREASE_HEALTH,
	ARMOR_PLUS,
	AvoidTrapDamage,
	Decrease_SkillCD,
	Increase_damage
};

#endif // !EnumLibrary_H
