#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class StackArray {
private:
    std::vector<T> data;
    size_t capacity;

public:
    explicit StackArray(size_t size) : capacity(size) {}

    void push(const T& value) {
        if (isFull()) throw std::overflow_error("Стек переповнений");
        data.push_back(value);
    }

    void pop() {
        if (isEmpty()) throw std::underflow_error("Стек порожній");
        data.pop_back();
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Стек порожній");
        return data.back();
    }

    bool isEmpty() const { return data.empty(); }
    bool isFull() const { return data.size() == capacity; }
};
