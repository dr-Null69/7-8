#pragma once
#include "Node.hpp"

template<typename T>
class StackList {
private:
    std::shared_ptr<Node<T>> top;

public:
    StackList() : top(nullptr) {}

    void push(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) throw std::underflow_error("Стек порожній");
        top = top->next;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Стек порожній");
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
    bool isFull() const { return false; } // список не обмежений
};
