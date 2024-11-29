# Sorting Algorithms
While this repository focuses on sorting algorithms and their performance, it goes a bit more into detail

For example, it focuses on multithreading different algorithms to see how well they scale across multiple hardware threads

This is definitely a script, not truly a program - the only way to properly use it is to change values and recompile, because this is built using arrays and built-in bools that I would rather keep in the code to make it easier and faster to run and test

Also, I am currently developing this on Windows, and I have not extensively tested it on Linux-based systems.

## Running the project:
Included is a makefile, README (you're reading it), and src folder with source code

1. Go to folder
2. make
3. Enjoy

The number of threads that is optimal is dependent on both the algorithm and your specific processor.

If you are unaware of what you have (and are on Windows), just check task manager -> performance -> CPU and put in the number of Logical Processors your chip has.
