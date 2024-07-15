#ifndef WET1MIVNE_DEQUE_H
#define WET1MIVNE_DEQUE_H

#include <iostream>

template <typename T>
struct DequeNode {
    T data;
    DequeNode* prev;
    DequeNode* next;

    DequeNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class Deque {
private:
    DequeNode<T>* frontNode;
    DequeNode<T>* backNode;
    size_t size;

public:
    Deque() : frontNode(nullptr), backNode(nullptr), size(0) {}

    ~Deque() {
        while (!empty()) {
            pop_front();
        }
    }

    DequeNode<T>* push_back(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>(value);
        if (empty()) {
            frontNode = newNode;
            backNode = newNode;
        } else {
            newNode->prev = backNode;
            backNode->next = newNode;
            backNode = newNode;
        }
        size++;
        return newNode;
    }

    void pop_front() {
        if (empty()) {
            return;
        }
        DequeNode<T>* temp = frontNode;
        if (size == 1) {
            frontNode = nullptr;
            backNode = nullptr;
        } else {
            frontNode = frontNode->next;
            frontNode->prev = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        DequeNode<T>* temp = backNode;
        if (size == 1) {
            frontNode = nullptr;
            backNode = nullptr;
        } else {
            backNode = backNode->prev;
            backNode->next = nullptr;
        }
        delete temp;
        size--;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        return frontNode->data;
    }

    bool empty() const {
        return size == 0;
    }

    void erase(DequeNode<T>* node) {
        if (!node) return;

        if (node == frontNode) {
            pop_front();
        } else if (node == backNode) {
            pop_back();
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            size--;
        }
    }

};

#endif // WET1MIVNE_DEQUE_H
