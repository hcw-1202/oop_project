#pragma once
#ifndef HeroSkill_H
#define HeroSkill_H

#include "../Library/gameutil.h"
#include "Hero.h"
#include "EnumLibrary.h"
#include "RandForMapObject.h"
namespace game_framework {
	const int _AllTalentSize = 6;
	
	class Hero;
	class HeroSkill{
	public:
		HeroSkill() {
			TF_AvoidTrap = false;
			TF_IncreatHealing = false;
			TF_choose = false;
			NowLevel = 0;
			HeroTotalTalent.clear();
		};
		void Talent_clear() {
			HeroTotalTalent.clear();
			HeroTalent.clear();
			TF_choose = false;
		};
		void Init_Talent() {
			Whichtalent = _rand.RandForThreeTalent(_AllTalentSize,HeroTotalTalent);
			
			for (int i = 0; i < 3; i++) {
				//printf("temp=%d\n", temp[i]);
				
				_skill[i].LoadBitmapByString({ "resources/potion_buff_pause.bmp","resources/increase_max_health_pause.bmp","resources/armor_plus_one_pause.bmp","resources/AvoidTrapDamage.bmp","resources/decrease_skillCD.bmp","resources/increase_damage.bmp","resources/black.bmp" });
				_skill_illusrate[i].LoadBitmapByString({ "resources/potion_buff_description.bmp","resources/increase_max_health_description.bmp","resources/armor_plus_one_description.bmp","resources/AvoidTrapDamage_description.bmp","resources/decrease_skillCD_description.bmp","resources/increase_damage_description.bmp","resources/black.bmp" });
				_skill[i].SetFrameIndexOfBitmap(Whichtalent[i]);
				_skill_illusrate[i].SetFrameIndexOfBitmap(Whichtalent[i]);

			}
			TF_choose = false;
			
			
		
		}
			
		void Set_Skill_block(int x,int y, int Level){
			NowLevel = Level+1;
			if (NowLevel%2 == 0) {
				
				
				for (int i = 0; i < 3; i++) {
					vector<int> ::iterator temp=std::find(HeroTotalTalent.begin(), HeroTotalTalent.end(), Whichtalent[i]);
					if (temp == HeroTotalTalent.end()) {
						
						_skill[i].SetTopLeft(x + 120 * i, y);
						
						_skill_illusrate[i].SetTopLeft(_skill[i].GetLeft() + (_skill[i].GetWidth() - _skill_illusrate[i].GetWidth() / 2), y - 60);
					}
					
				}
			}
			
			
		}
		void Select_Skill(Hero *hero) {
			if (NowLevel %2== 0) {
				for (int skillnum = 0; skillnum < 3; skillnum++) {
					if (CMovingBitmap::IsOverlap(hero->get_left_pic(), _skill[skillnum]) && !TF_choose) {
						TF_choose = true;
						sounds.play_what(13,false);
						if (_skill[skillnum].GetFrameIndexOfBitmap() == POTION_BUFF) {
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							TF_IncreatHealing = true;
							HeroTotalTalent.push_back(POTION_BUFF);
						}
						else if (_skill[skillnum].GetFrameIndexOfBitmap() == INCREASE_HEALTH) {
							int tempmax;
							tempmax = hero->get_maxblood();
							hero->set_maxblood(10);
							hero->Set_blood(static_cast<int>(floor(static_cast<float>(hero->get_blood()) / static_cast<float>(tempmax)  * 10.0))) ;
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							HeroTotalTalent.push_back(INCREASE_HEALTH);

						}
						else if (_skill[skillnum].GetFrameIndexOfBitmap() == ARMOR_PLUS) {
							hero->set_maxshield(hero->get_maxshield() + 1);
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							HeroTotalTalent.push_back(ARMOR_PLUS);
						}
						else if (_skill[skillnum].GetFrameIndexOfBitmap() == AvoidTrapDamage) {
							TF_AvoidTrap = true;
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							HeroTotalTalent.push_back(AvoidTrapDamage);
						}
						else if (_skill[skillnum].GetFrameIndexOfBitmap() == Decrease_SkillCD) {
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							HeroTotalTalent.push_back(Decrease_SkillCD);
							hero->set_skillCD(0.5);
							
						}
						else if (_skill[skillnum].GetFrameIndexOfBitmap() == Increase_damage) {
							_skill[skillnum].SetTopLeft(0, 100 + (HeroTotalTalent.size()*_skill[skillnum].GetHeight()));
							HeroTotalTalent.push_back(Increase_damage);
							hero->set_power(hero->get_power()+2);
						}
						HeroTalent.push_back(_skill[skillnum]);
					}
					else {

					}

				}
			}
			
		};
		void show_skill(Hero *hero) {
			
				for (int skillnum = 0; skillnum < 3; skillnum++) {
					if (CMovingBitmap::IsOverlap(hero->get_left_pic(), _skill[skillnum]) && !TF_choose) {
						if(NowLevel%2==0)
							_skill_illusrate[skillnum].ShowBitmap();
						else
							_skill_illusrate[skillnum].UnshowBitmap();
					}
				}
				for (int i = 0; i < 3; i++) {
					vector<int> ::iterator temp = std::find(HeroTotalTalent.begin(), HeroTotalTalent.end(), _skill[i].GetFrameIndexOfBitmap());
						if(!TF_choose && NowLevel%2==0 && temp==HeroTotalTalent.end())
							_skill[i].ShowBitmap();
						//printf("test=%d\n", _skill[i].GetFrameIndexOfBitmap());
					
						


				}
				
			

		}
		void show_hero_talent() {
			for (int i = 0; i < HeroTalent.size(); i++) {
				HeroTalent[i].ShowBitmap();
			}
		}
		bool Increase_potion_healing() {
			return TF_IncreatHealing;
		}
		bool Avoid_TrapDamage() {
			return TF_AvoidTrap;
		}
		~HeroSkill()=default;

	private:
		vector<CMovingBitmap> HeroTalent;
		CMovingBitmap _skill[3];
		CMovingBitmap _skill_illusrate[3];
		RandForAll _rand;
		music sounds;
		vector<int> HeroTotalTalent;
		int NowLevel;
		bool TF_IncreatHealing;
		bool TF_AvoidTrap;
		bool TF_choose;
		vector<int> Whichtalent = { 0 };
	};

	
}

#endif // !HeroSkill_H