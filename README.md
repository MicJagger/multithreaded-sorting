# Sorting Algorithms
While this repository focuses on sorting algorithms and their performance, it goes a bit more into detail

For example, it focuses on multithreading different algorithms to see how well they scale across multiple hardware threads

This is definitely a script, not truly a program - the only way to properly use it is to change values and recompile, because this is built using arrays and built-in bools that I would rather keep in the code to make it easier and faster to run and test

Also, this is currently windows-only. I intend on updating this to have Unix-support in the future, but the timing is based on std::chrono::high_resolution_clock::time_point, and since Windows measures in 100 nanosecond intervals, it was easy to apply what I have already done to this. I am spending more time in linux though, and figuring out how to make things cross-compatible, however my first goal is to get this to work as a proof-of-concept.

## Running the project:
Included is a makefile, README (you're reading it), and src folder with source code

1. Ensure you have MinGW32 / G++ installed
2. Navigate to the folder in your terminal of choice
3. Run MinGW32-make if on Windows (I will update this as I test Unix-based, I have had inconsistencies)
4. Enjoy

The number of threads that is optimal is dependent on both the algorithm and your specific processor.

If you are unaware of what you have (and are on Windows), just check task manager -> performance -> CPU and put in the number of Logical Processors your chip has.
