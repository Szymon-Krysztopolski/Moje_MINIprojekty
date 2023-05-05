#pragma once
#include <iostream>
using namespace std;

class Node
{
    Node *next, *previous;
    int value;

public:
    Node(int v)
    {
        value = v;
        next = nullptr;
        previous = nullptr;
    }
    int getValue() { return value; }
    void setValue(int v) { value = v; }
    Node *getNext() { return next; }
    void setNext(Node *n) { next = n; }
    Node *getPrevious() { return previous; }
    void setPrevious(Node *p) { previous = p; }
};

class List
{
    int elements;
    Node *head, *tail;

public:
    List();
    void Add(int newElement);
    void Push(int newElement);
    void AddAt(int newElement, int position);
    int Get();
    int GetAt(int position);
    int Pop();
    int RemoveAt(int position);

    void Sort();
    void Display();
};
