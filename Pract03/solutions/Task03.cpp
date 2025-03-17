#include <iostream>
#include <fstream>
using namespace std;

constexpr int MAX_SIZE = 1024;
void printFileCode() {
	ifstream ifs("Task03.cpp");
	if (!ifs.is_open())
		return;

	char buff[MAX_SIZE] = {};
	while (true)
	{
		ifs.getline(buff, MAX_SIZE);
		if (ifs.eof())
			break;

		cout << buff << '\n';
	}
}
