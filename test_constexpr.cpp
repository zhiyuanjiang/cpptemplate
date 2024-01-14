#include <iostream>

constexpr void test(int a) {
    int b = a++;
}

int main() {

    int a;
    test(a); 
    return 0;
}