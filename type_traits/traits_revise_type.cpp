/*
*   类型转换traits
*   template<class T>
*   struct remove_const;      移除const
*   
*   template<class T>
*   struct add_const;   增加const
*   
*   remove_reference, remove_pointer...
*/

#include <iostream>
#include <type_traits>

int main() {

    std::cout << "int = const int : " << std::is_same<int, const int>::value << std::endl;
    std::cout << "int = remove_const<const int>::type : " << std::is_same<int, std::remove_const<const int>::type>::value << std::endl;
    
    std::cout << "const int = int : " << std::is_same<const int, int>::value << std::endl;
    std::cout << "add_const<int>::type = const int : " << std::is_same<std::add_const<int>::type, const int>::value << std::endl;
    return 0;
}