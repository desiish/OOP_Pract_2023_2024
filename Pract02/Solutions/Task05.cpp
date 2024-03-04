#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Pair {
	int x, y;
};

constexpr size_t MAX_RELATION_SIZE = 25;

struct Relation {
	Pair pairs[MAX_RELATION_SIZE] = {};
	size_t size = 0;
};

void readPair(std::ifstream& ifs, Pair& p)
{
	ifs >> p.x >> p.y;
}

void readRelation(std::ifstream& ifs, Relation& relation) {
	ifs >> relation.size;
	for (int i = 0; i < relation.size; i++)
	{
		readPair(ifs, relation.pairs[i]);
	}
}

void addPair(Relation& relation, const Pair& p) {
	if (relation.size == MAX_RELATION_SIZE)
		return;

	relation.pairs[relation.size++] = p;
}

void writePair(std::ofstream& ofs, const Pair& p) {
	ofs << p.x << " " << p.y << '\n';
}

void writeRelation(std::ofstream& ofs, const Relation& rel) {
	ofs << rel.size << '\n';

	for (int i = 0; i < rel.size; i++)
		writePair(ofs, rel.pairs[i]);
}
