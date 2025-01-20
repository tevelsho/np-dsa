#pragma once
#include <string>
#include <iostream>
using namespace std;

template <typename T>

class List {
    private:
        struct Node {
            T item; 
            Node* next; 
        };

        Node* firstNode; 
        int size;	

    public:
        List();
        ~List();
        bool add(const T& newItem);
        bool add(int index, const T& newItem);
        void remove(int index);
        T get(int index) const; 
        int getLength() const;
        bool isEmpty() const; 
        void print() const;
};