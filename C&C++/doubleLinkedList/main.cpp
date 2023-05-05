#include <iostream>
#include "list.h"
#include "list.cpp"

using namespace std;

int elem, pos;

void menu();
void menuOneArgElem();
void menuOneArgPos();
void menuTwoArgs();
void menuResultElem(int elem);

int main()
{
    List *list = new List();
    cout << "Double linked list" << endl;

    while (true)
    {
        cout << "----------------------------------------" << endl;
        cout << "Debug display" << endl;
        list->Display();
        cout << "----------------------------------------" << endl;

        menu();
        char option;

        cin >> option;

        switch (option)
        {
        case '0':
            delete list;
            list = new List();
            break;

        case '1':
            menuOneArgElem();
            list->Add(elem);
            break;

        case '2':
            menuOneArgElem();
            list->Push(elem);
            break;

        case '3':
            menuTwoArgs();
            list->AddAt(elem, pos);
            break;

        case '4':
            menuResultElem(list->Get());
            break;

        case '5':
            menuOneArgPos();
            menuResultElem(list->GetAt(pos));
            break;

        case '6':
            menuResultElem(list->Pop());
            break;

        case '7':
            menuOneArgPos();
            menuResultElem(list->RemoveAt(pos));
            break;

        case '8':
            list->Sort();
            list->Display();
            break;

        case '9':
            list->Display();
            break;

        default:
            return 0;
            break;
        }
    }

    return 0;
}

void menu()
{
    cout << "----------------------------------------" << endl;
    cout << "0. Create new" << endl;
    cout << "1. Add - adds a new element to the end of the list." << endl;
    cout << "2. Push - adds a new element to the beginning of the list." << endl;
    cout << "3. AddAt - adds a new element after the element at pointed position." << endl;
    cout << "4. Get - returns an element from the end of the list." << endl;
    cout << "5. GetAt - returns an element from the item with index posiotion." << endl;
    cout << "6. Pop - returns an element from the beginning of the list." << endl;
    cout << "7. RemoveAt - returns an element from the indicated position." << endl;
    cout << "8. Sort & Display" << endl;
    cout << "9. Display" << endl;
    cout << "e. Exit" << endl;

    cout << "Choose once option: ";
}

void menuResultElem(int elem)
{
    cout << "This is your element: " << elem << endl;
}

void menuOneArgElem()
{
    cout << "Give VALUE of element: ";
    cin >> elem;
}

void menuOneArgPos()
{
    cout << "Give POSITION of element: ";
    cin >> pos;
}

void menuTwoArgs()
{
    cout << "Give value of element and position: ";
    cin >> elem >> pos;
}