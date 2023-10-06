## smart pointer,

```shell
# 只能在作用域内使用，无法转移所有权,
scoped_ptr

# 不提供index指针
scoped_array

# 用来取代auto_ptr,可以代理new对象也可以代理数组对象,
# 不允许拷贝构造和拷贝赋值, 
unique_ptr

# 带有引用计数, 可以被安全共享,
shared_ptr
make_shared<T>

# 没有*, ->操作符重载,
shared_array

# 桥接模式

# 工厂模式
# 包装了 new 操作符的使用,

# assistant, 获得资源的观测权, 
weak_ptr

# 一个侵入式的引用计数型指针, 
# 1. 对内存占用的要求非常严格，要求必须与原始指针一样
# 2. 现存代码已经有了引用计数机制管理的对象
intrusive_ptr

```

## pool
内存池库, 可以返回一个简单数据类型的内存指针,用于简单数据

```shell
# 用户定义的内存分配器, default_user_allocator_new_delete
UserAllocator
```

## object_pool
类实例的内存池,

## chap 2 Boost's Utilities
Boost.Optional, may or may not have a value,

Boost.Tuple, ordered sets of heterogeneous values, generalization of std::pair,

metafunction, type computation,

POD, Plain Old Data types, 


Variant,

Any, 用来代替union, 也就是一个变量可以有几种类型之一,

**recursive_variant**

**Boost.Any**
支持任意数据，必须支持RTTI, Runtime Type Identification(RTTI), 
存储numerica data, character arrays, non-POD (Plain Old Data) type objects,
```c
boost::any_cast; // 进行数据类型的强制转换
```

**Boost.Conversion**
需求，将文字转为数字类型，根据数字类型输出为不同的文本形式。
如基本的转换函数
```c
atoi, strtol,strtod, itoa, ecvt, fcvt,
boost::lexical_cast<>()
```
在类型之间做转换, 广义的类型转换句法, extended to arbitray types?

**处理命令行参数**
Boost.Program_Options library,

- short option, -U, 
- long option,  --unified, --unified=5
- switch or flag, -p, -pN, two switches, 

几条规则:
- short options, 开始以single hyphen
- long options, 开始以double hyphens
- short options, option-values 中间以空格隔开
- long options, option-values,中间以等号隔开
- 将short switches 写在一起

对于POSIX-compliant 系统，这就是标准的表达方式，如Linux. Windows下的表达又有所不同，使用Boost库的话，可以帮助我们处理这些平台选择的问题。

parsing positional parameters,
多个value, multitoken(),

Boost还包括一些微库, micro-libraries, 提供一些有用的功能。这些库放在Boost.Utility, 和Boost.Core下面。

查看**compile-time check**信息
BOOST_CURRENT_FUNCTION,


