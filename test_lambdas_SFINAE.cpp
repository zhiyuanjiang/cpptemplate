#include <iostream>
#include <type_traits>

/*
*   参考 c++ template
*   似懂非懂
*/

template<class F, class... Args, 
    class = decltype(std::declval<F>()(std::declval<Args&&>()...))>
std::true_type isValidImpl(void*);

template<class F, class... Args>
std::false_type isValidImpl(...);

inline constexpr
auto isValid = [](auto f) {
    return [](auto&&... args) {
        return decltype(isValidImpl<decltype(f), decltype(args)&&...>(nullptr)){};
    };
};

template<class T>
struct TypeT {
    using Type = T;
};

template<class T>
constexpr auto type = TypeT<T>{};

template<class T>
T valueT(TypeT<T>);



int main() {

    constexpr auto isDefaultConstructible  
        = isValid([](auto x) -> decltype((void)decltype(valueT(x))()) {

        });

    isDefaultConstructible(type<int>);
    isDefaultConstructible(type<int&>);

    return 0;
}