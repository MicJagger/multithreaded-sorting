#include "sorting.h"

// Random Lists

void sort::RandomList(int* array, int size) {
	std::chrono::steady_clock::time_point now;
	now = std::chrono::high_resolution_clock::now();
	long long seed = now.time_since_epoch().count();
	srand(seed % 0x100000000); // only take bottom 32 bits of current "ns" time
	int random;
	for (int i = 0; i < size; i++) {
		random = rand();
		array[i] = random;
	}
}

void sort::RandomList30(int* array, int size) {
	std::chrono::steady_clock::time_point now;
	now = std::chrono::high_resolution_clock::now();
	long long seed = now.time_since_epoch().count();
	srand(seed % 0x100000000);
	int random;
	for (int i = 0; i < size; i++) { // generates upper 15 bits
		random = rand();
		array[i] = random << 15;
	}
	now = std::chrono::high_resolution_clock::now();
	seed = now.time_since_epoch().count();
	srand(seed % 0x100000000);
	for (int i = 0; i < size; i++) { // generates lower 15 bits
		random = rand();
		array[i] += random;
	}
}

void sort::RandomList32(int* array, int size) {
	std::chrono::steady_clock::time_point now;
	now = std::chrono::high_resolution_clock::now();
	long long seed = now.time_since_epoch().count();
	srand(seed % 0x100000000);
	int random;
	for (int i = 0; i < size; i++) { // generates top 15 bits
		random = rand();
		array[i] = random << 17;
	}
	now = std::chrono::high_resolution_clock::now();
	seed = now.time_since_epoch().count();
	srand(seed % 0x100000000);
	for (int i = 0; i < size; i++) { // generates middle 15 bits
		random = rand();
		array[i] += random << 2;
	}
	now = std::chrono::high_resolution_clock::now();
	seed = now.time_since_epoch().count();
	srand(seed % 0x100000000);
	for (int i = 0; i < size; i++) { // generates bottom 2 bits
		random = rand();
		array[i] += random % 4;
	}
}


// Copy Array

void sort::CopyArray(int* array1, int* array2, int size) {
	for (int i = 0; i < size; i++) {
		array2[i] = array1[i];
	}
}


// Test Validity

bool sort::TestValid(int* array, int* correctArray, int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] != correctArray[i]) {
			return false;
		}
	}
	return true;
}


// Setup

double sort::MainSetup(int* unsorted, int* correct, int size) {
	RandomList(unsorted, size);
	CopyArray(unsorted, correct, size);
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::high_resolution_clock::now();

	std::sort(correct, correct + size);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}

void sort::Setup(std::string* name, int* unsorted, int* toSort, int size, int i, int j, bool first, std::vector<std::string>* names) {
	CopyArray(unsorted, toSort, size);
	if (first) {
		if (j == 1) { names->push_back(*name); }
		if (j > 1) { names->push_back(*name + " " + std::to_string(j) + "-Thread"); }
	}
	*name = *name + " " + std::to_string(i);
	if (j > 1) { *name += " " + std::to_string(j) + "-Thread"; }
}


// Algorithms

void sort::StandardSort(int* array, int size) {
	std::sort(array, array + size);
}

