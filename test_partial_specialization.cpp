#include <iostream>
#include <memory>

/*
*   偏特化时的模板形参，和原型的模板形参没有任何关系。
*   和原型不同，它的顺序完全不影响模式匹配的顺序，它只是偏特化模式。
*/

template <typename T, typename U> struct X            ;    // 0 
                                                           // 原型有两个类型参数
                                                           // 所以下面的这些偏特化的实参列表
                                                           // 也需要两个类型参数对应
template <typename T>             struct X<T,  T  > {};    // 1
template <typename T>             struct X<T*, T  > {};    // 2
template <typename T>             struct X<T,  T* > {};    // 3
template <typename U>             struct X<U,  int> {};    // 4
template <typename U>             struct X<U*, int> {};    // 5
template <typename U, typename T> struct X<U*, T* > {};    // 6
template <typename U, typename T> struct X<U,  T* > {};    // 7

template <typename T>             struct X<std::unique_ptr<T>, std::shared_ptr<T>>; // 8

// 以下特化，分别对应哪个偏特化的实例？
// 此时偏特化中的T或U分别是什么类型？

X<float*,  int>      v0;                       
X<double*, int>      v1;                       
X<double,  double>   v2;                          
X<float*,  double*>  v3;                           
// X<float*,  float*>   v4;                          
X<double,  float*>   v5;                          
X<int,     double*>  v6;                           
// X<int*,    int>      v7;                       
X<double*, double>   v8;

int main() {

    return 0;
}