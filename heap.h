//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        ++size;
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) { return -1; }
        int root = data[0];
        data[0] = data[size - 1];
        --size;
        if (size > 0) {
            downheap(0, weightArr);
        }
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int parent;
        while (pos > 0) {
            parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                int temp = data[parent];
                data[parent] = data[pos];
                data[pos] = temp;
                pos = parent;
            }
            else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int left_child, right_child, smallest_child;
        while ((2 * pos + 1) < size) {
            left_child = (2 * pos) + 1;
            right_child = (2 * pos) + 2;
            smallest_child = left_child;

            if (right_child < size) {
                if (weightArr[data[right_child]] < weightArr[data[left_child]]) {
                    smallest_child = right_child;
                }
            }

            if (weightArr[data[pos]] > weightArr[data[smallest_child]]) {
                int temp = data[pos];
                data[pos] = data[smallest_child];
                data[smallest_child] = temp;
                pos = smallest_child;
            }
            else {
                return;
            }
        }
    }
};

#endif