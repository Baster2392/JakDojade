#pragma once
#include "Vector.h"
#include "City.h"

class PriorityQueue {
private:
    Vector<ListOfNeighbors> heap;

    void heapifyUp(int i)
    {
        int parent = (i - 1) / 2;
        if (i > 0 && heap[i].distance > heap[parent].distance) {
            ListOfNeighbors help = heap[i];
            heap[i] = heap[parent];
            heap[parent] = help;

            heapifyUp(parent);
        }
    }

    void heapifyDown(int i)
    {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int largest = i;

        if (leftChild < heap.getSize() && heap[leftChild].distance > heap[largest].distance)
        {
            largest = leftChild;
        }

        if (rightChild < heap.getSize() && heap[rightChild].distance > heap[largest].distance)
        {
            largest = rightChild;
        }

        if (largest != i)
        {
            ListOfNeighbors help = heap[i];
            heap[i] = heap[largest];
            heap[largest] = help;

            heapifyDown(largest);
        }
    }

public:
    void push(ListOfNeighbors& value) {

        heap.pushBack(value);
        heapifyUp(heap.getSize() - 1);
    }

    void pop() {
        if (!heap.getSize() == 0) {
            heap[0] = heap[heap.getSize() - 1];
            heap.popBack();
            heapifyDown(0);
        }
    }

    ListOfNeighbors top()
    {
        return heap[0];
    }

    bool empty()
    {
        return heap.getSize() == 0;
    }

    int size()
    {
        return heap.getSize();
    }

    ListOfNeighbors operator[](int index)
    {
        return this->heap[index];
    }
};