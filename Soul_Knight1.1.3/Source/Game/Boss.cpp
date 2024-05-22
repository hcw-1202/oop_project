#include "stdafx.h"
#include "Boss.h"

namespace game_framework {
	void Boss::set_init() {
		this->phase1 = false;
		this->phase2 = false;
		this->phase3 = false;
		this->loading = false;
		this->is_running = false;
		this->boss_x = 0;
		this->boss_y = 0;
		this->stopping = false;
	}
	bool Boss::check_is_shot_end() {
		if (phase1 == true && phase2 == true && phase3 == true) {
			phase1 = false;
			phase2 = false;
			phase3 = false;
			return true;
		}
		return false;
	}
	void Boss::set_phase(int x) {
		if (x == 1) phase1 = true;
		if (x == 2) phase2 = true;
		if (x == 3) phase3 = true;
		if (x == 200) is_running = true;
		if (x == 201) is_running = false;
	}
	void Boss::set_time() {
		phase_time = clock();
	}
	bool Boss::get_phase(int x) {
		if (x == 1) return phase1;
		if (x == 2) return phase2;
		if (x == 3) return phase3;
		if (x == 200) return is_running;
	}
	clock_t Boss::get_time() {
		return phase_time;
	}
	void Boss::show_boss() {
		if (alive) {
			this->get_left_pic().ShowBitmap();
		}
	}
	void Boss::set_boss_loading(int type) {
		if (type == 0) boss_loading = true; //冷卻中
		else if (type == 1) boss_loading = false; //冷卻完畢
	}
	bool Boss::get_boss_loading() {
		return boss_loading;
	}
	void Boss::set_xy(int x, int y) {
		boss_x = x;
		boss_y = y;
	}
	int Boss::get_boss_x() {
		return boss_x;
	}
	int Boss::get_boss_y() {
		return boss_y;
	}
	void Boss::set_stop(int x) {
		if (x == 0) stopping = true;
		else stopping = false;
	}
	bool Boss::get_stopping() {
		return stopping;
	}
}