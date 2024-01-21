/*
*   std::void_t源码实现：
template<class... _Types>
using void_t = void;

用途：
能够检测出应用SFINAE特性时出现的非法类型。传入到std::void_t中的类型必须是一个有效的类型。
*/

#include <iostream>
#include <type_traits>

template<class T, class U = std::void_t<>>
struct HasType : std::false_type {};

template<class T>
struct HasType<T, std::void_t<typename T::value>> : std::true_type {};

struct S {
    using value = int;
};

template<class T, class U = std::void_t<>>
struct HasValue : std::false_type {};

template<class T>
struct HasValue<T, std::void_t<decltype(T::value)>> : std::true_type {};

struct T {
    static int value;
};

int main() {
    std::cout << HasType<int>::value << std::endl;
    std::cout << HasType<S>::value << std::endl;

    std::cout << HasValue<int>::value << std::endl;
    std::cout << HasValue<T>::value << std::endl;
    return 0;
}