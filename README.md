# Assignment-5

### Usage of the code:

​	`./generate.sh [1 or 2 or 3]` , where :

1 - Default RR scheduler

2 - FCFS scheduler

3 - Priority-based scheduler



### Task 1:

#### Part 1 : Implement waitx syscall :

**Problem statement :** As a part of this task, you're expected to extend the current proc structure and add new fields ctime, etime and rtime for creation time, end-time and total time respectively of a process. When  a new process gets created the kernel code should update the process creation time. The run-time should get updated after every clock tick for the process. To extract this information from the kernel add a new system call which extends wait. The new call will be: **int waitx(int* wtime, int* rtime)**. The two arguments are pointers to integers to which waitx will assign the total number of clock ticks during which process was waiting and total number of clock ticks when the process was running. The return values for waitx should be same as that of wait system-call. Create a test program which utilizes the waitx system call by creating a ‘time’ like command for the same. 
**Note**: This can be used to implement your scheduler functions.



**Solution :** Modifications were made to : 

1. syscall.c ==> sys_waitx line was added. 
2. syscall.h  ===>  define syscall number for waitx.
3. user.h  ===>  waitx function was initialised.
4. defs.h  ===>  added waitx() definition line in //proc.c section.
5. sysproc.c ==> added the syscall for waitx function.
6. usys.S ===>  SYSCALL(waitx) line was added.
7. proc.c ===>  The code for waitx() syscall was added.
8. proc.h ===> The **proc struct ** was extended. 
9. Makefile ==>  added waitx.c to EXTRAS , _waitx to UPROGS .
10. **Created** a new file named **waitx.c** where the waitx function is called and the wait-time and run-time for a process are displayed.



#### Part 2 : Implement getpinfo syscall:

**Problem Statement : ** You'll need to create a new system call for this part:  int getpinfo(struct proc_stat*) . This routine returns some basic information about each process: its process ID, total run time, how many times it has been chosen to run, which queue it is currently on 0, 1, 2, 3 or 4 (check Task 2 part c) and ticks received in each queue. To do this, you will need to create the  proc_stat struct :-
`struct proc_stat {
int pid; // PID of each process
float runtime; // Use suitable unit of time
int num_run; // number of time the process is executed
int current_queue; // current assigned queue
int ticks[5]; // number of ticks each process has received at each of the 5 priority
queue
};`



**Solution :** 

1. **Assumption** : Only the processes that are completed will be stored in the *proc_stat  array.
2. The ongoing processes can be seen by the **ps** syscall.
3. For the **getpinfo** and **ps** syscall:
   1. proc.h  ===>   The struct proc_stat was added.
   2. syscall.h  ===>  syscall number for getpinfo, ps was defined .
   3. syscall.c  ===>  sys_getpinfo, sys_ps lines were added, and their corresponding syscall functions were defined.
   4.  user.h  ===>  getpinfo, ps functions were initialised.
   5. defs.h  ===>  added getpinfo(), ps() definition lines in //proc.c section.
   6. sysproc.c ==> added the syscalls for getpinfo, ps functions.
   7. usys.S ===>  SYSCALL(getpinfo), SYSCALL(ps) lines were added.
   8. proc.c ===>  The codes for getpinfo(), ps() syscalls were added.
   9. Makefile ==>  added getpinfo.c, ps.c to EXTRAS , _getpinfo, _ps to UPROGS .
   10. **Created** a new file named **getpinfo.c** where the getpinfo function is called and the pid(process id) and run-time for a process are displayed.
   11. **Created** a new file names **ps.c**, where the ps function is called and the pid(process id), process-name, process-state, process-priority, process-creation time, process-runtime for a process are displayed.





### Task 2 :  

#### Part 1 : Implement 2 other scheduling policies and incorporate them in Xv6.

**Problem Statement : ** 

The default scheduler of xv6 is a round-robin based scheduler. In this task, you’ll
implement 3 other scheduling policies and incorporate them in Xv6.
(a) **First come - First Served (FCFS):**

Implement a non preemptive  policy that selects the process with the lowest creation
time. The process runs until it no longer needs CPU time.

(b) **Priority Based Scheduler**
A priority-based scheduler selects the process with the highest priority for execution.
In case two or more processes have the same priority, we choose them in a
round-robin fashion. The priority of a process can be in the range [0,100], the smaller
value will represent higher priority. Set the default priority of a process as 60. To
change the default priority add a new system call  set_priority which can change the
priority of a process.
int set_priority(int)
The system-call returns the old-priority value of the process. In case the priority of
the process increases (the value is lower than before), then rescheduling should be
done.



**Solution** : 

1. For both the schedulers, the main problem was to decide which process to pick for execution, so the appropriate process-selection code was written in the **scheduler()** function in proc.c . Apart from that, changes were made according to the scheduling algorithm, in files init.c , trap.c . On process initialisation, the priority was set to default value of 60.
2. For the set priority syscall:
   1. syscall.c ==> sys_chpr line was added. 
   2. syscall.h  ===>  define syscall number for set_priority.
   3. user.h  ===>  chpr function was initialised.
   4. defs.h  ===>  added chpr() definition line in //proc.c section.
   5. sysproc.c ==> added the syscall for chpr function.
   6. usys.S ===>  SYSCALL(chpr) line was added.
   7. proc.c ===>  The code for chpr() syscall was added.
   8. Makefile ==>  added set_priority.c to EXTRAS , _set_priority to UPROGS .
   9. **Created** a new file named **set_priority.c** where the set_priority function is called, with the input as the **id, desired priority value** of the process whose priority is to be changed.







### Additional:

1. A syscall, called **foo** was added, which is a process that does futile computations to use up CPU time. This process can be called as :
   `foo ` or `foo &` or `foo <enter_custom_priority> <enter_number_[1-10]>` 
   The number 1-10 decides number of iterations of the for loop in **foo.c**, thus deciding how slow or fast will the process be (1 means fast, 10 means slow). For this **foo** syscall, only the child process does the computation, and not the parent process.
2. Added a benchmark testing file, **benchmark.c**  that generates CPU and IO bound processes   and records the performance of the scheduling algorithm. The procedure was added as a syscall. Usage of the syscall:
   `benchmark [n]` : where n is the number of processes of each type.