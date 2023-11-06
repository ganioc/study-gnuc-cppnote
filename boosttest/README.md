

Boost.Asio: A library for asynchronous I/O and networking
Boost.Smart_pointers: A collection of smart pointer classes
Boost.Thread: A library for threading and synchronization
Boost.Regex: A regular expression library
Boost.Spirit: A library for parsing and generation of text
Boost.Bind: A library for creating function objects and bindings

如何得到Boost的版本呢?


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
* 在local使用, 作为一个local scope guard in function, 
* 也可以作为class member, 当类的成员发生异常时，如何安全地释放类成员的资源，动态分配的对象，成为一个难题。使用try/catch, 也不优雅。使用智能指针可以解决。

```cpp
boost::scoped_array
boost::scoped_array<byte> img(new byte[sz]);
```
特性:
* 用于处理legacy code with lots of dynamic arrays
* C++建议使用std::vectors over dynamic arrays

```cpp
std::unique_ptr
```
$C^{++}11$引入了std::unique_ptr智能指针模板, 代替过时的std::auto_ptr, 标准的unique_ptr可以和boost::scoped_ptr对应
* default-constructed unique_ptr包含一个null指针，nullptr,
* get(), 得到包含的指针
* swap(), 交换指针
* operator*, operator->访问成员

**ownership transfer using unique_ptr,**

**make_unique in C++14**
std::make_unique, create an object on dynamic memory and wrap it in std::unique_ptr, 
```cpp
std::unique_ptr<Logger> logger = 
    std::make_unique<Logger>(filename)
```

**shared ownership semantics**
有些情况下需要分享资源across multiple contexts,不同的上下文, 不知道具体的owner是谁?

例子:2个线程在一个进程里，读取内存中动态分配的数据的不同的部分，每个线程都会去处理数据、读取数据。当最后一个线程终止时，应该回收数据内存。但是哪一个线程应该来做回收动作呢?

用智能指针来封装buffer, 当索引计数为0时，自动回收buffer资源。

```cpp
boost::shared_ptr
std::shared_ptr
```
特性:
* 支持move semantics,
* as a class member,分享数据库连接给多个应用，可以使用shared_ptr,
* 可以放在多个STL container里面
* 可以由多个线程共享

**Non owning aliases**
boost::weak_prt, std::weak_ptr,
boost::make_shared, std::make_shared,

**intrusive smart pointers**
boost::intrusive_ptr,
reference count并不是share_ptr的一部分, 

# chap 4 Working with strings
文本数据通常表示为一个序列的，一组character, 或string, 分布在连续的内存空间，以null作为terminator. C++标准将字符串的概念抽象化,使用了class template std::basic_string, 
basic_string模板有3个参数:
* character type
* 一些intrinsic properties , behaviors of the character type 封装在trait class里
* an allocator type, 分配内部的数据结构

```cpp
template <typename charT
    typename  Traits = std::char_traits<chart>,
    typename Allocator = std::allocator<chart>>
std::basic_string;
```
C++03有, 
```cpp
std::string, narrow characters, 8-bit char
std::wsting, wide characters, 16 or 32-bit wchar_t
```
C++11,
```cpp
std::u16string, u16char_t
std::u32string, u32char_t
```
plain old C-style strings, POC, char, wchar_t, in legacy C++code,

transform, algorithm, 算法转换
boost:to_upper, 看起来更好理解一些,
Boost.Range, 
boost::iterator_range, 使用一对iterator,来表示不同种类的ranges,
boost::contains, 
find algorithms,
```cpp
boost::find_first
boost::find_last
boost::find_nth
boost::find_all,
boost::find_token(), 查找词，也就是token,
boost::iter_find,
boost::find_regex,
boost::find,
boost::find_head, 获取字符串里的一部分
boost::find_tail, 带offset的,
boost::start_with,
boost::ends_with,
boost::equals,
boost:contains,

```
What is a functor?
>函数对象

boost range lib, 

trimming algorithms
```cpp
boost:trim_left
boost::trim_right
boost::trim
```

replace and erase algorithms,

split and join algorithms

**Regular expressoin**
boost::regex,

# chap 5 Effective Data Structures beyond STL
标准库的通用容器
```cpp
std::vector
std::deque
std::list
std::forward_list
```
ordered and unordered associative containers
```cpp
std::map
std::set
std::unordered_map
std::unordered_set
```
访问使用iterators, 
>read, write, forward traversal,bidirectional traversal, random access. 根据，依赖the internal structure of a container

