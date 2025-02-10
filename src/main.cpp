#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

#include "sorting.hpp"

namespace cfg {
    // size of the array
    const int size = 100 * 1000;
    // number of test "suites" to run
    const int tests = 4;
    // number of threads to run (up to)
    const int threads = 16;

    // unsorted list to clone
    int* unsorted = new int[size];
    // list to sort inside algorithm
    int* toSort = new int[size];
    // control group to test validity against
    int* correct = new int[size];

    bool testValid = true;
    bool writeCSV = true;

    bool standard = true;
    bool bubble = true;
    bool heap = true;
    bool merge = true;
    bool quick = true;
};

// Returns 15-bit random list
void RandomList(int* array, int size);

// copy array 1->2
//template<typename T>
void CopyArray(int* array1, int* array2, int length);

// test validity
//template<typename T>
int TestValid(int* array, int* correctArray, int size);

// setup
//template<typename T>
double Setup(int* unsorted, int* correct, int size);

void RunSortTimed(std::string name, functionPtr* function, int j, std::vector<std::string> &names, std::vector<double> &durations);


// 

int main() {
	std::vector<std::string> names;
	std::vector<double> durations;
	std::vector<double> baseDurations;

	int threadruns = 0; // find how many times the j loop runs the first time
	bool first = true;
	for (int i = 0; i < cfg::tests; i++) {
		baseDurations.push_back(Setup(cfg::unsorted, cfg::correct, cfg::size)); // make new list and std::sort, save times
		std::cout << "Begin Test Suite Number " << i << "\n\n";

		for (int j = 1; j <= cfg::threads; j++) {
			// Standard Sort
			if (cfg::standard) {
				RunSortTimed(std::string("Standard Sort"), &sort::StandardSort, j, names, durations);
			}
			
			// Bubble Sort
			if (cfg::bubble) {
				RunSortTimed(std::string("Bubble Sort"), &sort::StandardSort, j, names, durations);
			}

			// Heap Sort
			if (cfg::heap) {

			}

			// Merge Sort
			if (cfg::merge) {

			}

			// Quick Sort
			if (cfg::quick) {

			}

			// see how many times j runs the first time
			if (first) {
				threadruns++;
			}
			std::cout << '\n';
		}
		first = false;
		std::cout << '\n';
	}

	// durations.size() = tests * threadsLoop
	// baseDurations.size() = tests
	// names.size() = threadsLoop * numAlgs

	/*
	
	std::ofstream Out;
	if (runs::writeCSV) {
		Out.open("out.csv");
		if (!Out.is_open()) { std::cout << "FAIL TO OPEN" << '\n'; }
		Out << "Array Size:,," << val::size << '\n' << '\n';
		Out << "Name,,Average Time,,Speedup" << '\n';
	}

	std::cout << "Array Size: " << val::size << '\n' << '\n';

	std::cout << std::setw(24) << std::left << "Names";
	std::cout << std::setw(20) << std::right << "Averages";
	std::cout << std::setw(20) << std::right << "Speedup" << '\n';

	double baseAverage = 0;
	for (int i = 0; i < val::tests; i++) {
		baseAverage += baseDurations[i];
	}
	baseAverage /= val::tests;

	double average;
	int uniqueAlgorithms = names.size() / threadruns;
	for (int i = 0; i < uniqueAlgorithms; i++) { // for each unique algorithm
		if (runs::writeCSV) { Out << '\n'; }
		std::cout << '\n';

		for (int j = 0; j < threadruns; j++) { // for each threaded run of each algorithm
			average = 0;
			for (int k = 0; k < val::tests; k++) {
				average += durations[names.size() * k + uniqueAlgorithms * j + i];
			}
			average /= (double)val::tests;
			
			if (runs::writeCSV) {
				Out << names[uniqueAlgorithms * j + i] << ",," << average << ",," << baseAverage / average << '\n';
			}
			std::cout << std::setw(24) << std::left << names[uniqueAlgorithms * j + i];
			std::cout << std::setw(20) << std::right << std::fixed << std::setprecision(6) << average;
			std::cout << std::setw(20) << std::right << std::fixed << std::setprecision(6) << baseAverage / average << '\n';
		}
	}
	
	*/

    return 0;
}


//

void RunSortTimed(std::string name, functionPtr* function, int threadCount, std::vector<std::string> &names, std::vector<double> &durations) {
	double time;
	CopyArray(cfg::unsorted, cfg::toSort, cfg::size);
	
	if (threadCount == 1) {
		time = sort::SortTimed(function, cfg::toSort, cfg::size); 
	}
	else {
		time = sort::MultiSortTimed(function, cfg::toSort, cfg::size, threadCount); 
	}

	name.append(" w/ " + std::to_string(threadCount) + "t");
	names.push_back(name);
	int index;
	if ((index = TestValid(cfg::toSort, cfg::correct, cfg::size)) == 0) { 
		std::cout << name << " took " << time << " milliseconds" << '\n';
		durations.push_back(time); 
	}
	else {
		std::cout << "FAILED " << name << " @ " << index << '\n';
		durations.push_back(index);
	}
}

void RandomList(int* array, int size) {
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	for (int i = 0; i < size; i++) {
		array[i] = rand();
	}
}

//template<typename T>
void CopyArray(int* array1, int* array2, int size) {
	for (int i = 0; i < size; i++) {
		array2[i] = array1[i];
	}
}

//template<typename T>
int TestValid(int* array, int* correctArray, int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] != correctArray[i]) {
			return i;
		}
	}
	return 0;
}

//template<typename T>
double Setup(int* unsorted, int* correct, int size) {
	RandomList(unsorted, size);
	CopyArray(unsorted, correct, size);
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::steady_clock::now();

	std::sort(correct, correct + size);

	end = std::chrono::steady_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}
