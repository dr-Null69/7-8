#pragma once
#include "Node.hpp"
#include <iostream>
#include <stdexcept>

template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    size_t size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }

    void pushFront(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void pushBack(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
        } else {
            auto temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        ++size;
    }

    void popFront() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        head = head->next;
        --size;
    }

    void popBack() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        if (!head->next) {
            head = nullptr;
        } else {
            auto temp = head;
            while (temp->next->next) temp = temp->next;
            temp->next = nullptr;
        }
        --size;
    }

    T& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        auto temp = head;
        for (size_t i = 0; i < index; ++i) temp = temp->next;
        return temp->data;
    }

    void insertAt(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of bounds");
        if (index == 0) return pushFront(value);

        auto newNode = std::make_shared<Node<T>>(value);
        auto temp = head;
        for (size_t i = 0; i < index - 1; ++i) temp = temp->next;

        newNode->next = temp->next;
        temp->next = newNode;
        ++size;
    }

    void removeAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        if (index == 0) return popFront();

        auto temp = head;
        for (size_t i = 0; i < index - 1; ++i) temp = temp->next;
        temp->next = temp->next->next;
        --size;
    }

    int find(const T& value) const {
        auto temp = head;
        size_t index = 0;
        while (temp) {
            if (temp->data == value) return index;
            temp = temp->next;
            ++index;
        }
        return -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
        auto temp = list.head;
        os << "[";
        while (temp) {
            os << temp->data;
            if (temp->next) os << " -> ";
            temp = temp->next;
        }
        os << "]";
        return os;
    }
};