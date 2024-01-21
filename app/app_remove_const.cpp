#include <iostream>

template<typename _Tp>
struct RemoveConst { typedef _Tp type; };

template<typename _Tp>
struct RemoveConst<_Tp const> { typedef _Tp type; };


int main() {

    RemoveConst<const int>::type a = 2;
    return 0;
}