#include <iostream>
#include <string>
#include <type_traits>

template<class T>
void test_ref(T& val) {

}

template<class T, class = std::enable_if_t<!std::is_const_v<T>>>
void test_ref_nconst(T& val) {

}

// c++20的concept
template<class T>
requires (!std::is_const_v<T>)
void test_ref_nconst2(T& val) {

}

// template<class T>
// void test_ref_nconst2(T& val) requires std::is_const_v<T> {
    
// }

// template <typename T>
// void print(T t) requires std::is_integral_v<T> {
//     std::cout << t << std::endl;
// }


int main() {

    std::string a = "hello";
    test_ref(a);
    // test_ref(std::string("hello"));   // error, 无法将一个右值绑定到一个非const的左值
    // test_ref(std::move(a));           // error, 无法将一个右值绑定到一个非const的左值

    const std::string b = "hello";
    test_ref(b);
    // 为啥这里又ok了呢，因为变量b是const类型，函数模板的引用传参不会改变参数类型，
    // 所有T实际上是const std::string类型，那么test_ref此时支持右值类型的传入，在test_ref内部对val的修改是不被允许的
    // 我们可以明确的限制不能传入const类型的对象
    test_ref(std::move(b));    

    // test_ref_nconst(b);     // error，no type named ‘type’ in ‘struct std::enable_if<false, void>’
    return 0;
}