Standard Template Library, STL, 
Developed at HP Labs by Alexander Stepanov and Meng Lee, 在1994年接纳为C++语言的一部分, 
C++ heavily used STL containers and algorithms,Boost提供了一些有用的库弥补这些gap,

**Boost Container library**
什么对象能够存储在STL container里，什么不能呢？

std::vector, object对象类型T,必须是一个完整的类型, 不能只是declared, 必须完整定义了的, 
一般来说，在C++11之前, type T的对象object 必须是copyable 和assignable的。container拷贝-intensive framework. 
到了C++11, 引入了move 语法, 使得move-construct new objects, by 移动，usruping the state of an exisiting object, 类似的, object的状态、内容可以被移动到另一个存在的对象里，通过move-assignment操作。C++11还运行对象直接在容器里面建立，而不是先生成再拷贝。

**Move-awareness and in-place construction**
使用Boost move emulation macros to define its move semantics. 

```cpp
rvalue // C++ rvalue reference syntax,
boost::move // explicitly move
```
move-aware containers, very similar to C++11 counterparts, 

**Nonstandard containers**
Flat associative containers
分为2种, 
ordered , 
>std::set, std::multiset, std::map, std::multimap,

一般是使用平衡搜索树来实现的，de facto实现标准是，优化了的红黑树, 是按照排列的顺序存储成员的,因此是有序的。

unordered,
>std::unordered_set, std::unordered_multiset, std::unordered_map, std::unordered_multimap, 

一般是用hash表来实现的，in an array of buckets, 根据对象的值的hash结果来进行检索的。

Associative 容器支持快速查找，有序容器使用平衡的搜索树支持对数时间的搜寻，hash表支持固定时间的搜索, 

Binary search on sorted sequence允许随机位置的访问，同样支持对数时间的搜索, 
```cpp
flat_set,
flat_multiset,
flat_map,
flat_multimap,
```
Flat associative containers, 可以存储既不copyable也不movable的对象。对象存储在连续地址的内存里面，不使用指针。比使用tree-based, hash-based的容器更加节省内存。

**slist**
a singly-linked list abstraction similar to container template in SGI STL implementations, std::list是一个双向链表,C++11引入了单向链表std::forward_list,slist是move-aware的，

**splicing**
in constant time, spice, 

**stable-vector**
std::vecotr, 标准库是不稳定的, 
moot:无考虑意义,

**boost.assign**
存放指针的容器, ptr_vector,自动回收，并处理exception,

**boost.iterator**
Iteration pattern, a framework for writing iterators for custom classes that conform to the standards and are compatible with algorithms in the Standard Library. more abstract object collections, not limited to containers.

iterator adaptors,
- Filter iterator, boost::make_filter_iterator, 
- Transform iterator, boost::make_transform_iterator, 
- Function output iterator, 

binary search tree. the left subtree of a node are smaller than the node, all elements in the right sub-tree of a node are larger than the node. Nodes with zero children are called leaves. A threaded binary search tree is optimized for traversing its elements in a sorted order, the so-called inorder traversal.

- bidirectional iterator , allow forward and reverse traversal of the tree in the order of its elements,

boost::iterator_core_access, 派生,生成自己的iterator, 
- dereference function, 
- equal(), 
- begin()
- end(), 

# chap 6 Bitmap and Multi-index containers
标准库具有ordered, unordered associative containers for storing objects and looking them up efficiently using some *key*.
ordered-container
```cpp
std::set, std::map,
```
unordered-container
```shell
compute a integer hash value for each key, 
``` 
根据不同的索引值进行搜索, 

## Containers for multi-criteria lookups



## Boost Multi-index containers


## Boost Bitmap
Standard Library has ordered and unordered associative containers for storing objects and looking them  up efficiently using some key.

key可以是
text type, 
numeric type,
first-class objects,

std::set, 
>不能有重复

std::multiset
>可以有重复,

index types,
>sequenced index, random index,  

**containers for multi-criteria lookups**

**boost multi-index containers**

**boost bimap**
lookup table abstraction
std::map
std::multimap,
to look up a key given a value, 从值查找key,
bimaps,  bidirectional mapping, 

Collection types:
除了one-to-one mapping,还支持one-to-many, many-to-many mappings, 这不就是个数据库吗？

|  Collection Types   | Semantics  | View Types |
|  ----  | ----  | ---- |
| set_of  | ordered, unique |  map    |
| multiset_of | Ordered, non-unique | multimap |
| unordered_set_of| Hashed ,unique| unordered_map  |
| unordered_multiset_of| Hashed, non-unique|unordered_multimap|
| unconstrained_set_of| Unconstained| No view available |
| list_of | Non-ordered, non-unique |Linked list of ky-value pairs|
| vector_of | Non-ordered, non-unique,random access sequence| vector of key-value pairs |

