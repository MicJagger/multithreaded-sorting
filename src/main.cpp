#include "sorting.h"

namespace cfg {
    // size of the array
    const int size = 1000 * 1000;
    // number of test runs
    const int tests = 8;
    // number of threads to run
    const int threads = 32;

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
}

int main() {

    /*
    
    std::string name;
	double time;
	std::vector<std::string> names;
	std::vector<double> durations;
	std::vector<double> baseDurations;

	int threadruns = 0; // find how many times the j loop runs the first time
	bool first = true;
	for (int i = 0; i < val::tests; i++) {
		baseDurations.push_back(MJsort::MainSetup(val::unsorted, val::correct, val::size)); // make new list and std::sort, save times

		for (int j = 1; j <= val::maxThreads; j *= 2) {
			// Algorithms

			// Standard Sort
			if (runs::standard) {
				name = "Standard Sort";
				MJsort::Setup(&name, val::unsorted, val::toSort, val::size, i, j, first, &names);
				
				if (j == 1) { time = MJsort::SortTimed(val::toSort, val::size, &MJsort::StandardSort); }
				else { time = MJsort::ThreadedSortATimed(val::toSort, val::size, j, &MJsort::StandardSort); }
				
				std::cout << name << " took " << time << " milliseconds" << '\n';
				if (MJsort::TestValid(val::toSort, val::correct, val::size)) { durations.push_back(time); }
				else { durations.push_back(-1); }
			}
			
			// Bubble Sort
			if (runs::bubble) {
				name = "Bubble Sort";
				MJsort::Setup(&name, val::unsorted, val::toSort, val::size, i, j, first, &names);
				if (j == 1) { time = MJsort::SortTimed(val::toSort, val::size, &MJsort::BubbleSort); }
				else { time = MJsort::ThreadedSortATimed(val::toSort, val::size, j, &MJsort::BubbleSort); }
				std::cout << name << " took " << time << " milliseconds" << '\n';
				if (MJsort::TestValid(val::toSort, val::correct, val::size)) { durations.push_back(time); }
				else { durations.push_back(-1); }
			}

			// Heap Sort
			if (runs::heap) {

			}

			// Merge Sort
			if (runs::merge) {

			}

			// Quick Sort
			if (runs::quick) {

			}

			// Extra needed stuff
			if (first) { // see how many times j runs the first time
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

	return 0;

    */

    return 0;
}

