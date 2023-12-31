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
thread pool basic 特性
- number of worker threads,
- request queue size,
- behavior when all workers are occupied and request queue is full,

## chap 4 Managing pthreads, 管理线程
### 线程属性
In the detached state, 配置线程的stack, scheduling 行为，

```shell
pthread_attr_t
pthread_create()
```

stack size,
    线程使用它自己的私有栈来存储本地变量，对于调用的每一个routine, 

detached state, 

设置属性的多个参数, 



### pthread_once,mechanism
只会运行一次, 只有一次, chorese, 日常工作，乏味的工作,如何避免多个线程在初始化时，只做一次初始化工作，比如打开某个第三方的库。


Keys,
    保存一个private copies of shared data item, 
    a kind of pointer, 
    共性, libraries with internal state, 
    非线程环境，key referenced data be as static data,

```C
static pthread_key_t conn_key;
pthread_key_create(key, destructor routine);
pthread_setspecific()
pthread_getspecific()
```

Cancellation,
    取消线程、终止线程的运行，one thread cancel another thread,
  
Scheduling,
    任务调度, real-time applications, 
    设置2个thread-specific attributes属性,
    scheduling priorityA thread's scheduling priority,
    哪一个线程可以在任意时间获得cpu资源
    同样级别的线程如果分享cpu资源
    scheduling priority, policy thread attributes,

Mutex scheduling attributes,
    避免priority inversion, 

**scheduling scope**
线程参加的调度活动、调度过程的范围。多少线程、线程的数量，调度器需要选择的彼此竞争的线程的数量。

实现时，线程的调度要么在进程范围，要么在系统范围。
许多操作系统允许将cpu作为单独的调度对象，这些分组grouping,称为"processor set"处理器组, 由系统调用生成，或者管理员的命令生成。Pthreads标准承认这些处理器组的存在，将之作为调度的分配域，allocation domains. 

```c
PTHREAD_SCOPE_SYSTEM
PTHERAD_SCOPE_PROCESS
pthread_getscope()
pthread_setscope()
```
将管理的进程、线程抽象化，将调度的cpu资源抽象化。

- 当我们说到pool of threads,线程池时
  - 在进程域，所有的线程都在同一个进程里
  - 在系统域，所有进程的所有线程都在同一个分配域中,allocation domain
- 当我们说调度器scheduler时,
  - 在进程域，我们指的是pthread library,或操作系统内核的调度程序
  - 在系统域，我们指的是操作系统的调度程序
- 当我们说到processing slot, 处理slot,
  - 在进程域，分配给进程的cpu时间，
  - 在系统域，分配给某个线程的cpu时间

可运行和被阻塞的线程

**priority ceiling**
优先级取顶协议，将调度优先级设置一个mutex, mutex可以给它的持有人一个有效的相同的运行优先级，如果mutex的持有人开始时的优先级较低的话。
```c
_POSIX_THREAD_PRIO_PROTECT,
_POSIX_THREAD_PRIO_INHERIT,
```

**priority inheritance**
优先级继承协议，使mutex可以提高拥有者的优先级，和正在等待的线程中的最高优先级相同。

## chap 5 Pthreads and UNIX
os操作process进程，而不是线程 

- signals, pthreads标准提供了一种线程的方法，参与signal handling,
- threadsafe libraries, 避免不同线程之间的竞争
- Cancellation-safe library, 
- Blocking functions, 
- Process management, 
- Multiprocessor memory synchronization, 保证threads' views of shared data,包含mutexes, condition variable的状态是一致的。在单处理器、多处理器都要正常工作

发送信号和等待信号

&nbsp;&nbsp;&nbsp;&nbsp;kill系统调用, 进程亦可以发送信号signal给自己，使用kill或raise系统调用
信号的到来会打断进程的执行。一些信号会回复进程的执行，当该进程因为调用系统调用wait, sigsuspend, sleep,pause而被操作系统挂起时。
&nbsp;&nbsp;&nbsp;&nbsp;使用signal mask来阻塞信号的接收,进程可以使用sigaction, sigsuspend调用来设置、重置信号的阻塞状态。


**多线程的信号处理,**
当进程收到信号时，系统要决定由哪一个线程来处理信号。选择方式有

同步产生的信号，系统产生，因为发生了exception异常
    接收者是某个线程，
    产生异常的线程


同步产生，内部的线程使用了pthread_kill系统调用，
    接收者是某个线程，不能发给其它进程的线程,
    targeted线程，


异步产生，外部进程使用了kill系统调用
    接收者是整个的进程，
    进程中的所有线程接收，根据每个线程的signal masks,
    pthread_sigmask, to block, unblock signals
    系统会选择一个thread来处理信号,
    所有的线程共享进程的own signal action, sigaction structure,
    一个线程sigaction了调用，其它的线程的触发也能够使用

