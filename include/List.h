//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_LIST_H
#define PROTOKIT_STD_LIST_H

#include "ArduinoButton.h"

template<typename T>
class List {
public:
    struct Node {
        T *item;
        Node *next = nullptr;
    };

public:
    List() = default;

    void add(T *item) {
        auto *itemNode = new Node;
        itemNode->item = item;
        itemNode->next = nullptr;

        if (_first == nullptr) {
            _first = itemNode;
            _last = itemNode;
        } else {
            _last->next = itemNode;
            _last = itemNode;
        }
    }

    void remove(T *item) {
        if (_first == nullptr) {
            return;
        } else if (_first->item == item) {
            auto deleteNode = _first;

            if (_first == _last) {
                _first = nullptr;
                _last = nullptr;
            } else {
                _first = _first->next;
            }

            delete deleteNode;
        }
        if (_first != nullptr) {
            auto *current = _first;

            while (current->next != nullptr &&
                   current->next->item != item) {
                current = current->next;
            }


            if (current->next != nullptr) {
                delete current->next;

                current->next = current->next->next;
                if (current->next == nullptr) {
                    _last = current;
                }
            }
        }
    }


    Node *firstNode() {
        return _first;
    }

    T *first() {
        if (_first == nullptr) {
            return nullptr;
        }

        return _first->item;
    }

    T *last() {
        if (_last == nullptr) {
            return nullptr;
        }
        return _last->item;
    }

private:
    Node *_first = nullptr;
    Node *_last = nullptr;
};


#endif //PROTOKIT_STD_LIST_H