void sort::BubbleSort(int* array, int size) {
	bool swapped;
	for (int i = 0; i < size - 1; i++) {
		swapped = false;
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				std::swap(array[j], array[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
	// Credit for this bubble sort goes to GeeksForGeeks @ https://www.geeksforgeeks.org/bubble-sort/
}


// Timed

double sort::SortTimed(int* array, int size, functionPtr* func) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::high_resolution_clock::now();

	func(array, size);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}


// Multi-Threaded w/ Full array

// Combine 2 adjacent sorted arrays into one larger sorted array using O(n) time and space
void sort::Combine2ArrayA(int* array1, int* array2, int size1, int size2) {
	bool array1done = false;
	bool array2done = false;
	int array1index = 0;
	int array2index = 0;
	int left_off;
	int* output_temp = new int[size1 + size2];
	for (int i = 0; i < size1 + size2 - 1; i++) {
		if (array1[array1index] <= array2[array2index]) { // if array1 is <= array2, select that value
			output_temp[i] = array1[array1index];
			array1index++;
			if (array1index == size1) { // if array1 is done, break out and finish array2
				array1done = true;
				left_off = i + 1;
				break;
			}
		}
		else { // array1 > array2
			output_temp[i] = array2[array2index];
			array2index++;
			if (array2index == size2) { // if array2 is done, break out and finish array1
				array2done = true;
				left_off = i + 1;
				break;
			}
		}
	}
	if (array1done) { // finish array2
		for (int i = left_off; i < size1 + size2; i++) {
			output_temp[i] = array2[array2index];
			array2index++;
		}
	}
	else { // finish array1
		for (int i = left_off; i < size1 + size2; i++) {
			output_temp[i] = array1[array1index];
			array1index++;
		}
	}
	int output_index = 0;
	for (int i = 0; i < size1; i++) { // fill array1 with first half of sorted
		array1[i] = output_temp[output_index];
		output_index++;
	}
	for (int i = 0; i < size2; i++) { // fill array2 with second half of sorted
		array2[i] = output_temp[output_index];
		output_index++;
	}
	delete[] output_temp;
}

// Combining Arrays uses O(n) time and space, sorting dependent on thread count and function
void sort::ThreadedSortA(int* array, int size, int threads, functionPtr* func) {
	// Split up work
	std::vector<std::thread> threadsV;
	int max_threads = threads;
	int normal_size = size / max_threads;
	for (int i = 0; i < (max_threads - 1); i++) { // create worker threads of all equal sizes except the last one of possible variable size
		threadsV.push_back(std::thread(func, array + (i * normal_size), size / max_threads));
	}
	threadsV.push_back(std::thread(func, array + ((max_threads - 1) * normal_size), normal_size + (size % max_threads))); // create last worker thread of size + remainder
	for (int i = 0; i < max_threads; i++) {
		threadsV[i].join();
	}
	threadsV.clear();

	// Combine Arrays
	normal_size = size / threads;
	int remainder = size % threads;
	int last = normal_size + remainder;
	int array_count = threads;
	int current_threads = threads / 2;
	bool odd = array_count % 2;
	bool one_more_merge = false;
	while (current_threads) {
		for (int i = 0; i < (current_threads - 1); i++) { // combine pairs of sorted arrays
			threadsV.push_back(std::thread(Combine2ArrayA, array + (2 * i * normal_size), array + ((2 * i + 1) * normal_size), normal_size, normal_size));
		}
		odd = array_count % 2;
		if (odd) { // if odd count of threads
			threadsV.push_back(std::thread(Combine2ArrayA, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, normal_size));
			array_count = array_count / 2 + 1;
			if (array_count == 3) {
				one_more_merge = true;
			}
		}
		else { // if even
			threadsV.push_back(std::thread(Combine2ArrayA, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, last));
			array_count /= 2;
			last += normal_size;
		}
		normal_size *= 2; // double size of standard (non-last) array
		for (int i = 0; i < current_threads; i++) {
			threadsV[i].join();
		}
		if (odd && current_threads % 2) { // i cant really explain why but i know this needs to happen
			current_threads = current_threads / 2 + 1;
		}
		else {
			current_threads /= 2;
		}
		threadsV.clear();
	}
	if (one_more_merge && 0) {
		threadsV.push_back(std::thread(Combine2ArrayA, array, array + normal_size, normal_size, last));
		threadsV[0].join();
		threadsV.clear();
	}
}

double sort::ThreadedSortATimed(int* array, int size, int threads, functionPtr* func) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::high_resolution_clock::now();
	
	ThreadedSortA(array, size, threads, func);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}


// Multi-Threaded w/ Queue

void sort::Combine2ArrayQ(int* array1, int* array2, int size1, int size2) {

}

void sort::ThreadedSortQ(int* array, int size, int threads, functionPtr* func) {
	
}

double sort::ThreadedSortQTimed(int* array, int size, int threads, functionPtr* func) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::high_resolution_clock::now();
	
	ThreadedSortQ(array, size, threads, func);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}