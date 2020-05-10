# squaresolver
 
Simple example of classic Conusmer-Producer problem.

The task is following:

* Producer gets parameters of quadratic equasions from command line arguments
and schedules tasks to the task queue
* Consumer gets tasks from task queue, if it is not empty, and solves 
the quadratic equation
* Program should work correctl and fast, without wasting resources

Solution contains several classic patterns:

* Monitors as synchronization primitives for multithreading execution
* Blocking queue based on Monitrors for managing correct and safe access to its data
* Poison Pill for termination working threads

Solution is crossplatform and tested on the following platforms:
* Windows 10, MSVC 19.25 (VS2019 16.5.4) x64
* Windows 10, MSYS2, MinGW x64, GCC 8.2.1
* ArchLinux x64, GCC 9.x

Solution requires only one framework - testing framework Catch2.
This framwework could be installed like that:
* For MSVC on Windows vcpkg could be used
* For MSYS2 and ArchLinux, catch2 could be installed from packman
* On Linux different package managers could have this package in theirs repos, or you could use vcpkg also.
