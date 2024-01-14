#include <iostream>
#include <utility>
#include <type_traits>

template<class FROM, class TO>
struct IsConvertibleHelper {
private:
    static void aux(TO);

    template<class F, class = decltype(aux(std::declval<F>()))>
    static std::true_type test(void*);

    template<class>
    static std::false_type test(...);

public:
    using Type = decltype(test<FROM>(nullptr));
};

template<class FROM, class TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO>::Type {};

template<class FROM, class TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::Tyep;

template<class FROM, class TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;

int main() {

    std::cout << IsConvertibleT<int, int>::value << std::endl;
    std::cout << IsConvertibleT<int, std::string>::value << std::endl;
    std::cout << IsConvertibleT<char const*, std::string>::value << std::endl;
    std::cout << IsConvertibleT<std::string, char const*>::value << std::endl;
    
    return 0;
}