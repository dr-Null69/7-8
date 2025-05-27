#pragma once
#include "Node.hpp"

template<typename T>
class QueueList {
private:
    std::shared_ptr<Node<T>> front;
    std::shared_ptr<Node<T>> rear;

public:
    QueueList() : front(nullptr), rear(nullptr) {}

    void enqueue(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Черга порожня");
        front = front->next;
        if (!front) rear = nullptr;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Черга порожня");
        return front->data;
    }

    bool isEmpty() const { return front == nullptr; }
    bool isFull() const { return false; }
};
