/*
*   条件选择的traits
*   template<bool B, class T, class F>
*   struct conditional;  
*   如果B为true，conditional::type为T，否则为F。
*/

#include <iostream>
#include <type_traits>

int main() {

    std::conditional<true, int, float>::type a = 1;
    std::conditional<false, int, float>::type b = 2.1;

    return 0;
}