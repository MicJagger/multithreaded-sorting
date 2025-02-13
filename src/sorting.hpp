#pragma once
#ifndef _SORTING_HPP
#define _SORTING_HPP

#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

/*
template<typename T>
struct func {
	
};
*/

typedef void(functionPtr)(int*, int);

namespace helper {
	//template<typename T>
	void Combine2Arrays(int* array1, int* array2, int size1, int size2) {
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

	// sorting function helpers (all credit given at main functions)

	void heapify(int* array, int size, int index) {
		int largest = index;
		int left = (2 * index) + 1;
		int right = left + 1;
	
		if (left < size && array[left] > array[largest]) {
			largest = left;
		}
		if (right < size && array[right] > array[largest]) {
			largest = right;
		}

		if (largest != index) {
			std::swap(array[index], array[largest]);
			heapify(array, size, largest);
		}
	}

	void merge(int* array, int left, int mid, int right) {
		int subArrayOne = mid - left + 1;
		int subArrayTwo = right - mid;
		
		int* leftArray = new int[subArrayOne];
		int* rightArray = new int[subArrayTwo];

		for (int i = 0; i < subArrayOne; i++) {
			leftArray[i] = array[left + i];
		}
		for (int j = 0; j < subArrayTwo; j++) {
			rightArray[j] = array[mid + 1 + j];
		}
		
		int indexOfSubArrayOne = 0;
		int indexOfSubArrayTwo = 0;
		int indexOfMergedArray = left;
	
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
			if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else {
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}
	
		while (indexOfSubArrayOne < subArrayOne) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
		}
		while (indexOfSubArrayTwo < subArrayTwo) {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
		}

		delete[] leftArray;
		delete[] rightArray;
	}

	void mergeSorter(int* array, int begin, int end) {
		if (begin >= end) {
			return;
		}

		int mid = begin + (end - begin) / 2;

		mergeSorter(array, begin, mid);
		mergeSorter(array, mid + 1, end);

		merge(array, begin, mid, end);
	}

	int partitionArray(int* array, int begin, int end) {
		int pivotPoint = array[begin];
		int count = 0;
	
		for (int i = begin + 1; i <= end; i++) {
			if (array[i] <= pivotPoint) {
				count++;
			}
		}
		
		int pivotIndex = begin + count;
		std::swap(array[pivotIndex], array[begin]);
		
		while (begin < pivotIndex && end > pivotIndex) {
			while (array[begin] <= pivotPoint) {
				begin++;
			}
			while (array[end] > pivotPoint) {
				end--;
			}
			if (begin < pivotIndex && end > pivotIndex) {
				std::swap(array[begin++], array[end--]);
			}
		}
		return pivotIndex;
	}

	void quickSorter(int* array, int begin, int end) {
		if (begin >= end) {
			return;
		}

		int pivotIndex = partitionArray(array, begin, end);
	
		quickSorter(array, begin, pivotIndex - 1);
		quickSorter(array, pivotIndex + 1, end);
	}
}


// 

namespace sort {
	// algorithms

	// std::sort
	//template<typename T>
	void StandardSort(int* array, int size) {
		std::sort(array, array + size);
	}

	//template<typename T>
	void BubbleSort(int* array, int size) {
		bool swapped;
		for (int i = 0; i < size - 1; i++) {
			swapped = false;
			for (int j = 0; j < size - i - 1; j++) {
				if (array[j] > array[j + 1]) {
					std::swap(array[j], array[j + 1]);
					swapped = true;
				}
			}
			if (swapped == false) {
				break;
			}
		}
		// Credit to https://www.geeksforgeeks.org/bubble-sort/
	}

	void HeapSort(int* array, int size) {
		for (int i = (size / 2) - 1; i >= 0; i--) {
			helper::heapify(array, size, i);
		}
		for (int i = size - 1; i >= 0; i--) {
			std::swap(array[0], array[i]);
			helper::heapify(array, i, 0);
		}
		// Credit to https://www.geeksforgeeks.org/heap-sort/
	}

	void MergeSort(int* array, int size) {
		helper::mergeSorter(array, 0, size - 1);
		// Credit to https://www.geeksforgeeks.org/merge-sort/
	}

	void QuickSort(int* array, int size) {
		helper::quickSorter(array, 0, size - 1);
		// Credit to https://www.geeksforgeeks.org/quick-sort/?ref=lbp
	}

	// Multithread a method
	//template<typename T>
	void MultiSort(functionPtr* function, int* array, int size, int threadCount) {
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
				threadsV.push_back(std::thread(helper::Combine2Arrays, array + (2 * i * normal_size), array + ((2 * i + 1) * normal_size), normal_size, normal_size));
			}
			odd = array_count % 2;
			if (odd) { // if odd count of threads
				threadsV.push_back(std::thread(helper::Combine2Arrays, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, normal_size));
				array_count = array_count / 2 + 1;
				if (array_count == 3) {
					one_more_merge = true;
				}
			}
			else { // if even
				threadsV.push_back(std::thread(helper::Combine2Arrays, array + ((2 * (current_threads - 1)) * normal_size), array + ((2 * (current_threads - 1) + 1) * normal_size), normal_size, last));
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
			threadsV.push_back(std::thread(helper::Combine2Arrays, array, array + normal_size, normal_size, last));
			threadsV[0].join();
			threadsV.clear();
		}
	}

	
	// Timed

	//template<typename T>
	double SortTimed(functionPtr* function, int* array, int size) {
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		start = std::chrono::steady_clock::now();
	
		function(array, size);
	
		end = std::chrono::steady_clock::now();
		std::chrono::duration<long long, std::nano> time = end - start;
		return (double)time.count() / (double)1000000;
	}

	//template<typename T>
	double MultiSortTimed(functionPtr* function, int* array, int size, int threadCount) {
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		start = std::chrono::steady_clock::now();
		
		MultiSort(function, array, size, threadCount);

		end = std::chrono::steady_clock::now();
		std::chrono::duration<long long, std::nano> time = end - start;
		return (double)time.count() / (double)1000000;
	}
}

#endif