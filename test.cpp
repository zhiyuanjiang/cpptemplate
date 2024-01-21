#include <iostream>
#include <vector>
#include <type_traits>

class EmptyClass {
    using Int = int;
};

class EmptyTwo : public EmptyClass {

};

class EmptyThree : public EmptyTwo, public EmptyClass {

};

int main() {
    
    std::cout << "size: " << sizeof(EmptyClass) << std::endl;
    std::cout << "size: " << sizeof(EmptyTwo) << std::endl;
    std::cout << "size: " << sizeof(EmptyThree) << std::endl;

    return 0;
}