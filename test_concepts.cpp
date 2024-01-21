#include <iostream>
#include <type_traits>

template<class T, class = std::enable_if_t<!std::is_same_v<T, int>>>
void add() {
    std::cout << "T is not int" << std::endl;
}

template<class T, class = std::enable_if_t<std::is_same_v<T, int>>, class = void>
void add() {
    std::cout << "T is int" << std::endl;
}

// test concepts
// concepts 看起来比enable_if 更加的简洁
template<class T>
requires std::is_same_v<T, int>
void sub() {
    std::cout << "T is int" << std::endl;
}

template<class T>
requires (!std::is_same_v<T, int>)
void sub() {
    std::cout << "T is not int" << std::endl;
}

int main() {

    add<float>();
    add<int>();

    sub<float>();
    sub<int>();

    return 0;
}