SIGFPE, divide by Zero
SIGSEGV, 访问了错误的内存地址
SIGPIPE, broken pipe,管道不存在

job control signals,
- SIGALRM
- SIGHUP
- SIGINT
- SIGKILL
- SIGUSR1, SIGUSR2,

asynchronous signal-safe functions, 可以安全地从signal handler被调用的函数。这些函数有一个特别的属性，reentrancy,允许重入。

POSIX calls可以从信号处理函数调用的有:
```shell
access,  alarm, cfgetispeed, cfsetispeed, cfsetospeed
chdir, chmod, chown, close, creat, dup,
dup2, execle, execve, _exit, fcntl, fork,
fstat, getgroups, getpgrp, getpid, getppid, getuid,
kill, link, lseek, mkdir, mkfifo, open,
pathconf, puase, pipe, read, rename, rmdir,
setgid, setpgid, setsid, setuid, sigaction, sigaddset,
sigdelset, sigemptyset, sigismember, sigpending, sigprocmask,
sigusspend,sleep, stat, sysconf, tcdrain, tcflow,
tcflush, tcgetattr, tcgetpgrp, tcsendbreak, tcsetattr,
tcsetup, time, times, umask, uname,
unlink, utime, wait, waitpid, write,
```
如果系统支持POSIX实时扩展，还可以调用
```powershell
aio_error, aio_return,aio_suspend,
clock_gettime, fdatasync, fsync,
getegid, geteuid, sem_post,
sigqueue, timer_getoverrun, timer_gettime,
timer_settime,
```
当需要pthread接收并处理signal时，可以使用sigwait系统调用
- Mask the signal 在所有的线程里面, sigwait会检测到这些信号, signal
- 用一个专门的thread来等待信号的到来
- 在一个专门的thread里循环调用sigwait,

ATM的例子里, 增加接收命令，关闭的功能。
当服务器接收到关闭请求时，必须
- 让工作线程完成当前的工作
- boss线程不会再生成新的工作线程

我们会生成一个新的线程->shutdown thread, 
- 这个线程会设置一个全局变量，表明shutdown开始了
- 其它的线程都block对SIGUSR1信号的处理, 
- 当收到信号后，检查当前的worker thread的数量，等待减为零
- exit，退出程序

**线程安全，线程不安全**
线程调用第三方库的时候要注意，这个库可能被不同的进程调用, 如果使用了公共的buffer,运行时就会出问题。将buffer放在线程的stack之上，即可。

**使用errno得库**
使用errno的系统调用会对多线程程序产生问题。对于一个process,只有一个公共的errno公共变量。
Pthread标准将errno,实现为一个宏。展开时，会返回一个线程相关的错误值。
Pthread的解决办法是生成一些新的线程安全的调用接口
```c
asctime_r, ctime_r, getgrgid_r, getgrnam_r,
getlogin_r, getpwnam_r, getpwuid_r, gmtime_r,
localtime_r, rand_r, readdir_r, strok_r
ttyname_r,
```

**file-locking functions for threads**
flock是用于进程间共享的，
用于线程共享的是
```c
flockfile, // locks a file on a per-thread basis
ftrylockfile,
funlockfile,
```
一般需要查找操作系统文档, 线程安全的函数库为libxxx_r.a, 原始的函数库为libxxx.a

调用时，使用mutex或者condition来使只有一个线程访问那些线程调用不安全的接口。

**线程取消，cancellation**
多线程环境里的线程取消。
- 在线程执行某些系统调用的时候，我们能够取消线程吗？
- 对一个延迟的取消，这些调用可以作为取消的时间点吗?

**asynchronous cancellation-safe**
异步的取消安全的函数, 
在系统调用编写的时候，是不考虑线程的存在的。定义一个随机取消安全的wrapper,
```c
#define async_cancel_safe_read(fd,buf,amt) \{
int oldtype; \
pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,&oldtype);
if(read(fd,buf,amt) <0)
    perror("read")
    exit(-1)
pthread_setcanceltype(oldtype, NULL)
pthread_testcancel();
}
```
作为cancellation points的pthread调用
```c
pthread_testcancel,
pthread_cond_wait,
pthread_cond_timedwait,
pthread_join
```
POSIX.1和ANSI C routines可以作为cancellation points的
```shell  
closedir, ctermid, fclose, fcntl, fflush,
fgetc, fgets, fopen, fprintf, fputc,
fputs,fread, freopen, fscanf, fseek,
ftell, fwrite, getc, getchar, getchar_unlocked,
getc_unlocked, getcwd, getgrgid, getgrgid_r, getgrnam,
getgrnam_r, getlogin, getlogin_r, getpwnam, getpwnam_r,
getpwuid, getpwuid_r, gets, lseek, opendir,
perror, printf, putc, putchar, putchar_unlocked,
putc_unlocked, puts, readdir,remove, rename,
rewind, rewinddir, scanf, tmpfile, tmpname,
ttyname, ttyname_r, ungetc, unlink
```
下面这些调用必须定义为cancelation points,
```shell  
aio_suspend, close, creat, fcntl, fsync, mg_receive,
mg_send, msync, nanosleep, open, pause, read,
sem_wait, sigsuspend, sigtimedwait, sigwait, sigwaitinfo, sleep,
system,tcdrain, wait, waitpid,write,
```
 
