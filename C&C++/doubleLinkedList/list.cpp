#pragma once
#include <iostream>
#include "list.h"
using namespace std;

List::List()
{
    elements = 0;
    head = tail = nullptr;
}

void List::Add(int newElement)
{
    Node *c = new Node(newElement);

    if (head == nullptr)
    {
        head = c;
        tail = c;
        return;
    }

    c->setPrevious(tail);
    tail->setNext(c);
    tail = c;
}

void List::Push(int newElement)
{
    Node *c = new Node(newElement);

    if (head == nullptr)
    {
        head = c;
        tail = c;
        return;
    }

    head->setPrevious(c);
    c->setNext(head);
    head = c;
}

void List::AddAt(int newElement, int position)
{
    if (position < 0)
    {
        cout << "Position cannot be negative!" << endl;
        return;
    }
    else if (head == nullptr || tail == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    int counter = 0;
    Node *element = head;

    while (counter < position)
    {
        if (element == nullptr)
        {
            cout << "Error with AddAt!" << endl;
            return;
        }
        element = element->getNext();
        counter++;
    }

    Node *c = new Node(newElement);
    c->setNext(element->getNext());
    c->setPrevious(element);
    element->setNext(c);

    if (element == tail)
    {
        tail = c;
    }
}

int List::Get()
{
    if (head == nullptr || tail == nullptr)
    {
        cout << "List is empty!" << endl;
        return -1;
    }

    return tail->getValue();
}

int List::GetAt(int position)
{
    if (position < 0)
    {
        cout << "Position cannot be negative!" << endl;
        return -1;
    }
    else if (head == nullptr || tail == nullptr)
    {
        cout << "List is empty!" << endl;
        return -1;
    }

    int counter = 0;
    Node *element = head;
    while (counter < position)
    {
        if (element == nullptr)
        {
            cout << "Error with GetAt!" << endl;
            return -1;
        }
        element = element->getNext();
        counter++;
    }

    return element->getValue();
}

int List::Pop()
{
    if (head == nullptr || tail == nullptr)
    {
        cout << "List is empty!" << endl;
        return -1;
    }

    Node *newHead = head->getNext();
    int firstValue = head->getValue();

    delete head;
    head = newHead;

    if (head != nullptr)
        head->setPrevious(nullptr);

    return firstValue;
}

int List::RemoveAt(int position)
{
    if (position < 0)
    {
        cout << "Position cannot be negative!" << endl;
        return -1;
    }
    else if (head == nullptr || tail == nullptr)
    {
        cout << "List is empty!" << endl;
        return -1;
    }

    int counter = 0;
    Node *element = head;
    while (counter < position)
    {
        if (element == nullptr)
        {
            cout << "Error with RemoveAt!" << endl;
            return -1;
        }
        element = element->getNext();
        counter++;
    }

    if (head == element)
        return this->Pop();

    int removedValue = element->getValue();
    element->getPrevious()->setNext(element->getNext());

    if (tail != element)
    {
        element->getNext()->setPrevious(element->getPrevious());
    }
    else
    {
        tail = tail->getPrevious();
    }

    delete element;

    return removedValue;
}

void List::Display()
{
    Node *element = head;

    if (element == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    cout << "List: ";
    while (element != nullptr)
    {
        cout << element->getValue() << " ";
        element = element->getNext();
    }
    cout << endl;
}

void List::Sort()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *smallest = current, *compare = current->getNext();
        while (compare != nullptr)
        {
            if (compare->getValue() < smallest->getValue())
                smallest = compare;
            compare = compare->getNext();
        }

        int temp = current->getValue();
        current->setValue(smallest->getValue());
        smallest->setValue(temp);
        current = current->getNext();
    }
}