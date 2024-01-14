/*
*   比较两种类型traits
*   
*   template<class T, class U>
*   struct is_same;
*   判断两个类型是否想等
*   
*   template<class Base, class Derived>
*   struct is_base_of;
*   判断Base类型是否是Derived类型的基类
*   
*   template<class From, class To>
*   struct is_convertible;
*   判断前面的模板参数能否转换成后面的模板参数类型
*/

#include <iostream>
#include <type_traits>


class A {};
class B : public A {};
class C {};


int main() {
    std::cout << "int = int: " << std::is_same<int, int>::value << std::endl;
    std::cout << "int = double: " << std::is_same<int, double>::value << std::endl;
    
    std::cout << "B is derived of A: " << std::is_base_of<A, B>::value << std::endl;
    std::cout << "C is derived of A: " << std::is_base_of<A, C>::value << std::endl;

    std::cout << "B can convert to A: " << std::is_convertible<B, A>::value << std::endl;
    std::cout << "C can convert to A: " << std::is_convertible<C, A>::value << std::endl;
    return 0;
}