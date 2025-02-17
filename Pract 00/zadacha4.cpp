#include <iostream>
void buildArray(int* arrayOfNumbers, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Enter a number: \n";
        int nextN;
        std::cin >> nextN;
        *arrayOfNumbers = nextN;
        arrayOfNumbers++;
    }

}
int isSequence(int *arrayOfNumbers) {
    if (*arrayOfNumbers == '\0') {
        return 1;
    }
    if (*arrayOfNumbers < isSequence(arrayOfNumbers++)) {
        return 0;
    }


}
int main()
{
    int n;
    std::cout << "Enter amount of sequence's indexes: \n";
    std::cin >> n;

    int *arrayOfNumbers = new int[n + 1];
    buildArray(arrayOfNumbers, n);



    std::cout << isSequence(arrayOfNumbers);

    
}


