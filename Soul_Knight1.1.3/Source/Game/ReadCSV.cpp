#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "ReadCSV.h"

using std::ifstream;
using std::stringstream;

namespace game_framework {
	ReadCSV::ReadCSV(string path) {
		ifstream file(path);
		
		string cell;
		string rowString;
		stringstream rowStringStream;

		while (file && getline(file, rowString)) {
			
			vector<int> row;
			rowStringStream << rowString;
			while (getline(rowStringStream, cell, ',')) {
				
				stringstream numberStringStream(cell);
				int number;
				numberStringStream >> number;
				row.push_back(number);
			}
			data.push_back(row);
			rowStringStream.str("");
			rowStringStream.clear();
		}
	}

	vector<vector<int>> ReadCSV::GetData() {
		return data;
	}
}