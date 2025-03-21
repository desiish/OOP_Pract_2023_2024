#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

constexpr size_t MAX_SIZE = 1024;
constexpr size_t INVALID_LINE_INDEX = -1;
void printDiffLineIndex(std::ifstream& ifs1, std::ifstream& ifs2) {
	char buff1[MAX_SIZE] = {};
	char buff2[MAX_SIZE] = {};

	int ctr = 0;
	while (true) {
		ctr++;
		ifs1.getline(buff1, MAX_SIZE);
		ifs2.getline(buff2, MAX_SIZE);

		if (ifs1.eof() && ifs2.eof())
		{
			cout << INVALID_LINE_INDEX << endl;
			return;
		}

		if (ifs1.eof() || ifs2.eof() || strcmp(buff1, buff2) != 0)
		{
			cout << ctr << endl; 
			return;
		}
	}
}