**projections**

# chap 7 Higher Order and Compile-time Programming
callback entities, function objects, 回调对象，函数对象, functors,

将一个函数对象作为参数传给算法, 
也可以返回一个函数对象,
give rise to higher order transforms, 高阶变换,
higher order programming: 传送,返回函数，

C++ templates, 模版, 这种编程模式, style, 被称为: compile-time programming or template metaprogramming,
编译时编程，模版元编程
Boost Phoenix Library, C++ 11 facilites, bind and lambda,
在编译时使用的template metaprogramming, 
Domain Specific Embedded Languages,

generic programming techniques,

functor,
是一个类、结构体, 定义了重载的function call operator,
predicate,
takes one or more arguments and maps them to a Boolean truth value
arity,
number of arguments it takes,
nullary, 无参数，
unary,单一参数
binary, 两个参数
pure function, with no side effects,

**lambda**
[](){}, lambda captures,
=， 访问scope里的所有变量,
&var, 访问某一个变量, as a reference,

High-level C++ API, 
The client of your API must register for the types of messages it is interested in and pass a callback - a function object. 
Your API could be a member of a Queue class.

Boost.Function library,
std::function, C++ 11,
C++ 11 variadic templates,
calling scope, accessible in another scope via the lambda capture,
dynamic scoping, 
closures, 
delegates, callbacks especially bound to specific objects are called.

还是应该来学习现代C++，

**partial function**
boost::bind(pow, _1, 3), a wrapper function, 
>bind a member funciton to an object instance,
boost::mem_fn, std::mem_fn(),

reference,
pointer,
smart pointer,

**Compile-time programming**
模版可以允许写C++ code, 与输入参数的类型无关，thus work unchanged with a large family of types. 

* function templates
* class templates,
* struct templates,

C++ templates, 强大的计算子系统，查看数据类型,
glean their properties,
write sophisticated recursive and branching logic
at compile time,

提供generic interfaces, highly optimized for each type operate upon

```cpp
boost::lexical_cast<double>(strPi);
```
Boost Type Traits Library,

decltype, computing the type of an expression,
boost::is_pod, Plain Old Data type, 
boost::true_type,
boost::false_type,
对于基础数据，可以进行shallow copy, or memcpy; non-POD type, to perform element by element copies,

boost::is_base,
boost::is_copy_constructable,
boost::has_pre_increment,
boost::is_same,

**SFINAE**
Substitution Failure is Not An Error, 
>no candidates, or ambiguity,

模版里面的overload resolution set, 
boost::enable_if
boost:;disable_if,

**Boost Phoenix**
Boost Phoenix 3 is a library for enabling functional programming constructs in C++. DSEL, domain specific embedded language,
lazy expressions, expression templates,

Boost Spirit Parser Framework,
actors:
>abstractions for lazy functions. Used to generate unnamed functions or lambdas. composed to generate more complex functors. In that sense, Phoenix is a lambda language library.

Actors are categorized based on functionality and exposed through a set of header files. 

ref:
>to create a lazy mutable variable reference

cref:
>generates a lazy immutable reference

arithmetic, +,-
comparison, <,==,>
logical, &&, ||,
bitwise operators, |,^,&,

boost::phoenix::ref
>generate an actor for lazily evaluating the variable , and cache it in a varible x.
boost::phoenix::val,
boost::phoenix::placeholders::_1, _2, etc.

**Boost Spirit Parser Framework**
a popular DSEL used for generating lexers and parsers.
生成C or C++ code from a language neutral specification in the Extended Backus-Naur Form (EBNF),
Uses only the C++ compiler to generate parsers, 解析器,
Spirit makes heavy use of template metaprogramming, resulting in slower compile time sbut generates parsers that are efficient at runtime.

Spirit包含
- Spirit Lex, a lexer, 词法分析器,
- Spirit Qi, a parser, 
  - parse text data according to some specified gramma
  - verifying that the input conforms to the grammar
  - decomposing a conforming input into meaningful semantic components
- Spirit Karma, a generat, 

to build powerful data translation enginers,

Predefined parsers,
- Integers
- Real numbers
- Boolean
- Characters,
- Strings,

Spirit defines a number of overloaded operators, called parser operators,

# chap 8 Date and Time Libraries
时间，以及测试代码性能, 

**Boost Date Time**
时间系统的分辨率, Resolution,


