#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

constexpr size_t MAX_NAME_SIZE = 64;
constexpr size_t MAX_CITIES = 20;
struct City {
	char name[MAX_NAME_SIZE] = {};
	unsigned citizens = 0;
};

struct District {
	size_t size = 0;
	City cities[MAX_CITIES] = {};
};

void writeCityToFile(std::ofstream& ofs, const City& city) {
	ofs << city.name << " " << city.citizens << '\n';
}

void writeDistrictToFile(std::ofstream& ofs, const District& d)
{
	ofs << d.size << '\n';
	for (int i = 0; i < d.size; i++)
		writeCityToFile(ofs, d.cities[i]);
}

void readCityFromFile(std::ifstream& ifs, City& c) {
	ifs >> c.name >> c.citizens;
}

void readDistrictFromFile(std::ifstream& ifs, District& d) {
	ifs >> d.size;
	for (int i = 0; i < d.size; i++)
		readCityFromFile(ifs, d.cities[i]);
}

void sortCities(City* cities, size_t size, bool (*pred) (const City& lhs, const City& rhs)) {
	for (int i = 0; i < size - 1; i++)
	{
		int minInd = i;
		for (int j = i; j < size; j++)
		{
			if (pred(cities[j], cities[minInd]))
				minInd = j;
		}

		if (minInd != i)
			std::swap(cities[i], cities[minInd]);
	}
}

void readAndSaveSorted(std::ifstream& ifs, std::ofstream& ofs, District& d) {
	readDistrictFromFile(ifs, d);
	sortCities(d.cities, d.size, [](const City& lhs, const City& rhs) {return lhs.citizens < rhs.citizens; });
	writeDistrictToFile(ofs, d);
}
