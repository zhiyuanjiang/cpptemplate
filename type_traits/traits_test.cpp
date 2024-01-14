#include <iostream>
#include <type_traits>


int main() {

    int v = 2;
    std::cout << std::is_integral<int>::value << std::endl;
    
    return 0;
}
