#pragma once
#include "Node.hpp"
#include <iostream>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }

    void pushFront(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
        ++size;
    }

    void pushBack(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void popFront() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        head = head->next;
        if (head) head->prev.reset();
        else tail.reset();
        --size;
    }

    void popBack() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        if (!tail->prev.lock()) {
            head = tail = nullptr;
        } else {
            tail = tail->prev.lock();
            tail->next.reset();
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
        if (index == size) return pushBack(value);

        auto newNode = std::make_shared<Node<T>>(value);
        auto temp = head;
        for (size_t i = 0; i < index; ++i) temp = temp->next;

        newNode->prev = temp->prev;
        newNode->next = temp;
        temp->prev.lock()->next = newNode;
        temp->prev = newNode;
        ++size;
    }

    void removeAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        if (index == 0) return popFront();
        if (index == size - 1) return popBack();

        auto temp = head;
        for (size_t i = 0; i < index; ++i) temp = temp->next;

        auto prevNode = temp->prev.lock();
        auto nextNode = temp->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
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

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        auto temp = list.head;
        os << "[";
        while (temp) {
            os << temp->data;
            if (temp->next) os << " <-> ";
            temp = temp->next;
        }
        os << "]";
        return os;
    }
};