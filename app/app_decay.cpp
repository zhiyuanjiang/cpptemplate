#include <iostream>
#include <type_traits>

template<class T>
struct RemoveConst {
    using type = T;
};

template<class T>
struct RemoveConst<const T> {
    using type = T;
};

template<class T>
struct RemoveVolatile {
    using type = T;
};

template<class T> 
struct RemoveVolatile<volatile T> {
    using type = T;
};

template<class T>
struct RemoveCV : RemoveVolatile<typename RemoveConst<T>::type> {};

// 别名模板
template<class T>
using RemoveCV_t = typename RemoveCV<T>::type;

template<class T>
struct DecayT : RemoveCV<T> {};

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

