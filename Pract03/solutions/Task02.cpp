#include <iostream>
#include <fstream>
using namespace std;

constexpr size_t MAX_SIZE = 64;
int countOccurecesOfNum(const int* arr, size_t size, int num) {
	int ctr = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == num)
			ctr++;
	}

	return ctr;
}

int findMostCommonInArr(const int* arr, size_t size) {
	int maxNum = -1;
	int maxOcc = 0;
	for (int i = 0; i < size; i++)
	{
		int curr = arr[i];
		int currOcc = countOccurencesOfNum(arr, size, curr);
		if (currOcc > maxOcc) {
			maxOcc = currOcc;
			maxNum = curr;
		}
	}

	return maxNum;
}

int findMostCommonNumInFile(std::ifstream& ifs) {
	int arr[MAX_SIZE] = {};
	int len;
	ifs >> len;
	for (int i = 0; i < len; i++)
	{
		ifs >> arr[i];
	}

	return findMostCommonInArr(arr, len);
}