**Boost Chrono**
用来测量时间。与std::chrono, 大部分功能兼容。
```cpp
boost::ratio
boost::chrono::duration<>
```
Clocks and time points,
Unix, POSIX epoch January 1, 1970 00:00:00 UTC,
```cpp
duration
time_point
now,
// clocks
system_clock, // wall clock, system time
steady_clock, // monotonic time system,
high_resolution_clock,x  // 高精度时钟
```
编译时，可能需要链接的库, 
```cpp
-lboost_system -lboost_timer -lboost_chrono -lrt

process_real_cpu_clock // measruing the total time since a program started
process_user_cpu_clock // the time a program runs for in the user space
process_system_cpu // measuring the time the kernel runs some code on behalf of the program
thread_clock // total time for which a particular thread is scheduled. BOOST_CHRONO_HAS_THREAD_CLOCK preprocessor macro is defined
```

**Boost Timer**
测量代码运行时间，性能,
a separately compiled library, not header-only, internally uses Boost Chrono
```cpp
boost::timer::cpu_timer
boost::timer::auto_cpu_timer
``` 
需要用到boost::timer库, start(), resume(), stop()

# chap 9 Files, Directories and IOStreams
Provide programmatic accesss to OS substystem. Boost libraries for performing input and output, and interacting with filesystems. 

编写可以移植的C++程序，与文件系统交互，使用标准接口来进行I/O操作。
Boost支持Linux, Windows, Mac OS, BST variants. 

文件路径:
```cpp
boost::filesystem::path

```
parent path, the path stripped of the filename
relative path, the path following the leading slash
extension, 包含period or dot,
stem, the path is the stem
root name,
root directory, leading backslash following the root name,
root path, 

遍历目录结构:
生成目录
```cpp
boost::filesystem::create_directories()
::create_directory_symlink(target, link)
::create_symlink(target, link)
::copy_file( )
::copy_symlink(), 
::copy_directory()
fs::directory_iterator
boost::filesystem::rename(const path& old_path, new_path)
::remove(path& p)
::remove_all(p)
```

Path-aware fstreams

## Extensible I/O with Boost IOStreams
### Architecture of Boost IOStreams
Boost IOStreams library, a framework for operations of all kinds on all manner of devices. With a simpler interface for extending I/O facilities to newer devices. 标准的IOStream框架，提供了两个基本的抽象:
- streams, 
>提供了一个同意的接口来读写a sequence of characters在底层的设备之上
- stream buffers
>提供了一个lower-level抽象，实际设备device, 被之上的streams调用

Boost提供了
```cpp
boost::iostreams::stream
boost::iostreams::stream_buffer 模版
```
提供了一些概念和抽象
```cpp
source, an object from which a sequence of characters can be read
sink, an object to which a sequence of characters can be written
device, a sink, source or both
input filter, modifies a sequence of characters read from a source
output filter, modifies a sequence of characters before it is written to a sink
filter, an input or output filter, known as a dual use filter
```
为了在device上实施I/O操作, 我们在stream, stream_buffer上联系上一组zero or more filters plus the device. 
A sequence of filters 称为 chain,
一组filters加device at the end, 称为complete chain,

**Using devices,**
```cpp
fstreams
boost::iostreams::file_descriptor_source
boost::iostreams::file_descriptor_sink
boost::iostreams::file_descriptor device
```

device reading writing memories

boost_iostreams

```cpp
template<class Device, class Tr, class Alloc>
struct stream

array_sink
back_insert_device, // buffer可以增长
tee_device, // write to 2 devices at the same time
```
遇到问题了，有可能是Boost库不兼容的问题,折腾了半天，发现原来是因为没有包含stream.hpp头文件。改了就好了，与库版本无关。

std::ends, array is terminating null character
std::flush, make sure the content is not held in the device buffer, before we call strlen.

**Using Filters**
Do a variety of things, like
* tagging keywords
* translating text
* performing regular expression substitution
* performing compression or decompression
* observer filters can compute line and word counts
* compute a message digest among other things

必须使用filtering streams, filtering stream buffers, 形成一个chain

Basic filters

Grep Filter

Compression Filters, gzip, zlib, bzip2 formats.

gzip and zlib, DEFLATE algorithm for compression
bzip2 使用更加节省空间的 Burrows-Wheeler algorithm, 

压缩和解压缩,
使用filtering_stream 进行串联, 

**composing filters**
Form a pipleline strating with the outermost filter, inserting the filters in the desired order, and ending with the device.

使用|来连接pipeline, 有点像那个GStreamer,

# chap 10 Concurrency with Boost
























