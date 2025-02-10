#pragma once
#ifndef _SORTING_H
#define _SORTING_H

typedef void(functionPtr)(int*, long long);

namespace sort {
	// algorithms
	// std::sort
	void StandardSort(int* array, int size);
	void BubbleSort(int* array, int size);

	// Timed
	double SortTimed(functionPtr* func, int* array, int size);

	// Multi-Threaded

	void Combine2Arrays(int* array1, int* array2, int size1, int size2);
	void ThreadedSort(int* array, int size, int threads, functionPtr* func);
	double ThreadedSortTimed(int* array, int size, int threads, functionPtr* func);

}

#endif