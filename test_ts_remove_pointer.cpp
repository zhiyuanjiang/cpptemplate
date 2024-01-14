#include <iostream>

template<class T>
class RemovePointer {
public:
    typedef T Result;
};  

template<class T>
class RemovePointer<T*> {
public:
    typedef typename RemovePointer<T>::Result Result;
};

int main() {
    RemovePointer<int*>::Result t1 = 2;
    RemovePointer<int**>::Result t2 = 3;
    std::cout << t1 << " " << t2 << std::endl;
    return 0;
}