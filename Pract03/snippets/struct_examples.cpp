/*-------------------------Struct Examples-------------------------*/
struct A {
    int a;
    bool* b;
    bool c;
}

struct B {
    int arr[5];
    int b;
    A* obj;
}

struct C {
    B obj;
    A obj2;
    bool c[];
}

