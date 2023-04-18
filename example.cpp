#include "merge_sort.hpp"
#include <vector>
#include <iostream>
#include <cmath>

bool intgreater(int num1, int num2) {
    return num1 < num2 ? true : false;
}

int main() {
    std::vector<int> test1 = {34, 2, 90, 245, 92, 67, 21, 43, 60, 2};
    std::vector<int> test2 = {2,1};
    MergeSort::printVec<int>(MergeSort::mergeSort<int>(test1,intgreater));
}