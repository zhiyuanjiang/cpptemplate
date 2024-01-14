#include <iostream>
#include <string>
#include <type_traits>

template<class T>
class Optional {
public:
    typedef typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type data_t;

    Optional() {}
    Optional(const T& val) {
        create(val);
    }
    Optional(const Optional& val) {
        // 先释放，再拷贝
        if(val.is_init()){
            destroy();
            _init = true;
            new (&_data) T(*(T*)(&val._data));
        }
    }
    ~Optional() {
        destroy();
    }

    // 可变参数进行初始化
    template<class... Args>
    void emplace(Args&& ...args) {
        destroy();
        create(std::forward<Args>(args)...);
    }

    explicit operator bool () const {
        return is_init();
    }

    const T& operator * () const {
        if(is_init()){
            return (*((T*)(&_data)));
        }
        throw std::logic_error("is not init");
    }

    bool is_init() const { return _init; }

private:
    void destroy() {
        if(is_init()){
            // 调用T的析构函数
            ((T*)(&_data))->~T();
            _init = false;
        }
    }

    template<class... Args>
    void create(Args&&... args) {
        _init = true;
        new (&_data) T(std::forward<Args>(args)...);
    }

private:
    bool _init = false;
    data_t _data;
};

struct MyStruct {
    MyStruct() {}
    MyStruct(int a, int b) : _a(a), _b(b) {}
    int _a;
    int _b;
};

int main() {

    Optional<std::string> a("ok");
    Optional<std::string> b("nok");
    Optional<std::string> c(b);

    if(a){
        std::cout << "a: " << *a << std::endl;
    }
    if(c){
        std::cout << "c: " << *c << std::endl;
    }
    
    Optional<MyStruct> ms;
    ms.emplace(2, 3);
    MyStruct tmp;
    if(ms){
        tmp = *ms;
    }
    std::cout << "ms: " << tmp._a << " " << tmp._b << std::endl;
    return 0;
}