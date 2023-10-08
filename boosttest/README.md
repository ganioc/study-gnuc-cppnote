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

**BOOST_CURRENT_FUNCTION**
在打印调试信息时，如果能打印函数名称等信息的话，非常有用。再编译时，这些函数的名字、信息，编译器是很清楚得。不同编译器对这些信息的处理是不一样的。

使用的语法非常简单！即可
```cpp
cout << BOOST_CURRENT_FUNCTION << endl;
```

**Boost.Swap**
a useful micro library part of BoostCore,

ADL(Argument Dependent Lookup), 

**Compile-time asserts**
在代码的某个位置要求某些条件被满足，to find errors at compile time.

```c
#include <cassert>
assert();
#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT();
```
MPL, Boost Metaprograming Library 
Boost TypeTraits library

**Diagnostics using preprocessor macros**
在我的软件工程师生涯里，曾经做过相当一些项目，某些代码要运行在5个不同的Unix版本和Windows平台上。编译服务器的配置不同。最好的办法就是使用preprocessor macros, 来打印编译信息:
* compiler names
* compiler version,
* architecture,
* likes at program startup,

找到编译器不匹配的地方。

```Cpp
Config library
Predef library
```
在编译时找到编译环境的信息, 


# chapt 3 Memory Management and Exception Safety
C++保留了指针，访问内存地址，提供手动内存管理, new, delete. 
C++代码经常处理操作系统资源的handlers,
* heap memory
* open files
* sockets
* threads
* shared memory,

获得这些资源，忘了释放的话，会带来不期望的后果，insidious bug, memory leak, deadlocks.

将指针包装成为dynamically-allocated objects, 使用*smark pointers*智能指针, exception-safe code, 

**动态内存分配**

**exception safety,异常安全**
The Abrahams Exception Safety Guarantees, Dave Abraham , cofounder of Boost,
- basic guarantee, 
  - An operation terminated midway preserves invariants and does not leak resources
- Strong guarantee
  - An operation terminated midway will not have any effect, that is, the operation is atomic,
- No-throw guarantee,
  - An operation that cannot fail

解决办法是使用RAII(Resource Acquision is Initialization), RAII建议以下模型来将资源包裹起来，避免手动管理,
- Encapsulate resource acquisition in the constructor of a wrapper object
- Encapsulate resource release in the destructor of the wrapper object
- Additionally, define consistent copy and move semantics for the wrapper object or disable them

如果wrapper object是在栈上建立的，它的destructor的调用，要么来自正常的exit,或者exit due to exceptions. 否则wrapper object应该按照RAII的原则来管理。

在发生异常时，在stack上分配的对象，还是会调用destructor,

**智能指针**
```cpp
boost::scoped_ptr,
boost::scoped_ptr<Widget> wgt(new Widget);
boost::checked_delete();

```
在scope范围内有效，出了scope,自动调用delete, 
特性:
* 不能被copy，
* 任何时间都只能有一个instance, 
* exhibit unique ownership semantics,语义学
* 不能放在C++的标准container里面使用
* 最简单的形式, lightweight, versatile smart pointer, scope guard







