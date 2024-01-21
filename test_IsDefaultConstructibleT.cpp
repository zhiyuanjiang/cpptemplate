#include <iostream>
#include <type_traits>

// SFINAE for function override
template<class T>
struct IsDefaultConstructibleT {
private:
    template<class U, class = decltype(U())>
    static char test(void*);

    template<class>
    static long test(...);

public:
    static constexpr bool value = std::is_same_v<decltype(test<T>(nullptr)), char>;
};

// SFINAE排除偏特化
template<class T, class = std::void_t<>>
struct IsDefaultConstructible : public std::false_type {};

template<class T>
struct IsDefaultConstructible<T, std::void_t<decltype(T())>> : public std::true_type {};

struct S {
    S() = delete;
};

int main() {

    std::cout << IsDefaultConstructibleT<int>::value << std::endl;;
    std::cout << IsDefaultConstructibleT<S>::value << std::endl;

    std::cout << IsDefaultConstructible<int>::value << std::endl;;
    std::cout << IsDefaultConstructible<S>::value << std::endl;

    return 0;
}