## Optional实现
Optional声明
```c++
template<class T>
class Optional;
```
### 实现功能
实现一个Optional类，提供一些功能：
* 构造函数
* 拷贝构造函数
* 提供一个`emplace`方法构造Optional
* 析构函数
* `bool`运算符重载
* `*`运算符重载

### 实现方案
* 需要一个标志判断`Optional`中是否包含对象
* 需要开辟一个内存对齐的缓存区，用来保存需要存储的对象

## Any实现
**Any**是一个只能容纳一个元素的容器，可以付给它任意类型的值，也能将该值进行还原。
### 实现功能
* 任意类型元素的赋值。
* 元素的还原，实现一个`any_cast<T>`的函数。
### 实现方案
* 需要一种通用的方式能保存所有类型的数据。这里可以利用继承来实现，基类不包含模板参数，派生类才包含模板参数，这个模板参数就是赋值的类型。用一个基类指针来指向包含的数据。
* 如果想要对元素进行还原，需要记录原本数据的类型，用`type_index`来保存，`typeid`获取数据类型。

## function_traits实现
**function_traits**能获取函数的一些相关信息，例如函数类型、返回类型、参数个数和参数具体的类型。
### 实现功能
* 获取函数类型
`function_traits<decltype(func)>::function_type;`
* 获取函数返回值
`function_traits<decltype(func)>::reture_type;`
* 获取函数的参数个数
`function_traits<decltype(func)>::arity;`
* 获取函数的第一个参数
`funciton_traits<decltype(func)>::arg_type<0>;`