#pragma once
#include "../Library/gameutil.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace game_framework {
    class ReadCSV {
    public:
        ReadCSV(string);
        vector<vector<int>> GetData();

    private:
		
        vector<vector<int>> data;
    };
}