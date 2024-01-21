#include <iostream>
#include <vector>
#include <type_traits>

// SFINAE
template<class T, class = std::void_t<>>
struct HasLess : std::false_type {};

template<class T>
struct HasLess<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

template<class T>
constexpr bool HasLessV = HasLess<T>::value;

template<class T>
requires (!HasLessV<T>)
void tmin() {
    std::cout << "not has less" << std::endl;
}

template<class T>
requires HasLessV<T>
void tmin() {
    std::cout << "has less" << std::endl;
}

struct T {

};

struct S {
    bool operator < (const S&) { return true; }
};

int main() {
    
    tmin<int>();
    tmin<T>();
    tmin<S>();

    return 0;
}