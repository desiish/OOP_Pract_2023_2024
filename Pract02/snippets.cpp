#include <iostream>
// Structs
struct Empty {

}; // 1

struct Test1 {
    int a;
}; // 4

struct Test2 {
    char* a;
    int* b;
}; // 16

struct Test3 {
    char a[3];
    short b;
    double c[2];
    char d;
}; // 32

struct Test4 {
    int a[3];
    short b;
    char c[];
}; // 16

struct A {
    int i;
    bool b;
    double c;
}; // 16

struct B {
    A obj;
    int c;
}; // 24

struct C {
    A objA;
    B objB;
}; //40