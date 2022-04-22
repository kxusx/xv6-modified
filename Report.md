Implemented Schedulers 
1) Round Robin
2) First Come First Serve
3) Priority Based Scheduling

----------------------------------------------------------------------------------------------------------------------------

Spec 1
    - Added $U/_strace\ in Makefile
    - Added mask in proc.h as a variable for tracing
    - Added sys_trace() in sysproc.c
    - Added user implementation in strace.c
    - Added ``[SYS_trace] sys_trace,`` in syscall.c in (*syscalls[])(void)
        - Also added `syscall_names` and `syscallnum` list.
    - Modified syscall() in syscall.c to print required output

----------------------------------------------------------------------------------------------------------------------------

Spec 2

- Added the below for correct selection of scheduling algorithm
        ifndef $(SCHEDULER)
            SCHEDULER := RR
        endif
        CFLAGS += -D $(SCHEDULER)
----------------------------------------------------------------------------------------------------------------------------

1) Round Robin
- To run it, type ``make qemu`` in your terminal and enjoy the Round Robin

----------------------------------------------------------------------------------------------------------------------------

2) FCFS
- Added `int createTime;` in proc.h for struct proc
- Initialised createTime as ticks in allocproc() in proc.c
- Added the FCFS functionality in scheduler() in proc.c by doing 
    #ifdef FCFS
        code
    #endif
- The code goes through all RUNNABLE processes and selects one with lowest createTime, which is then ran through swtch()
- Since FCFS is nonpremptive, I disabled yield() by 
    #ifndef FCFS
        ...
    #endif
  around the yield() code

----------------------------------------------------------------------------------------------------------------------------

3) PBS
- Added `int priority;` in proc.h for struct proc
- Initialised priority as 60 in allocproc() in proc.c and other variables
    p->state = USED;
    p->createTime = ticks;
    p->rtime = 0;
    p->priority = 60;
    p->NoofRuns = 0;
    p->startTime = 0;
- Added the PBS functionality in scheduler() in proc.c by doing 
    #ifdef PBS
        code
    #endif
- The code 
    - goes through all RUNNABLE processes 
    - and calculates the niceness of code if it has ran 1 already
    - then calculates dynamicProperty as DP = max(0, min(SP − niceness + 5, 100))
    - the proc with is selected based on many tie-breakers
        - highest dynamic priority for execution
        - number of times the process has been scheduled 
        - start-time of the process 
    - after selection of appropriate process, I set the correct values for the proc variables as 
        RUNproc->startTime = ticks;
        RUNproc->NoofRuns = RUNproc->NoofRuns + 1;
        RUNproc->state = RUNNING;
        RUNproc->runTime = 0;
        RUNproc->sleepTime=0;
    - and then the process is ran through swtch()
- Added updateTime() to keep the right track of runtime and sleeptime
- Also added setpriority() similar to strace.
- And implemeted waitx as shown in tutorial. Thankyou:)

----------------------------------------------------------------------------------------------------------------------------

Spec 3

- Added rtime to store total runtime of process
- Also added endtime 
- printed appropriate stuff when SCHEDULER=PBS
    printf("%d %d %s %d %d %d", p->pid, p->priority,state,p->rTime,(p->etime)? p->etime - p->ctime - p->rtime: ticks - p->ctime - p->rtime, ,p->NoofRuns);

----------------------------------------------------------------------------------------------------------------------------

Benchmarks

RR - Average rtime 22,  wtime 117
FCFS - Average rtime 56,  wtime 66
PBS - Average rtime 25,  wtime 109
