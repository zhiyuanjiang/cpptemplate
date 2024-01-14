/*
*   类型判断traits
*/

#include <iostream>
#include <type_traits>

template<class T>
typename std::remove_cv<typename std::remove_reference<T>::type>::type*
    create() {
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type U;
    return new U();
}

// 对于普通类型，decay就是用来去除引用、const、volatile修饰符的
template<class T>
typename std::decay<T>* 
    create2() {
    typedef typename std::decay<T>::type U;
    return new U();
}

int main() {

    std::cout << "int = int: " << std::is_integral<int>::value << std::endl;
    std::cout << "double = int: " << std::is_integral<double>::value << std::endl;

    std::cout << "float = float: " << std::is_floating_point<float>::value << std::endl;
    std::cout << "double = float: " << std::is_floating_point<float>::value << std::endl;

    std::cout << "void* = pointer: " << std::is_pointer<void*>::value << std::endl;
    std::cout << "int& = ref: " << std::is_reference<int&>::value << std::endl;

    return 0;
}