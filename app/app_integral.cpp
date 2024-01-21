#include <iostream>
#include <type_traits>

// 主模板
template<class T>
struct IsIntegral : std::false_type {};

// 模板偏特化
template<>
struct IsIntegral<int> : std::true_type {};

template<>
struct IsIntegral<long> : std::true_type {};

template<>
struct IsIntegral<short> : std::true_type {};

template<>
struct IsIntegral<unsigned int> : std::true_type {};

int main() {

    std::cout << "int : " << IsIntegral<int>::value << std::endl;
    std::cout << "long : " << IsIntegral<long>::value << std::endl;
    std::cout << "float : " << IsIntegral<float>::value << std::endl;

    return 0;
}