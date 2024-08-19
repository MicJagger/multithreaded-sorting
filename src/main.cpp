#include "sorting.h"

// some main funcitons


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

    bool checkSorted = true;
    bool writeCSV = true;

    bool standard = true;
    bool bubble = true;
    bool heap = true;
    bool merge = true;
    bool quick = true;
}

int main() {


    return 0;
}

// function definitions

