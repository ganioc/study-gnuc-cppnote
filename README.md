## README

a cpp project

Use meson to manage the project,

A single project which can compile , only in this situation can the intellisense function works well! 

```
/usr/include/c++/11


```

## chap 10, 诊断和调试
对任务的注释,
- TODO,
- HACK,
- UNDONE, 

```c
#error
__FILE__
__LINE__

#ifndef _DEBUG
标准exception类, 
```

输出调试信息, cerr, stderr, cout, stdout, 

cassert(), 

编写异常安全的类:
保护类的用户不会受到异常的影响。异常不是错误传播机制, 如果类中的方法执行失败，但是可以恢复，使对象的状态保持一致，应该使用返回值来指示。异常发生时，数据无效，这种状态是无法恢复的。

当异常发生时，有3个选项来应对,
- 允许异常在调用栈上传播，将处理异常的任务指派给调用方代码完成。
- 通过try代码抛出异常来保护代码，捕获已知的异常，并抛出
- 使用try保护所有代码, 捕获和处理所有异常，因此调用代码无需抛出任何异常


## Boost 提供6种智能指针

- shared_ptr
- weak_ptr
- scoped_ptr
- scoped_array
- shared_array
- intrusive_ptr







