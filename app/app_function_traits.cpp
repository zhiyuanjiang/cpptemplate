#include <iostream>
#include <type_traits>
#include <functional>

template<class T>
class function_traits;

template<class F, class... Args>
class function_traits<F(Args...)> {
public:
    enum { arity = sizeof...(Args) };
    typedef F return_type;
    typedef F function_type(Args...);

    template<size_t N>
    using arg_type = typename std::tuple_element<N, std::tuple<Args...>>::type;
};

// 函数指针
template<class F, class... Args>
class function_traits<F(*)(Args...)> : public function_traits<F(Args...)> {};

// std::function
template<class F, class... Args>
class function_traits<std::function<F(Args...)>> : public function_traits<F(Args...)> {};

// 函数对象
template<class ClassName>
class function_traits : public function_traits<decltype(&ClassName::operator())> {};

// 成员函数
#define FUNCTION(...) \
template<class F, class... Args, class ClassName> \
class function_traits<F(ClassName::*)(Args...) __VA_ARGS__> : public function_traits<F(Args...)> {}; 
FUNCTION()
FUNCTION(const)
FUNCTION(volatile)
FUNCTION(const volatile)

template<typename T>
void PrintType(){
    std::cout << typeid(T).name() << std::endl;
}

int main(){
    std::function<int(int)> f = [](int a){return a; };
    PrintType<function_traits<std::function<char(long)>>::function_type>(); 
    PrintType<function_traits<std::function<int(int)>>::arg_type<0>>();
    PrintType<function_traits<decltype(f)>::function_type>();
}
