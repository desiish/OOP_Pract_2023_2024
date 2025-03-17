#include <iostream>
#include <fstream>
using namespace std;

void saveTwoNums() {
	int x, y;
	cin >> x >> y;
	ofstream ofs("result1.txt");
	if (!ofs.is_open())
		return;

	ofs << x + y << " " << x - y << endl;
}

void readDiffAndSUm() {
	int sum, diff;
	ifstream ifs("result1.txt");
	if (!ifs.is_open())
		return;

	ifs >> sum >> diff;
	cout << (sum + diff) / 2 << " " << (sum - diff) / 2 << endl;
}
