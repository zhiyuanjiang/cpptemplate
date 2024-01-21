#include <iostream>
#include <type_traits>

template<class T>
struct IsConst : std::false_type {};

template<class T>
struct IsConst<T const> : std::true_type {};

int main() {

    std::cout << "const int : " << IsConst<const int>::value << std::endl;
    std::cout << "int : " << IsConst<int>::value << std::endl;

    return 0;
}