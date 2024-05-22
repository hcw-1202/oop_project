#include "stdafx.h"
#include "music.h"
namespace game_framework {
	music::music() {
		count = 0;
		is_played = false;
	}
	music::~music() {
		//game_framework::CAudio *audio = game_framework::CAudio::Instance();
		//audio->~CAudio();
	}
	void music::load_music() {
		game_framework::CAudio *audio = game_framework::CAudio::Instance();
		string song = "Sounds/Player_shoot.mp3";
		string background = "Sounds/forest_bgm.mp3";
		string potion = "Sounds/drink_potion.mp3";
		string chest = "Sounds/open_chest.mp3";
		string buff = "Sounds/choose_buff.mp3";
		string fail = "Sounds/fail.mp3";
		string victory = "Sounds/victory.mp3";
		char * target1 = new char[song.length() + 1];
		char * target2 = new char[background.length() + 1];
		strcpy(target1, song.c_str());
		strcpy(target2, background.c_str());
		for (int i = 0; i < 10; i++) {
			audio->Load(i, target1);
		}
		audio->Load(10, target2); //background music
		strcpy(target1, potion.c_str());
		audio->Load(11, target1); //drink potion
		strcpy(target2, chest.c_str());
		audio->Load(12, target2); //open chest
		strcpy(target1, buff.c_str());
		audio->Load(13, target1); //choose buff
		strcpy(target2, fail.c_str());
		audio->Load(14, target2); //fail
		strcpy(target1, victory.c_str());
		audio->Load(15, target1); //victory
		delete[] target2;
		delete[] target1;
	}
	void music::play_music() {
		game_framework::CAudio *audio = game_framework::CAudio::Instance();
		audio->Play(count, false);
		count += 1;
		if (count == 10) count = 0;
	}
	void music::play_what(int x,bool TF) {
		/*
		0-9:子彈音效(bullet sound)
		10:背景音效(background music)
		11:喝藥水(drink potion)
		12:開箱子(open chest)
		13:選天賦(choose buff)
		14:通關失敗(fail)
		15:通關成功(victory)
		*/
		game_framework::CAudio *audio = game_framework::CAudio::Instance();
		if (x == 14) is_played = true;
		audio->Play(x, TF);
		printf("play %d song\n", x);
	}
	void music::pause(int x) {
		game_framework::CAudio *audio = game_framework::CAudio::Instance();
		audio->Stop(x);
		if (x == 14) is_played = false;
	}
	bool music::get_is_played() {
		return is_played;
	}
}