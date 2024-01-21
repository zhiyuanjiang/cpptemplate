/*
*   template<bool B, class T = void>
*   struct enable_if;
*   判断条件B为true时，enable_if::type才存在，type默认为void
*/

#include <iostream>
#include <type_traits>

template<class T, class Enable = void>
class A;

// 偏特化，限定第一个参数只能是浮点型；注意这里没有对A进行定义。
template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {};

int main() {

    A<float> a;
    // A<int> b;

    return 0;
}