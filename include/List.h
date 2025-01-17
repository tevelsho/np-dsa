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
        bool add(T newItem);
        bool add(int index, T newItem);
        void remove(int index);
        ItemType get(int index); 
        int getLength();
        bool isEmpty(); 
        void print();
};