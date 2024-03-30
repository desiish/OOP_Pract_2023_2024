#include "Multiset.h"

Multiset::Multiset(unsigned n) {
	this->n = n;
	countOfBuckets = n / elementsInBucket + 1;
	buckets = new uint8_t[countOfBuckets]{0};
}

Multiset::Multiset(const Multiset& other) {
	copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Multiset::~Multiset() {
	free();
}

bool Multiset::addNumber(unsigned num) {
	unsigned bucket = num / elementsInBucket;
	unsigned index = num % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	uint8_t mask = 1;
	unsigned occurrences = getCountOfOccurrences(num);

	mask <<= index * 2;

	switch (occurrences)
	{
	case 0: 
	case 2:
	{
		currBucket |= mask;
		return true;
	}
	case 1: {
		mask = ~mask;
		currBucket &= mask;
		mask = ~mask;
		mask <<= 1;
		currBucket |= mask;
		return true;
	}
	default: return false;
	}
}

bool Multiset::removeNumber(unsigned num) {
	unsigned bucket = num / elementsInBucket;
	unsigned index = num % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	uint8_t mask = 1;
	unsigned occurrences = getCountOfOccurrences(num);

	mask <<= index * 2;

	switch (occurrences)
	{
	case 3:
	case 1:
	{
		mask = ~mask;
		currBucket &= mask;
		return true;
	}
	case 2: {
		currBucket |= mask;
		mask <<= 1;
		mask = ~mask;
		currBucket &= mask;
		return true;
	}
	default: return false;
	}
}

unsigned Multiset::getCountOfOccurrences(unsigned num) const {
	unsigned bucket = num / elementsInBucket;
	unsigned index = num % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	uint8_t mask = 1;
	mask <<= index * 2;
	bool isFirstUp = ((currBucket & mask) == mask);
	mask <<= 1;
	bool isSecondUp = ((currBucket & mask) == mask);

	return (isFirstUp * (1 << 0) + isSecondUp * (1 << 1)); // 2^0 and 2^1
}

void Multiset::printNumber(unsigned num, unsigned occurances) const {
	for (unsigned i = 0; i < occurances; i++)
		std::cout << num << " ";
}

void Multiset::printSet() const {
	std::cout << '{';
	for (unsigned i = 0; i < n; i++)
	{
		unsigned occurrences = getCountOfOccurrences(i);
		printNumber(i, occurrences);
	}
	std::cout << '}';
}

void Multiset::addNumberMultipleTimes(unsigned num, unsigned times) {
	if (times > maxOccurrences)
		times = maxOccurrences;

	for (unsigned i = 0; i < times; i++)
		addNumber(num);
		
}

Multiset intersect(const Multiset& s1, const Multiset& s2) {
	assert(s1.n == s2.n);

	int n = s1.n;
	Multiset res(n);

	for (unsigned i = 0; i < n; i++)
	{
		unsigned occurrencesInS1 = s1.getCountOfOccurrences(i);
		unsigned occurrencesInS2 = s2.getCountOfOccurrences(i);
		unsigned occurrences = occurrencesInS1 < occurrencesInS2 ? occurrencesInS1 : occurrencesInS2;
		res.addNumberMultipleTimes(i, occurrences);
	}

	return res;
}

Multiset unify(const Multiset& s1, const Multiset& s2) {
	assert(s1.n == s2.n);

	int n = s1.n;
	Multiset res(n);

	for (unsigned i = 0; i < s1.countOfBuckets; i++)
	{
		res.buckets[i] = s1.buckets[i] | s2.buckets[i];
	}

	return res;
}

void Multiset::free() {
	delete[] buckets;
	n = countOfBuckets = 0;
	buckets = nullptr;
}

void Multiset::copyFrom(const Multiset& other) {
	n = other.n;
	countOfBuckets = other.countOfBuckets;

	for (int i = 0; i < countOfBuckets; i++)
		buckets[i] = other.buckets[i];
}
