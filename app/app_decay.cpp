#include <iostream>
#include <type_traits>

// remove const volatile
template<class T>
struct DecayT : std::remove_cv<T> {};

// 数组退化成指针
template<class T>
struct DecayT<T[]> {
    using type = T*;
};

template<class T, size_t N>
struct DecayT<T[N]> {
    using type = T*;
};

// 函数类型退化成函数指针
template<class F, class...Args>
struct DecayT<F(Args...)> {
    using type = F(*)(Args...);
};

template<class T>
void print() {
    using type = typename DecayT<T>::type;
    if(std::is_same_v<type, int>){
        std::cout << "type: int" << std::endl;
    }else if(std::is_const_v<type>){
        std::cout << "type: const" << std::endl;
    }else if(std::is_pointer_v<type>){
        std::cout << "type: pointer" << std::endl;
    }else{
        std::cout << "aaa" << std::endl;
    }
}

int main() {
    print<int>();
    print<const int>();
    print<const volatile int>();
    print<int[]>();
    print<int(int)>();
    return 0;
}

