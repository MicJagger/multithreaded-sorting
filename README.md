# sorting-algorithms
While this repository focuses on sorting algorithms and their performance, it goes a bit more into detail \
For example, it focuses on multithreading different algorithms to see how well they scale across multiple hardware threads \
This is not a whole software, but just something smaller to demonstrate stuff - the only way to properly use it is to change values and recompile, because this is built using arrays and built-in bools that I would rather keep in the code to make it easier and faster to run and test \
Also, I am currently developing this on Windows, and I have not extensively tested it on Linux-based systems.

## Running the project:
Building is as simple as it can be

1. Go to folder in terminal
2. make
3. Enjoy

The number of threads that is optimal is dependent on both the algorithm and your specific processor. \
If you are unaware of what you have (and are on Windows), just check task manager -> performance -> CPU and put in the number of logical processors your CPU has.
