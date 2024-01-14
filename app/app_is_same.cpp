#include <iostream>

template<class T1, class T2>
struct IsSameT {
    static constexpr bool value = false;
};

// 偏特化
template<class T>
struct IsSameT<T, T> {
    static constexpr bool value = true;
};

int main() {

    std::cout << "int is int: " << IsSameT<int, int>::value << std::endl;
    std::cout << "int is double: " << IsSameT<int, double>::value << std::endl; 
    return 0;
}