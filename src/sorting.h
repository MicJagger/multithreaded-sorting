#pragma once
#ifndef _SORTING_H
#define _SORTING_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

typedef void(functionPtr)(int*, long long);

namespace sort {
    // Random Lists
	// "random" 15-bit integers
	void RandomList(int* array, int size);
    // ""random""" 30-bit integers
	void RandomList30(int* array, int size);
    // ""random""" 32-bit integers
	void RandomList32(int* array, int size);
    // notice the double quotes... i mean it does take multiple seeds so its less predictable
	
	// copy array 1->2
	void CopyArray(int* array1, int* array2, int size); // copy array1 to array2

	// test validity
	bool TestValid(int* array, int* correctArray, int size);

	// setup
	double MainSetup(int* unsorted, int* correct, int size);
	void Setup(std::string* name, int* unsorted, int* toSort, long long size, 
               int i, int j, bool first, std::vector<std::string>* names);

	// helper algorithms
	namespace helper {

	}

	// algorithms
	void StandardSort(int* array, int size);
	void BubbleSort(int* array, int size);

	// Timed
	double SortTimed(int* array, int size, functionPtr* func);

	// Multi-Threaded w/ Full array
	void Combine2ArrayA(int* array1, int* array2, int size1, int size2);
	void ThreadedSortA(int* array, int size, int threads, functionPtr* func);
	double ThreadedSortATimed(int* array, int size, int threads, functionPtr* func);

	// Multi-Threaded w/ Queue
    /*
    void Combine2ArrayQ(int* array1, int* array2, int size1, int size2);
	void ThreadedSortQ(int* array, int size, int threads, functionPtr* func);
	double ThreadedSortQTimed(int* array, int size, int threads, functionPtr* func);
    */

	// Mult-Threaded w/ Swaps
	//double ThreadedSortSwaps(int* array, int size);

}

#endif