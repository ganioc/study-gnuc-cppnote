## PThread
首先用Linux c 来学习 <Pthread Programming >

```shell
/usr/aarch64-linux-gnu/lib/libpthread.so.0
/usr/include/pthread.h
/usr/include/boost/thread/pthread

```

concurrent programming , tasks can occur in any order,

parallel programming, refer to the simultaneous execution of concurrent tasks on different processors,

mutex,

sockets, shared memory, messages,

pthread_self(), pthread_equal()

pthread_exit()退出, pthread_cancel()取消其它的thread, pthread_detach()使thread detach

joinable thread, detached thread, 


concurrency:

- potential parallelism
- overlapping I/O
- asynchronous events
- realtime scheduling

Unix utilities:
- select system call
- signals
- nonblocking I/O
- setjmp/longjmp system call pairs,
- aio_read, aio_write, 

## chap 2 Designed Threaded Programs

* 响应异步事件
* computational, signal-processing applications on multiprocessing systems
* real-time, servers and multiprocessing applications

Models:
- boss/worker model
  - boss thread accepts input and pass specific tasks to more worker threads; boss loops until one arrives
  - for database servers, file servers, window managers
- peer model
  - workcrew model, have a fixed or well-defined set of inputs, matrix multipliers, parallel database search engines, prime number generators,
  - well defined input,
- pipeline model
  - a long stream of input
  - a series of suboperations, stages or filters, every unit of input must be processed
  - each processing stage handle a different unit of input at a time
  - image processing, text processing, 






