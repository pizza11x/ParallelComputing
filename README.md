# Parallel computing exercises
This repository includes exercises for practicing parallel computing.

The difficulty of the exercises is increasing: starting from the classic HelloWorld, up to the sorting algorithm (OddEvenSort).

# Compile and Run the exercises:
To compile: gcc -fopenmp -o name-executable name-code.c

To run: ./name-executable

if you want, you can change the environment variables: export OMP_NUM_THREAD = 2 (this command must be entered before running the executable)

# Execution time:
At launch, use the "time" command: time ./name-executable

At the output you can see:
-real: wall-clock time or elapsed-time. Is the time actually elapsed from the start to the end of the launch.
-user: is the time spend in user mode.
-sys: is the time spend in services of system.
