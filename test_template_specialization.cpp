#include <iostream>
#include <functional>

/*
*   当模板实例化时提供的模板参数不能匹配到任何的特化形式的时候，它就会去匹配类模板的”原型“形式。
*   类模板和类模板特化的作用，仅仅是指导编译器选择哪个编译，但是特化和它原型的类模板之间，是分别独立实现的。
*/ 

// 模板定义
template<class T>
class PrintId {
public:
    static const int id = -1; 
};

// 模板特化
template<>
class PrintId<int> {
public:
    static const int id = 1;
};

template<>
class PrintId<void*> {
public:
    static const int id = 2;
};

template<>
class PrintId<std::function<void()>> {
public:
    static const int id = 3;
};

template<>
class PrintId<int8_t> {
public:
    static const int pid = 4;
};

template<class T>
void print(T) {
    std::cout << "id: " << PrintId<T>::id << std::endl;
}

int main() {
    // 原始模板
    print(3.14);
    // 特化模板
    print(2);
    print((void*)0);
    print(std::function<void()>([]{}));
    std::cout << "pid: " << PrintId<int8_t>::pid << std::endl;
    return 0;
}