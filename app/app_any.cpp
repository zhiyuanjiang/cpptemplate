#include <iostream>
#include <type_traits>
#include <memory>
#include <typeinfo>
#include <typeindex>

class Any {
public:
    Any(void) : _data_index(typeid(void)) {}
    Any(Any& rhs) : _data_ptr(rhs.clone()), _data_index(rhs._data_index) {}
    Any(Any&& rhs) : _data_ptr(std::move(rhs._data_ptr)), _data_index(rhs._data_index) {}

    template<class T, class = typename std::enable_if<!std::is_same<typename std::decay<T>::type, Any>::value, T>::type>
    Any(T&& rhs) : 
        _data_ptr(new Derived<typename std::decay<T>::type>(std::forward<T>(rhs))), 
        _data_index(typeid(typename std::decay<T>::type)) {}

    template<class T>
    bool is() const {
        return _data_index == std::type_index(typeid(T));
    }

    template<class T>
    T& any_cast() {
        if(!is<T>()){
            std::cout << "can not cast " << typeid(T).name() << " to " << _data_index.name() << std::endl;
            throw std::bad_cast();
        }
        auto derived = dynamic_cast<Derived<T>*>(_data_ptr.get());
        return derived->_data;
    }

    Any& operator=(const Any& a) {
        if(_data_ptr == a._data_ptr){
            return *this;
        }
        _data_ptr = a.clone();
        _data_index = a._data_index;
        return *this;
    }

private:

    class Base;
    using BasePtr = std::unique_ptr<Base>;
    class Base {
    public:
        // virtual ~Base();
        virtual BasePtr clone() const = 0;
    };
    template<class T>
    class Derived : public Base {
    public:
        // 这里不用模板直接报错了，没懂。
        template<class U>
        Derived(U&& val) : _data(std::forward<U>(val)) {}
        BasePtr clone() const {
            return BasePtr(new Derived<T>(_data));
        }
        T _data;
    };

    BasePtr clone() const {
        if(_data_ptr){
            return _data_ptr->clone();
        }
        return nullptr;
    }

    BasePtr _data_ptr;
    std::type_index _data_index;
};

int main() {
    Any n;
    std::string s = "hello";
    n = s;
    auto t = n.any_cast<std::string>();
    std::cout << t << std::endl;
    n = 1;
    n.is<int>();
    return 0;
}