#include <iostream>
#include <type_traits>

template<bool, class T = void>
struct EnableIfT {};

template<class T>
struct EnableIfT<true, T> {
    using type = T;
};

template<bool Cond, class T = void>
using EnableIf = typename EnableIfT<Cond, T>::type;

// 这里使用了函数模板重载，只有默认模板参数不同会被认为是相同的函数，
// 所以需要在第二个重载的函数模板中增加第三个默认模板参数
template<class T, class = EnableIf<!std::is_same_v<T, int>>>
void add() {
    std::cout << "T is not int" << std::endl;
}

template<class T, class = EnableIf<std::is_same_v<T, int>>, class = void>
void add() {
    std::cout << "T is int" << std::endl;
}

int main() {

    add<float>();
    add<int>();

    return 0;
}