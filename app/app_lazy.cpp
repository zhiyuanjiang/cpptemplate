#include <iostream>
#include <type_traits>
#include <optional>
#include <functional>
#include <memory>

template<class T>
class Lazy {
public:
    Lazy() {}
    // 保存需要延迟执行的函数
    template<class Func, class... Args>
    Lazy(Func&& func, Args&& ...args) {
        _func = [&func, &args...]{ return func(args...); };
    }
    T& value() {
        if(!_data){
            _data = _func();
        }
        return *_data;
    }
    bool is_create() const {
        return *_data;
    }

private:
    std::optional<T> _data;
    std::function<T()> _func;
};

template<class Func, class... Args>
Lazy<typename std::result_of<Func(Args...)>::type> lazy(Func&& func, Args&& ...args) {
    return Lazy<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(func), std::forward<Args>(args)...);
}

// test
struct BigObject {
    BigObject() {
        std::cout << "lazy load big object" << std::endl;
    }
};

struct MyStruct {
    MyStruct() {
        _obj = lazy([]{ return std::make_shared<BigObject>(); });
    }

    void load() {
        _obj.value();
    }

    Lazy<std::shared_ptr<BigObject>> _obj;
};

int foo(int x) {
    return x * 2;
}

int main() {

    int y = 4;
    auto lazy1 = lazy(foo, 4);
    std::cout << "lazy1: " << lazy1.value() << std::endl;

    Lazy<int> lazy2 = lazy([]{ return 12; });
    std::cout << "lazy2: " << lazy2.value() << std::endl;

    std::function<int(int)> f = [](int x){ return x+3; };
    auto lazy3 = lazy(f, 3);
    std::cout << "lazy3: " << lazy3.value() << std::endl;

    MyStruct t;
    t.load();
    return 0;
}