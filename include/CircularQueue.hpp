#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class CircularQueue {
private:
    std::vector<T> buffer;
    size_t head, tail, count, capacity;

public:
    explicit CircularQueue(size_t size) : buffer(size), head(0), tail(0), count(0), capacity(size) {}

    void enqueue(const T& value) {
        if (isFull()) throw std::overflow_error("Циклічна черга переповнена");
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        ++count;
    }

    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Циклічна черга порожня");
        head = (head + 1) % capacity;
        --count;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Циклічна черга порожня");
        return buffer[head];
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
};
