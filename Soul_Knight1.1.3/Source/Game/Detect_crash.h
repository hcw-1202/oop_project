
#include "Block.h"
using namespace game_framework;

bool Detect_crash(int mode, Character character, Block obstacle,Block floor,int sp) {
	
	int gap = sp;
	
	if (obstacle.is_obstacle()) {
		bool tempans = false, tempans2 = false;
		if (mode == 0) {
			
			if (floor.GetLeft() < character.GetLeft() + character.GetWidth() && character.GetLeft() + character.GetWidth() < floor.GetLeft() + floor.GetWidth() || floor.GetLeft() < character.GetLeft() && character.GetLeft() < floor.GetLeft() + floor.GetWidth()) {
				//printf("test\n");
				tempans = true;
			}
			
			if (character.GetTop() - (floor.GetTop() + floor.GetHeight()) >= 0 && character.GetTop() - (floor.GetTop() + floor.GetHeight()) <= gap) {
				//printf("test2\n");
				tempans2 = true;
			}
				

			return tempans && tempans2;
		}
		else if (mode == 1) {
			
			if (floor.GetTop() < character.GetTop() && character.GetTop() < floor.GetTop() + floor.GetHeight() || floor.GetTop() < character.GetTop() + character.GetHeight() && character.GetTop() + character.GetHeight() < floor.GetTop() + floor.GetHeight()) {
				tempans = true;
				
			}
			
			if (floor.GetLeft() - (character.GetLeft() + character.GetWidth()) >= 0 && floor.GetLeft() - (character.GetLeft() + character.GetWidth()) <= 3) {
				
				tempans2 = true;
			}
				

			return tempans && tempans2;
		}
		else if (mode == 2) {
			
			if (floor.GetLeft() < character.GetLeft() + character.GetWidth() && character.GetLeft() + character.GetWidth() < floor.GetLeft() + floor.GetWidth() || floor.GetLeft() < character.GetLeft() && character.GetLeft() < floor.GetLeft() + floor.GetWidth()) {
				tempans = true;
			}
			if (floor.GetTop() -(character.GetTop() + character.GetHeight())  >= 0 && floor.GetTop() - (character.GetTop() + character.GetHeight()) <= gap)
				tempans2 = true;

			return tempans && tempans2;
		}
		else if (mode == 3) {
			
			if (floor.GetTop() < character.GetTop() && character.GetTop() < floor.GetTop() + floor.GetHeight() || floor.GetTop() < character.GetTop() + character.GetHeight() && character.GetTop() + character.GetHeight() < floor.GetTop() + floor.GetHeight()) {
				tempans = true;
			}
			if (character.GetLeft()-(floor.GetLeft() + floor.GetWidth() )  >= 0 && character.GetLeft()-(floor.GetLeft() + floor.GetWidth())   <=gap)
				tempans2 = true;

			return tempans && tempans2;
		}


	}

	return false;







}

