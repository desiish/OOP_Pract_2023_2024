#include <iostream>
#include <cstring>
#include <fstream>

namespace Constants {
	constexpr size_t MAX_NAME_SIZE = 100;
	constexpr size_t MAX_SUPPLIER_SIZE = 100;
	constexpr size_t MAX_PRODUCTS_SIZE = 100;
}

enum class Category {
	BEAUTY,
	BOOKS,
	CLOTHING,
	ELECTRONICS,
	FOOD,
	UNKNOWN
};

struct Product {
	char name[Constants::MAX_NAME_SIZE + 1] = {};
	char supplier[Constants::MAX_SUPPLIER_SIZE + 1] = {};
	Category cat = Category::UNKNOWN;
	int quantity = 0;
	double price;
};

void readProducts(std::ifstream& ifs, Product* products, size_t& size) {
	ifs.read((char*)&size, sizeof(size_t));
	ifs.read((char*)products, size * sizeof(Product));
}

void writeProducts(std::ofstream& ofs, const Product* products, size_t size) {
	ofs.write((const char*)&size, sizeof(size));
	ofs.write((const char*)products, size * sizeof(Product));
}

Category initCategory(int index) {
	switch (index) {
	case 0:return Category::BEAUTY;
	case 1: return Category::BOOKS;
	case 2: return Category::CLOTHING;
	case 3: return Category::ELECTRONICS;
	case 4: return Category::FOOD;
	default: return Category::UNKNOWN;
	}
}

void readProduct(Product& pr) {
	std::cin >> pr.name;
	std::cin >> pr.supplier;
	std::cin >> pr.quantity;
	std::cin >> pr.quantity;
	int catIndex;
	std::cin >> catIndex;
	pr.cat = initCategory(catIndex);
}

bool contains(const Product* products, size_t size, const Product& pr) {
	for (int i = 0; i < size; i++)
	{
		if (strcmp(products[i].name, pr.name) == 0)
			return true;
	}

	return false;
}

void saveNProducts(const char* fileName, int n) {
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		return;

	Product currProducts[Constants::MAX_PRODUCTS_SIZE];
	size_t currSize;

	readProducts(ifs, currProducts, currSize);
	ifs.clear();
	ifs.close();

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary | std::ios::app);

	if (!ofs.is_open())
		return;

	for (int i = 0; i < n; i++)
	{
		Product pr;
		readProduct(pr);
		if (!contains(currProducts, currSize, pr))
			ofs.write((const char*)&pr, sizeof(Product));
	}

	ofs.flush();
	ofs.clear();
	ofs.close();
}

void changeQuantity(const char* fileName, const char* prName, int newQuantity) {
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		return;

	Product currProducts[Constants::MAX_PRODUCTS_SIZE];
	size_t currSize;

	readProducts(ifs, currProducts, currSize);
	ifs.clear();
	ifs.close();

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		return;

	for (int i = 0; i < currSize; i++)
	{
		if (strcmp(currProducts[i].name, prName) == 0)
		{
			currProducts[i].quantity = newQuantity;
			break;
		}
			
	}
	writeProducts(ofs, currProducts, currSize);
	ofs.clear();
	ofs.close();
}

const char* categoryToString(Category cat) {
	switch (cat) {
	case Category::BEAUTY: return "Beauty";
	case Category::BOOKS: return "Books";
	case Category::CLOTHING: return "Clothing";
	case Category::ELECTRONICS: return "Electronics";
	case Category::FOOD: return "Food";
	default: return "Unknown";
	}
}

void printProduct(const Product& pr) {
	std::cout << pr.name << '\n' << pr.supplier << '\n' << categoryToString(pr.cat) << '\n'
		<< pr.quantity << '\n' << pr.price << '\n';
}

void printAllProducts(const Product* products, size_t size) {
	for (int i = 0; i < size; i++)
	{
		printProduct(products[i]);
	}
}

void printSpecificProduct(const Product* products, size_t size, const char* name) {
	for (int i = 0; i < size; i++)
	{
		if (strcmp(products[i].name, name) == 0)
		{
			printProduct(products[i]);
			return;
		}
	}
}

void printAllProductsFromFile(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		return;

	Product products[Constants::MAX_PRODUCTS_SIZE];
	size_t size;
	readProducts(ifs, products, size);
	printAllProducts(products, size);
}

void printSpecificProductFromFile(const char* fileName, const char* name) {
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		return;

	Product products[Constants::MAX_PRODUCTS_SIZE];
	size_t size;
	readProducts(ifs, products, size);
	printSpecificProduct(products, size, name);
}

void saveByCategory(const char* in, const char* out, Category cat) {
	std::ifstream ifs(in, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		return;

	Product currProducts[Constants::MAX_PRODUCTS_SIZE];
	size_t currSize;

	readProducts(ifs, currProducts, currSize);
	ifs.clear();
	ifs.close();

	std::ofstream ofs(out, std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		return;

	for (int i = 0; i < currSize; i++)
	{
		if (currProducts[i].cat == cat)
		{
			ofs.write((const char*)&currProducts[i], sizeof(Product));
		}

	}
	ofs.flush();
	ofs.clear();
	ofs.close();
}
