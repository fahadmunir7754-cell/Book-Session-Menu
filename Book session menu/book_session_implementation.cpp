#include "book_session_header.h"

DoublyLinkedList::DoublyLinkedList()
{
    head = tail = current = nullptr;
    count = 0;
}

bool DoublyLinkedList::IsEmpty()
{
    return head == nullptr;
}

int DoublyLinkedList::GetCount()
{
    return count;
}

bool DoublyLinkedList::IDExists(int id)
{
    for (dNode* node = head; node != nullptr; node = node->right)
        if (node->bookID == id)
            return true;
    return false;
}

void DoublyLinkedList::InsertRight(dNode* node)
{
    if (node == nullptr)
        return;

    node->left = tail;
    node->right = nullptr;

    if (tail != nullptr)
        tail->right = node;
    else
        head = node;

    tail = node;

    if (current == nullptr)
        current = node;

    count++;
}

void DoublyLinkedList::Next()
{
    if (IsEmpty())
        cout << "The borrowing session is empty.\n";
    else if (current->right != nullptr)
    {
        current = current->right;
        PrintCurrent();
    }
    else
        cout << "No next book. You are at the last book.\n";
}

void DoublyLinkedList::Previous()
{
    if (IsEmpty())
        cout << "The borrowing session is empty.\n";
    else if (current->left != nullptr)
    {
        current = current->left;
        PrintCurrent();
    }
    else
        cout << "No previous book. You are at the first book.\n";
}

void DoublyLinkedList::PrintCurrent()
{
    if (current == nullptr)
    {
        cout << "The borrowing session is empty.\n";
        return;
    }
    cout << "Current Book: " << current->bookID << " - " << current->title << endl;
}

void DoublyLinkedList::InsertAfterCurrent(dNode* node)
{
    if (node == nullptr)
        return;

    if (current == nullptr)
    {
        InsertRight(node);
        return;
    }

    node->left = current;
    node->right = current->right;

    if (current->right != nullptr)
        current->right->left = node;
    else
        tail = node;

    current->right = node;
    count++;
}

dNode* DoublyLinkedList::RemoveCurrent()
{
    if (current == nullptr)
        return nullptr;

    dNode* removed = current;
    dNode* previous = current->left;
    dNode* next = current->right;

    if (previous != nullptr)
        previous->right = next;
    else
        head = next;

    if (next != nullptr)
        next->left = previous;
    else
        tail = previous;

    current = (next != nullptr) ? next : previous;

    removed->left = nullptr;
    removed->right = nullptr;
    count--;
    return removed;
}

void DoublyLinkedList::PrintForward()
{
    if (IsEmpty())
    {
        cout << "The borrowing session is empty.\n";
        return;
    }
    cout << "\nBorrowing Session (First to Last):\n";
    for (dNode* node = head; node != nullptr; node = node->right)
    {
        cout << node->bookID << " - " << node->title;
        if (node == current)
            cout << " [CURRENT]";
        cout << endl;
    }
    cout << "Total books: " << count << endl;
}

void DoublyLinkedList::PrintBackward()
{
    if (IsEmpty())
    {
        cout << "The borrowing session is empty.\n";
        return;
    }
    cout << "\nBorrowing Session (Last to First):\n";
    for (dNode* node = tail; node != nullptr; node = node->left)
    {
        cout << node->bookID << " - " << node->title;
        if (node == current)
            cout << " [CURRENT]";
        cout << endl;
    }
    cout << "Total books: " << count << endl;
}

DoublyLinkedList::~DoublyLinkedList()
{
    dNode* node = head;
    while (node != nullptr)
    {
        dNode* next = node->right;
        delete node;
        node = next;
    }
}

int ReadInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string ReadTitle()
{
    string title;
    while (true)
    {
        cout << "Enter Book Title: ";
        getline(cin, title);
        if (!title.empty())
            return title;
        cout << "Title cannot be empty.\n";
    }
}

dNode* ReadBook(DoublyLinkedList& session)
{
    int id = ReadInt("Enter Book ID: ");
    if (session.IDExists(id))
    {
        cout << "A book with ID " << id << " is already in this session. Nothing added.\n";
        return nullptr;
    }
    return new dNode(id, ReadTitle());
}

void ShowMenu()
{
    cout << "\n========================================\n"
         << "   LIBRARY BORROWING SESSION MANAGER\n"
         << "========================================\n"
         << "1. Display Current Book\n"
         << "2. Move to Next Book\n"
         << "3. Move to Previous Book\n"
         << "4. Insert Book at the End\n"
         << "5. Insert Book After Current Book\n"
         << "6. Remove Current Book\n"
         << "7. Display Session from First to Last\n"
         << "8. Display Session from Last to First\n"
         << "9. Exit\n";
}
