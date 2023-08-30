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

buffer,
  a shared buffer, in the process's global data region,
  a lock, synchronize the access to it, mutex variable as a lock
  a suspend/resume mechanism,using conditional variable
  state information, some flag or variable, indicate buffer length

producer, consumer, 

double buffering,

**ATM example**
client program

server program
  使用select来确定有多少channel have data, waiting to be read
  Using asynchronous I/O, 

communicate with Unix socket,

synchronization,同步:
- Accounts, 多个线程访问同一账号, 使用mutex variable
- Limiting the number of workers. 防止CPU overloading, 
- Server shutdown, 必须完成所有的任务之后，才能关闭server,

优化:
- thread pool, 
- interrupt , cancellation, boss thread可以关闭worker thread
- scheduling, 某些worker thread的优先级会更高一些,

**Matrix Multiplication Program example**
加快运算，2种方式, overlapping I/O, parallel processing,

## chap 3 Synchronizing Pthreads
线程的同步







