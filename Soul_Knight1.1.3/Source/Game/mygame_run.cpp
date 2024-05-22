#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <cmath>
#include <string>


using namespace game_framework;

bool CGameStateRun:: TF_load_musice = true;

int bullet_num = -1;
clock_t hurt_start;
clock_t monster_stop[5];
clock_t skillCD;
clock_t gg;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
////////////////// ///////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{

}

CGameStateRun::~CGameStateRun()
{

}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	

	
	testroom.Monster_Move(&Hero, bullet_num, bullet,time);
	
	
	if (Hero.isalive()) {
		if (Is_press[0]) {

			testroom.ControlRoom(TOP,bullet_num,bullet);
			bool mv = false;
			//for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_stay(TOP, Hero.get_speed());
		}
		
		if (Is_press[1]) {
			
			testroom.ControlRoom(RIGHT, bullet_num, bullet);

			//for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_stay(RIGHT, Hero.get_speed());
		}
		
		if (Is_press[2]){
			
			testroom.ControlRoom(DOWN, bullet_num, bullet);
			//for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_stay(DOWN, Hero.get_speed());

		}

		if (Is_press[3]){

			testroom.ControlRoom(LEFT, bullet_num, bullet);
			bool mv = false;
			//for (int i = 0; i <= bullet_num; i++) if (bullet[i].is_flying()) bullet[i].bullet_stay(LEFT, Hero.get_speed());

		}
		if (Is_press[0] || Is_press[1] || Is_press[2] || Is_press[3]) {
			if (Hero.get_dir() == 1) {
				Hero.anime(true, RIGHT);
			}
			else {
				Hero.anime(true, LEFT);
			}
		}
		else {
			if (Hero.get_dir() == 1) {
				Hero.anime(false, RIGHT);
			}
			else {
				Hero.anime(false, LEFT);
			}
		}
		
		
		//skill
		if (skill) {
			skill = Hero.skill();
			Hero.TF_startanime(false);
			Hero.set_speed(10);
			Hero.is_invincible(0);
		}
		else {
			Hero.TF_startanime(true);
			Hero.set_speed(8);
		}

	}
	
	//printf("%d\n",static_cast<int>(floor(static_cast<float>(4) / static_cast<float>(6)  * 10.0)));
	testroom.ControlGate();
	testroom.Where_is_Hero(Hero);
	showLevel.SetFrameIndexOfBitmap(Level);
	testroom.Keep_detect_interaction();

	if (Hero.get_blood() == 0) {
		song.pause(10);
	}
}





