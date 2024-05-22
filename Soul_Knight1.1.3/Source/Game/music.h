#include <string>
#include <vector>
#include "../Library/audio.h"
#ifndef music_h
#define music_h


namespace game_framework {
	class music {
	public:
		music();
		~music();
		void load_music();
		void play_music();
		void play_what(int x, bool TF);
		void pause(int x);
		bool get_is_played();
	private:
		vector<string> playlist;
		int count;
		bool is_played = false;
	};
}

#endif