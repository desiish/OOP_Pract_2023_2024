#include <iostream> 

union unionExample {
    uint32_t n = 0;
    char arr[4];
};

void printByte(char ch) {
    uint8_t mask = 1 << 7;
    std::cout << '[';
    for (int i = 0; i < 8; i++)
    {
        std::cout << ((ch & mask) == mask);
        mask >>= 1;
    }
    std::cout << ']' << ' ';
}

void printIntegerLittleEndian(int n) {
    unionExample u;
    u.n = n;
    std::cout << "Little endian: ";
    for (int i = 0; i < 4; i++)
        printByte(u.arr[i]);
    std::cout << '\n';
}

void printIntegerBigEndian(int n) {
    unionExample u;
    u.n = n;
    std::cout << "Big endian: ";
    for (int i = 3; i >= 0; i--)
        printByte(u.arr[i]);
    std::cout << '\n';
}

int main() {
      printIntegerBigEndian(353);
      printIntegerLittleEndian(353);
}