**线程阻塞的库函数和系统调用**
suspend current thread not the whole process 调用包括
```shell  
fcntl, open, pause , read,
sigsuspend, sleep, wait, waitpid
write
```
如果不满足的话，可以
- fork another process to do the call, 
- 使用nonblocking alternatives, 

**线程和进程管理**
从线程中调用fork, exec会发生什么呢?
生成一个子进程只有一个线程的复制，也就是调用进程。会继承parent的held locks, confusion and deadlock. 子进程继承了heap areas, memory leaks, data loss, bug reports.

pthread_atfork调用来处理这些问题。
- routines placed on the prepare stack are run in the parent before the fork
- routines placed on the parent stack, are run in the parent after the fork
- routines placed on the child stack are run in the child after the fork

**multiprocessor Memory Synchronization**
Pthread标准需要库实现内存写的同步。for a subset of Pthreads and POSIX.1 functions. 
必须同步memory操作的函数包括
```powershell
pthread_cond_broadcast, pthread_mutex_unlock,
pthread_cond_signal, sem_post,
pthread_cond_timedwait, sem_trywait,
pthread_cond_wait, sem_wait,
pthread_create, fork,
pthread_join, wait,
pthread_mutex_trylock, waitpid,
pthread_mutex_lock,
```
线程不安全的库还是会存在，因为性能原因，或者数量原因，占大多数。

## chap 6 Practical Considerations
### 理解Pthreads的实现
实现方式，based in user space or kernel space, 或者是中间方案: two-level schedulers, lightweight processes(LWP), or activations,

纯用户线程的实现, 不提供全局scheduling scope, 实际上不允许同一个进程的线程运行在不同的CPU上,
all-to-one mapping, 一个process的所有pthreads运行, scheduler选择一个线程进行运行, library scheduler, 使用了Unix Programmer传统上管理一个进程里的多个上下文的方式进行编程，比如
- setjmp,
- longjmp
- signals,

Pthread library 可以定义一个user thread as a data structures,存储了execution point in the form of jmp_buf数据结构，被setjmp存储。当线程被选中时，longjmp 到新线程的执行点，根据存储的jmp_buf 数据

纯用户空间实现的优点,
- 不用修改kernel threads,
- 不使用昂贵的系统调用来生成线程，不需要内核来切换上下文，执行会快一些
- 内核是不知道用户线程的存在的，因此对内核没有影响, 
纯用户空间实现的缺点
- 线程优先级无法被kernel调用切换，抢占必须由用户来实现
- 无法利用多核处理器，

纯kernel-thread实现，无法扩展当一个进程拥有了几十、上百个线程的需求时,
为每个线程生成一个kernel hread,
one-to-one mapping, 
当cpu空闲的话，kernel会将线程分配给cpu，不管线程属于哪一个进程
每个线程有自己的优先级，调度器优先级，存储的寄存器值，

纯内核空间实现的优点
- 优先级调度
- 利用多cpu，
缺点:
- 开销更大一些
- 使用巨量线程的话会给cpu带来负担，下降整个的性能，影响所有的应用程序

Two-level调度器的实现,
将用户线程映射到一个kernel thread pool,内核线程池, some-to-one mapping。库和kernel都存储了关于线程的数据结构，
high I/O activity and high intense CPU use over time, 

2种线程
满足portable Pthread interface, 可移植性Pthread接口,

### 调试Debugging,
race conditions, deadlocks, 
Event ordering, 
通常是因为多个线程访问共享数据造成的。
```c
ladebug
```


### 性能Performance,
获得比单线程更好的性能，如何测量，如何调试性能呢?

Profiling a thread,
```c
prof
pixie,
```

## Appendix A,
复杂和异步事件,门事件。已经解决了字体问题。

DCE (Distributed Computing Environment), 由OSF(Open Software Foundation)组织开发。
DCE包含了很多编程工具和服务器程序, 使用了远程过程调用(RPC),彼此之间通讯。DCE应用天生就适合使用Pthread,线程。Pthread role in DCE-based application 应用。

DCE使用Draft 4 Pthread interface. 

**DCE server**
等待client requests on communication channel, 到达后处理请求。DCE server的engine使用了Posix threads来处理多个请求，并行。

```c
rpc_server_listen()
```
distributed application based on a client/server model. 生成一个IDL(Interface Definition Language)文件定义所有可能得client calls.

## Appendix C Pthreads Quick Reference