void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	if (TF_load_musice) {
		song.load_music();
		
		Hero.set_right_pic(0);

		Hero.set_left_pic(0);

		showLevel.LoadBitmapByString({ "resources/Level_11.bmp","resources/Level_12.bmp","resources/Level_13.bmp","resources/Level_14.bmp","resources/Level_15.bmp","resources/Level_21.bmp","resources/Level_22.bmp","resources/Level_23.bmp","resources/Level_24.bmp","resources/Level_25.bmp" }, RGB(0, 0, 0));

		fail_or_success.LoadBitmapByString({ "resources/fail_to_pass.bmp","resources/pass.bmp" });

		skill_cd_pattern.LoadBitmapByString({ "resources/wakuwaku.bmp" }, RGB(255, 255, 255));

		

		TF_load_musice = false;

	}
	if(song.get_is_played()) song.pause(14);
	song.play_what(10,true);
	
	Room::Hero_talent.Talent_clear();
	Hero.Hero_init(6, 6, 200);
	game_framework::Room::Hero_talent;


	Hero.set_speed(5);
	Hero.set_power(4);
	Hero.hurt_time();

	Hero.set_skillCD(1.0);
	skill = false;
	TF_change = false;
	_mute =true;
	state.SetHeroState();

	Hero.anime(false, LEFT);
	Hero.set_pos(700-Hero.GetWidth()/2,500-Hero.GetHeight()/2);
	testroom.OAODistributeMap(&setroom,&Hero,false);
	Level = 0;
	
	


	
	showLevel.SetTopLeft(0,1000-showLevel.GetHeight()-100);

	
	fail_or_success.SetTopLeft(0, 0);

	
	skill_cd_pattern.SetTopLeft(600, 450);

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if (Hero.isalive()) {
		if (nChar == VK_UP) {
			Is_press[0] = true;
		}
		else if (nChar == VK_RIGHT) {
			Is_press[1] = true;
			Hero.set_right();
		}
		else if (nChar == VK_DOWN) {
			Is_press[2] = true;

		}
		else if (nChar == VK_LEFT) {
			Is_press[3] = true;
			Hero.set_left();
		}
		if (nChar == 0x58) {
			testroom.near_attack();
			Hero.TF_nearattack(true);
			printf("false\n");
		
		}
		
	}
	

	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
		Is_press[0] = false;
	if (nChar == VK_DOWN)
		Is_press[2] = false;
	if (nChar == VK_LEFT) {
		Is_press[3] = false;
		Hero.set_left();
	}	
	if (nChar == VK_RIGHT) {
		Is_press[1] = false;
		Hero.set_right();
	}
	else if (nChar == VK_SPACE){
		if (!Hero.isalive()) {
			testroom.DeleteAll();
			CGameStateRun::OnInit();
			GotoGameState(GAME_STATE_INIT);
		}
		if (testroom.TF_interaction()) {
			if (Level < 9) {
				
				testroom.DeleteAll();
				Level++;
				testroom.OAODistributeMap(&setroom, &Hero, Level);
				
				printf("Level=%d\n", Level);
			}
			else {
				testroom.DeleteAll();
				CGameStateRun::OnInit();
				GotoGameState(GAME_STATE_OVER);
			}
			
		}
		
		if (testroom.Where_is_Hero(Hero) != 100) {
			bullet_num += 1;
			if (bullet_num == 20) bullet_num = 0;
			bullet[bullet_num].LoadBitmapByString({ "resources/yellow.bmp" }, RGB(255, 255, 255));
			bullet[bullet_num].SetTopLeft(Hero.get_left_pic().GetLeft(), Hero.get_left_pic().GetTop() + 20);
			if (testroom.Where_is_Hero(Hero) != 100) {
				if (setroom[testroom.Where_is_Hero(Hero)]->Get_roomtype() == MONSTER_Room && !setroom[testroom.Where_is_Hero(Hero)]->take_is_fight_end()) bullet[bullet_num].shoot(Hero, Hero.get_dir(), testroom.get_mon(), Is_press);
				else if (setroom[testroom.Where_is_Hero(Hero)]->Get_roomtype() == BOSS_Room && !setroom[testroom.Where_is_Hero(Hero)]->get_boss_delete() && setroom[testroom.Where_is_Hero(Hero)]->take_boss()->get_blood() > 0) {
					setroom[testroom.Where_is_Hero(Hero)]->take_boss()->set_range(Hero);
					bullet[bullet_num].shoot(Hero, Hero.get_dir(), setroom[testroom.Where_is_Hero(Hero)]->take_boss(), Is_press);
				}
				else bullet[bullet_num].shoot(Hero, Hero.get_dir(), Is_press);
			}
			else bullet[bullet_num].shoot(Hero, Hero.get_dir(), Is_press);
			song.play_music();
		}
	}
	// refresh map control
	if (nChar == VK_CONTROL) {
		
		Hero.Hero_init(6, 6, 200);
		testroom.DeleteAll();
		testroom.OAODistributeMap(&setroom,&Hero,false);
	}
	// imitate teleport Z
	if (nChar == 0x5A) {
		if (Level <9) {
			TF_change = true;
			testroom.DeleteAll();
			Level++;
			

			testroom.OAODistributeMap(&setroom, &Hero, Level);
			printf("Level=%d\n", Level);

		}
		else {
			testroom.DeleteAll();
			//CGameStateRun::OnInit();
			GotoGameState(GAME_STATE_OVER);
		}
	}
	//add blood to 100000 to imitate invincible
	if (nChar == 0x56) {
		Hero.Set_blood(100000);
	}
	
	if (nChar == 0x43 && TF_skill) {
		
		skillCD = clock();
		
		skill = true;
		printf("times\n");
		Hero.startskill();
	}
	// K killMonster
	if (nChar == 0x4B) {
		if (testroom.Where_is_Hero(Hero) != 100 && setroom[testroom.Where_is_Hero(Hero)]->Get_roomtype() == MONSTER_Room) {
			setroom[testroom.Where_is_Hero(Hero)]->kill_all_mon();
		}
		
	}
	//P pause
	if (nChar == 0x50) {
		
	}
	//x near attack
	if (nChar == 0x58) {
		Hero.TF_nearattack(false);
		
		printf("true\n");
	}
	
	// mute 
	if (nChar == 0x4D) {
		
		if (_mute) {
			song.pause(10);
			_mute = false;
		}
		else {
			song.play_what(10, true);
			_mute = true;
		}
		
		
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	
	
	
	
	if (Level <= 9) {
		if (!Hero.isalive()) {
			if (time.appearfailorsuccess(clock(), gg)) {

				fail_or_success.SetFrameIndexOfBitmap(0);
				fail_or_success.ShowBitmap();
				if (!song.get_is_played()) song.play_what(14, true);

			}
			else {

				for (int i = 0; i < setroom.size(); i++) {
					setroom[i]->show();
				}
				TF_skill = time.skillCD(&Hero, clock(), skillCD, 1.0);
				if (TF_skill)
					skill_cd_pattern.ShowBitmap();
				else
					skill_cd_pattern.UnshowBitmap();

				for (int i = 0; i <= bullet_num; i++) {
					if (bullet[i].is_flying()) bullet[i].ShowBitmap();
				}
				testroom.show_mon_bullet();
				state.SetValue(Hero);
				state.show();
				showLevel.ShowBitmap();
				draw_text();
			}


		}
		else {

			gg = clock();

			for (int i = 0; i < setroom.size(); i++) {
				setroom[i]->show();
			}
			TF_skill = time.skillCD(&Hero, clock(), skillCD, Hero.get_skillCD());
			if (TF_skill)
				skill_cd_pattern.ShowBitmap();
			else
				skill_cd_pattern.UnshowBitmap();

			for (int i = 0; i <= bullet_num; i++) {
				if (bullet[i].is_flying()) bullet[i].ShowBitmap();
			}
			testroom.show_mon_bullet();
			state.SetValue(Hero);
			state.show();
			showLevel.ShowBitmap();
			draw_text();


		}
	}
		

	
	
	
}

