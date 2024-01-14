/*
*   获取可调用对象返回值类型的traits
*   template<class F, class... ArgTypes>
*   class result_of<F(ArgTypes...)>;
*   第一个模板参数是可调用对象，第二个模板参数是参数的类型
*/

#include <iostream>
#include <type_traits>

int fn(int) { return int(); }  // function
typedef int(&fn_ref)(int);  // funciton reference
typedef int(*fn_ptr)(int);  // function pointerr
struct fn_class { int operator()(int i) { return i; }};

int main() {

    typedef std::result_of<decltype(fn)&(int)>::type A;
    typedef std::result_of<fn_ref(int)>::type B;
    typedef std::result_of<fn_ptr(int)>::type C;
    typedef std::result_of<fn_class(int)>::type D;

    return 0;
}