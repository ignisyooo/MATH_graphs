#pragma once

#include <memory>
#include <iostream>

struct Node {
    int fdata;
    std::unique_ptr<Node> next;

    Node(int data) : fdata(data), next(nullptr) {};
};

class List {
    private:
        std::unique_ptr<Node> head;

    public:
        List() : head(nullptr) {};
        List(const List &list);
        List(List &&list);

        ~List() { clean(); }

    public:
        bool isEmpty(void) const { return !head; }
        int GetTopValue(void) const;
        void push(int data);
        void pop(void);
        void clean(void);

        friend std::ostream &operator << (std::ostream &o, const List &list);
};