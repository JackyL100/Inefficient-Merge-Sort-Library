#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

namespace MergeSort {
    namespace {
        int leastGreatestPower(int num)  {
            int power = 0;
            int exp = 1;
            while (exp < num) {
                exp *= 2;
                power++;
            }
            return power;
        }

        template<typename T> void prepVec(std::vector<T>& vec) {
            int power = leastGreatestPower(vec.size());
            for (int i = vec.size(); i < pow(2, power); i++) {
                vec.push_back(0);
            }
        }

        template<typename T> std::vector<T> subVec(std::vector<T>& vec, int begin, int end) {
            std::vector<T> v = {vec.begin() + begin, vec.begin() + end};
            return v;
        }

        template<typename T> std::vector<T> trimFromFront(std::vector<T>& vec, int original_size) {
            std::vector<T> trimmed = subVec(vec, original_size, vec.size());
            return trimmed;
        }        

        template<typename T> void swap(T& first, T& second) {
            T temp = std::move(first);
            first = std::move(second);
            second = std::move(temp);
        }

        template<typename T> std::vector<T> merge(const std::vector<T>& left,const std::vector<T>& right, bool(*comparisonFunc)(T, T)) {
            std::vector<T> returned;
            int l, r;
            l = 0; r = 0;
            while(returned.size() < left.size() + right.size()) {
                if (l == left.size()) {
                    returned.push_back(right[r]);
                    r++;
                    continue;
                }
                if (r == right.size()) {
                    returned.push_back(left[l]);
                    l++;
                    continue;
                }
                if (comparisonFunc(left[l], right[r])) {
                    returned.push_back(left[l]);
                    l++;
                } else {
                    returned.push_back(right[r]);
                    r++;
                }
            }
            return returned;
        }

        template<typename T> void printVec(const std::vector<T>& vec) {
            for (const T i : vec) {
                std::cout << i << " ";
            }
            std::cout << "\n";
        }

        template<typename T> std::vector<T> sortMerge(std::vector<T>& arr, bool(*comparisonFunc)(T, T)) {
            if (arr.size() == 1) {
                return arr;
            }
            if (arr.size() == 2) {
                if (comparisonFunc(arr[1], arr[0])) {
                    swap(arr[0], arr[1]);
                } 
                return arr;
            } else {
                std::vector<T> returned;
                std::vector<T> left = subVec(arr, 0, arr.size() / 2);
                std::vector<T> right = subVec(arr, arr.size() / 2, arr.size());
                left = sortMerge<T>(left, comparisonFunc);
                right = sortMerge<T>(right, comparisonFunc);
                returned = merge(left, right, comparisonFunc);
                return returned;
            }
        }

    }

    template<typename T> std::vector<T> mergeSort(std::vector<T>& arr, bool(*comparisonFunc)(T, T)) {
        int size = arr.size();
        prepVec(arr);
        std::vector<T> sorted = sortMerge(arr, comparisonFunc);
        return trimFromFront(sorted, pow(2, leastGreatestPower(size)) - size);
    }
};

#endif