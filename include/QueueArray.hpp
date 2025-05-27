#pragma once
#include <stdexcept>
#include <vector>

template<typename T>
class QueueArray {
private:
    std::vector<T> data;
    size_t capacity;
    size_t front;
    size_t rear;
    size_t count;

public:
    explicit QueueArray(size_t size) : capacity(size), front(0), rear(0), count(0), data(size) {}

    void enqueue(const T& value) {
        if (isFull()) throw std::overflow_error("Черга заповнена");
        data[rear] = value;
        rear = (rear + 1) % capacity;
        ++count;
    }

    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Черга порожня");
        front = (front + 1) % capacity;
        --count;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Черга порожня");
        return data[front];
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
};
