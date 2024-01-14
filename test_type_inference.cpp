/*
*   在推断的时候自动类型的转换是受到限制的：
*   1 调用参数按引用传递：任何类型转换都不被允许
*   2 调用参数按值传递：只有退化（decay）这一类简单的转换被允许，const和volatile限定符会被忽略，引用类型的引用符号被忽略，
*   数组和函数被转换成指针类型。
*/

#include <iostream>
#include <type_traits>

template<class T>
void test(T a) {

    if(std::is_same<T, int>::value) {
        std::cout << "int type" << std::endl;
    }

    if(std::is_same<T, int*>::value) {
        std::cout << "int* type" << std::endl;
    }

}

// template<class F, class... Args>
// void test(F(Args...)) {
//     std::cout << "function type" << std::endl;
// }

template<class F, class... Args> 
void test(F(*)(Args...)) {
    std::cout << "function pointer type" << std::endl;
}

template<class T1, class T2>
auto max(T1 t1, T2 t2) -> decltype(t1 < t2 ? t2 : t1) {
    return t1 < t2 ? t2 : t1;
}

void add(int, int) {

}

typedef void (*tptr)(int, int);
typedef decltype(add) tp;

int main() {
    test(2);
    int a[2];
    test(a);
    const volatile int b = 2;
    test(b);
    const int& c = 2;
    test(c);
    tptr d = add;
    test(d);
    // 为啥无法传入一个函数类型
    // test(tp);

    int t1 = 5;
    double t2 = 3.1;
    auto t3 = max(t1, t2);
    if(typeid(decltype(t3)) == typeid(int)){
        std::cout << "int" << std::endl;
    }else if(typeid(decltype(t3)) == typeid(double)){
        std::cout << "double" << std::endl;
    }
    return 0;
}