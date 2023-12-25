## System Programming

book
- "<< Hands-on System Programming with C++ >>"

使用系统调用的API的程序，就被称为系统编程。通过调用操作系统的API实现功能的程序就叫做系统程序，这种行为就是系统编程。

**system call anatomy**
```c
int 13
iret
```
中断很慢。为了解决这个问题，现代的Intel X86 CPU提供了快速系统调用指令, Fast System call instructions. 
POSIX-compliant operating system. 

console input/output
stdout, stderr, 应用程序调用一个API来输出到stdout. 可以用几种方式来实现:
* Writing to a dedicated file handle, stdout
* Using C API such as printf
* Using C++ APIs such as std::cout
* Forking an application that outputs to stdout , such as using echo

由于应用程序调用的是系统调用，所以操作系统可以自由第将数据传送给serial device, log file, input to another application ,and so on.

这种灵活性是POSIX-compliant操作系统功能强大的原因。

**Memory Allocation**
内存分配， 

**File i/o**
读写文件，使用系统调用来读写character, block设备。可以是一个storage device, console device, 甚至是一个虚拟设备/dev/random.

**Networking**
NIC, Network Interface Controller, 

**Time**

**Threading and process creation**

**SYSRET**
fast system call, 在中断发生并返回时。a non-maskable-interrupt (NMI) could fire between the operating system loading the application's stack and the execution of SYSRET. 

**Meltdown and Spectre**
Kernel's memory mapped into each applicaiotn using a memory layout technical 3:1 split. Modern CPU会锁死内存的kernel空间, 只有kernel才能够访问全部内存空间。
一项技术Speculative execution, 

**Type safety in C++**
标准C不是type-safe语言。
C++还会提供RTTI, run-time type information. 这些信息有许多用途, 最重要的用途是dynamic_cast<> operator, 进行runtime type checking. 

* Polymorphic type conversions,
* Exception support, 

**C++对象**
RAII， Resource Acquisition Is Initialization, 
GSL Refresher,
用这些级数来避免很多C++编程的问题。

**模版**
Templates used in C++,

定义了操作系统的ABI, with a well defined API. 我们将讨论3种标准
- C 标准
>定义了程序的链接和执行标准，C语法, C库，提供ABI-to-API wrapper. C库可以认为是POSIX标准的一个子项，提供了不局限于filesystem, network, threading库

- C++ 标准
>定义了C++语法，程序链接和执行, C++库提供更高层的抽象对C和POSIX标准。这里讨论C++ 17

- POSIX 标准





