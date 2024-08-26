### Philosophers

Multithreading project for solving the introductory Philosophers problem with left and right forks

Mandatory Part is built using a threaded program while the Bonus part uses forked processes to argue as Philosophers, managing communication only through Semaphores.

![DALL·E-2024-08-26-12 02](https://github.com/user-attachments/assets/d9ba0854-3b74-4d3e-9259-a881cc3fe14b)"

### Implementation Details

1. **Philosopher Structure**: Each philosopher is represented by a struct containing their ID, eating status, time of last meal, and number of times eaten.

2. **Fork Management**: Forks are represented by mutex locks. Each philosopher needs to acquire both their left and right forks to eat.

3. **Deadlock Prevention**: To prevent deadlocks, philosophers are instructed to pick up the lower-numbered fork first, then the higher-numbered fork. This breaks the circular wait condition.

4. **Starvation Prevention**: A waiter (or guard) thread is implemented to check if any philosopher hasn't eaten for too long and to ensure fair resource distribution.

5. **Termination Conditions**: The simulation ends when either a philosopher dies of starvation or all philosophers have eaten a specified number of times.

---


### Multithreading

This project introduced the concept of multhithreaded programming, therefore running multiple calculations at the same time, 
taking advantage of multiple Cores of our CPUS for the first time in the curriculum.

It also introduced issues like deadlocks, race conditions, concurrency issues, logic jumps, invalid reads etc..
Serving as a good lesson in proper code structure and planning out a project before jumping straight into the code base.

---

### Deadlocks, Race Conditions and other interesting problems

Below I provide a short explanation of each of the issues that multithreaded programs can cause, 
this does not include problems more commonly seen when using asynchronous threading such as callback issues, state management, context switching or synchronization difficulties.
While these can occur in limited context in this project as well, they are not prevalent in this simple multithreaded program.

Deadlocks 🔒 :

A Deadlock occurs when two threads try to access resources held by another thread and cannot resolve the issue, becoming stuck.
This commonly occurs when the threads are mismanaged and not properly timed or have wrong access orders to resources.

An example encountered in this project:
Imagine you have to philosophers needing two forks to eat their meal, now each philosopher can only take their left and right fork.
What now happens when the first philosopher takes the left fork while the second philosopher takes the right fork?
Each of these philosophers now holds a fork and since they can't put down their fork, both philosophers become stuck and starve.

Race Conditions 🏎️ :

A race condition is a very common occurence when access to resources is not properly managed and locked.
This happens when two threads try to access the same resource and change the value, in these cases the values do not get added properly but become overwritten by the last thread having access to the resource.

Which is why it is so important to properly lock the action of changing values behind mutexes.

Resource Starvation 💀 :

Resource starvation occurs if the threads do not properly assign enough processing power to different threads, leading to incorrect calculations, timeouts and other various issues.
This was the biggest part of the project since we needed to provide each thread with enough power to cycle through their actions correctly and not have any threads die due to starvation.

---

### Process

The interesting part of this project was in how each thread managed their memory and updated their values correctly.

Since we were only allowed to use usleep in this project, I needed to improve the timer functions.

After setting up a custom timer that was more accurate than the normal usleep I started on the general structure of the program, splitting up memory necessary to be accessed by all threads to memory which each thread should hold on it's own.
For example:
Each thread had to hold it's own timer of when it had last eaten, as well as the amount of times it had eaten.
This was necessary to compare each threads values to the time it was allowed to sleep between eat cycles

### Bonus Part: Using Processes and Semaphores
In the bonus part, instead of threads, I used separate processes for each philosopher. 
Communication between processes was managed using semaphores instead of mutexes.

1. **Process Creation**: Use `fork()` to create a new process for each philosopher.
2. **Semaphores**: Replace mutexes with semaphores for fork management.

Issues:
Since forked processes receive a copy of the main processes allocated memory, each process has their own data blocks that cannot be accessed by the other child processes.
This led to the issue that I could not check and communicate to each child process when to stop eating or when to exit the loop due to the death of another process. 
The only way around this issue was creating a complicated semaphore structure inside of the main process, incrementing a loop value for each sated philosopher.
On reaching the number of philosophers necessary the loop would break and the kill command inside of the main loop would clean up all the children.

