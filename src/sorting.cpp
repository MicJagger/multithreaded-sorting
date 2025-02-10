#include "sorting.hpp"

#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

// Algorithms

template<typename T>
void sort::StandardSort(T* array, int size) {
	std::sort(array, array + size);
}

template<typename T>
void sort::BubbleSort(T* array, int size) {
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


// Multi-Threaded

// Combine 2 adjacent sorted arrays into one larger sorted array using O(n) time and space
template<typename T>
void Combine2Arrays(T* array1, T* array2, int size1, int size2) {
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

template<typename T>
void sort::MultiSort(func<void>::functionPtr* function, T* array, int size, int threadCount) {
	// Split up work
	std::vector<std::thread> threadsV;
	int max_threads = threadCount;
	int normal_size = size / max_threads;
	for (int i = 0; i < (max_threads - 1); i++) { // create worker threads of all equal sizes except the last one of possible variable size
		threadsV.push_back(std::thread(function, array + (i * normal_size), size / max_threads));
	}
	threadsV.push_back(std::thread(function, array + ((max_threads - 1) * normal_size), normal_size + (size % max_threads))); // create last worker thread of size + remainder
	for (int i = 0; i < max_threads; i++) {
		threadsV[i].join();
	}
	threadsV.clear();

	// Combine Arrays
	normal_size = size / threadCount;
	int remainder = size % threadCount;
	int last = normal_size + remainder;
	int array_count = threadCount;
	int current_threads = threadCount / 2;
	bool odd = array_count % 2;
	bool one_more_merge = false;
	while (current_threads) {
		for (int i = 0; i < (current_threads - 1); i++) { // combine pairs of sorted arrays
			threadsV.push_back(std::thread(Combine2Arrays, array + (2 * i * normal_size), array + ((2 * i + 1) * normal_size), normal_size, normal_size));
		}
		odd = array_count % 2;
		if (odd) { // if odd count of threads
			threadsV.push_back(std::thread(Combine2Arrays, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, normal_size));
			array_count = array_count / 2 + 1;
			if (array_count == 3) {
				one_more_merge = true;
			}
		}
		else { // if even
			threadsV.push_back(std::thread(Combine2Arrays, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, last));
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
		threadsV.push_back(std::thread(Combine2Arrays, array, array + normal_size, normal_size, last));
		threadsV[0].join();
		threadsV.clear();
	}
}


// Timed

template<typename T>
double sort::SortTimed(func<void>::functionPtr* function, T* array, int size) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::steady_clock::now();

	function(array, size);

	end = std::chrono::steady_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}

template<typename T>
double sort::MultiSortTimed(func<void>::functionPtr* function, T* array, int size, int threadCount) {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	start = std::chrono::steady_clock::now();
	
	MultiSort(function, array, size, threadCount);

	end = std::chrono::steady_clock::now();
	std::chrono::duration<long long, std::nano> time = end - start;
	return (double)time.count() / (double)1000000;
}
