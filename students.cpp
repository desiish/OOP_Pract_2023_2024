#include <iostream>
#include <assert.h>
using std::cin;
using std::cout;
using std::endl;

enum class Year {
	FIRST, 
	SECOND, 
	THIRD, 
	FOURTH, 
	UNKNOWN
};

struct Student {
	unsigned fn;
	Year y;
	double grade;
};

void initStudent(Student& s, unsigned fn, Year y, double grade) {
	s.fn = fn;
	s.y = y;
	s.grade = grade;
}

void printYear(Year y) {
	switch (y) {
	case Year::FIRST: cout << "First"; break;
	case Year::SECOND: cout << "Second"; break;
	case Year::THIRD: cout << "Third"; break;
	case Year::FOURTH: cout << "Fourth"; break;
	default: cout << "Unknown"; break;
	}
	cout << endl;
}

void printStudent(const Student& s) {
	cout << "FN: " << s.fn << endl;
	printYear(s.y);
	cout << "Grade: " << s.grade << endl;
}

enum class ErrorCode {
	OK, 
	INVALID_YEAR
};

struct Result{
	Year y;
	ErrorCode code;
};

Result getYearRes(int n) {
	switch (n) {
	case 0: return { Year::FIRST, ErrorCode::OK };
	case 1: return { Year::SECOND, ErrorCode::OK };
	case 2: return { Year::THIRD, ErrorCode::OK };
	case 3: return { Year::FOURTH, ErrorCode::OK };
	default: return { Year::UNKNOWN, ErrorCode::INVALID_YEAR };
	}
}

Student readStudent() {
	unsigned fn;
	cin >> fn;
	int n;
	cin >> n;
	Result res = getYearRes(n);
	assert(res.code == ErrorCode::OK);
	double grade;
	cin >> grade;
	Student s;
	initStudent(s, fn, res.y, grade);
	return s;
}

constexpr unsigned MAX_SIZE = 32;

struct Group {
	Student students[MAX_SIZE] = {};
	unsigned currSize = 0;
	double average;
};

Group readGroup() {
	int size;
	cin >> size;
	assert(size <= MAX_SIZE);

	Group gr;
	double sumOfGrades = 0.0;

	for (int i = 0; i < size; i++) {
		gr.students[gr.currSize] = readStudent();
		sumOfGrades += gr.students[gr.currSize++].grade;
	}

	gr.average = sumOfGrades / gr.currSize;

	return gr;
}

unsigned getCountOfScholarships(const Group& gr, double minGrade) {
	unsigned ctr = 0;
	for (int i = 0; i < gr.currSize; i++) {
		if (gr.students[i].grade >= minGrade)
			ctr++;
	}

	return ctr;
}

void sortGroup(Group& gr, bool (*pred) (const Student& lhs, const Student& rhs)) {
	for (int i = 0; i < gr.currSize - 1; i++) {
		int minInd = i;
		for (int j = i; j < gr.currSize; j++) {
			if (pred(gr.students[j], gr.students[minInd]))
				minInd = j;
		}

		if (minInd != i) {
			std::swap(gr.students[minInd], gr.students[i]);
		}
	}
}

void printAllScholarshipsSorted(Group& gr, double minGrade) {
	sortGroup(gr, [](const Student& lhs, const Student& rhs) {return lhs.grade > rhs.grade;});
	for (int i = 0; i < gr.currSize; i++) {
		if (gr.students[i].grade < minGrade)
			break;

		printStudent(gr.students[i]);
	}
}

int main() {
	Group gr = readGroup();
	double minGrade;
	cin >> minGrade;
	printAllScholarshipsSorted(gr, minGrade);
}