void CGameStateRun::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();


	/* Print title */


	/* Print info */
	int boss_bl;
	if (testroom.Where_is_Hero(Hero) != 100) {
		if (setroom[testroom.Where_is_Hero(Hero)]->Get_roomtype() == BOSS_Room) {
			boss_bl = setroom[testroom.Where_is_Hero(Hero)]->take_boss()->get_blood();
		}
	}
	string boss_blood(std::to_string(boss_bl));
	int bl = Hero.get_blood();
	int sh = Hero.get_shield();
	int ma = Hero.get_mana();
	string blood(std::to_string(bl));
	string shield(std::to_string(sh));
	string mana(std::to_string(ma));
	blood = blood + " / " + std::to_string( Hero.get_maxblood());
	shield = shield + " / " + std::to_string(Hero.get_maxshield());
	mana = mana + " / " + "200 ";
	
	CTextDraw::ChangeFontLog(pDC, 12, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 100, 10, blood);
	CTextDraw::Print(pDC, 100, 34, shield);
	CTextDraw::Print(pDC, 84, 60, mana);
	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(255, 255, 255));
	if (testroom.Where_is_Hero(Hero) != 100 && setroom[testroom.Where_is_Hero(Hero)]->Get_roomtype() == BOSS_Room && setroom[testroom.Where_is_Hero(Hero)]->take_boss()->get_blood() > 0) {
		CTextDraw::Print(pDC, setroom[testroom.Where_is_Hero(Hero)]->take_boss()->GetLeft() +30, setroom[testroom.Where_is_Hero(Hero)]->take_boss()->GetTop() - 40, boss_blood);
	}

	CDDraw::ReleaseBackCDC();


}

