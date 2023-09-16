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

出问题, in one of hundred times, single indivisible transaction, atomic,

race condition, 

* pthread_join
* mutex variable functions, mutual exclusion, 
* condition variable functions
* pthread_once, 

同步方式：
* Reader/writer exclusion, 多个线程同时读取数据，保证任何写线程拥有对访问的绝对控制权
* Threadsafe data structures, 数据结构里就包含了同步的原语
* Semaphore, semaphores, 信号量, coutning semaphore, 


pthread,
```shell
pthread_mutex_lock
pthread_mutex_unlock,
pthread_mutex_trylock,
pthread_once,

```

* Direct access to data and resources. 并不是特别的高效。
* Reader/writer locks, 
* recursive lock, 可以反复被调用者lock, recursive mutex, 进入代码段时只是简单地增加计数值，而不会做任何操作系统级别的行为



event synchronization, 


mutex的竞争,
  选择哪一个thread呢, 是根据individual thread的scheduling priorities, 任务调度优先级,
priority inversion,
  低优先级thread锁住了高优先级thread需要的lock, 

多个线程访问linked list时, 会发生意想不到的情况。

non-threadsafe, nonreentrant code, 

设计同步的数据结构，需要做到2点:
* 消除所有的竞争条件
* 不要引入死锁

最简单的方式是对entire list的所有访问，增删改查，都使用一个独立的mutex保护,然而在访问频繁的情况下，这种方式的效率就比较低了。

一些特殊的处理方式为:
  如果大部分行为是读写存在的数据节点的话，而不是插入删除的话，可以对每个节点建立一个mutex变量,
  lock granularity, 对共享数据加锁的级别, 
  coarse-grain locking, single mutex to control access to all shared data,
  fine-grain locking, a lock on every individually data, 
  to use the most efficient implementation while ensuring the application works correctly,

Locking hierarchy, 加锁的级别，层次,
  deadly embrace, 
  为了避免问题, enforce a fixed locking hierarchy, 

在进程间共享mutex,
  compile time definition, __POSIX_THREAD_PROCESS_SHARED,
  mutex attribute object,
  pthread_mutex_attr_t, 
  in shared memory, or through mmap calls,


一些惯例:
  process-to-process synchronization, semaphores,
  thread-to-thread, semaphores, alternative to process-shared mutexes

### condition variables,
条件变量，对变量的值进行同步,

```shell
pthread_cond_wait()
pthread_cond_timedwait()
pthread_cond_signal()
pthread_cond_broadcast(),
```

### 同时使用 mutex 和condition variable
condition variable如果不使用mutex的话，signaling thread可能在waiting thread开始等待之前就会发送信号signal,


### reader/writer locks
mutex + condition variable, create a third - the reader/writer lock

```C
pthread_rdwr_init_np
pthread_rdwr_rlock_np // obtain read lock
pthread_rdwr-runlock_np
pthread_rdwr_wlock_np // obtain write lock
pthread_rdwr_wunlock_np
```

```C
pthread_rwlock_init

```

给ATM项目加上同步控制, 

### threadpool


