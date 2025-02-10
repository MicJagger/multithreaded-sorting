#pragma once
#ifndef _SORTING_H
#define _SORTING_H

template<typename T>
struct func {
	typedef void(functionPtr)(T*, int);
};

namespace sort {
	// algorithms

	// std::sort
	template<typename T>
	void StandardSort(T* array, int size);

	template<typename T>
	void BubbleSort(T* array, int size);

	// Multithread a method
	template<typename T>
	void MultiSort(func<void>::functionPtr* function, T* array, int size, int threadCount);

	// Timed

	template<typename T>
	double SortTimed(func<void>::functionPtr* function, T* array, int size);
	template<typename T>
	double MultiSortTimed(func<void>::functionPtr* function, T* array, int size, int threadCount);
}

#endif