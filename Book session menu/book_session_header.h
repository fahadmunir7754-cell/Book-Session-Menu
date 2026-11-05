#ifndef BOOK_SESSION_HEADER_H
#define BOOK_SESSION_HEADER_H

#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct dNode
{
    int bookID;
    string title;
    dNode* left;
    dNode* right;

    dNode(int id, string name)
    {
        bookID = id;
        title = name;
        left = nullptr;
        right = nullptr;
    }
};

class DoublyLinkedList
{
private:
    dNode* head;
    dNode* tail;
    dNode* current;
    int count;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    bool IsEmpty();
    int GetCount();
    bool IDExists(int id);
    void InsertRight(dNode* node);
    void Next();
    void Previous();
    void PrintCurrent();
    void InsertAfterCurrent(dNode* node);
    dNode* RemoveCurrent();
    void PrintForward();
    void PrintBackward();
    ~DoublyLinkedList();
};

int ReadInt(const string& prompt);
string ReadTitle();
dNode* ReadBook(DoublyLinkedList& session);
void ShowMenu();

#endif
