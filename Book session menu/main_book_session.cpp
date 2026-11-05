#include "book_session_header.h"

int main()
{
    DoublyLinkedList session;
    int choice = 0;

    do
    {
        ShowMenu();
        choice = ReadInt("Enter your choice: ");

        switch (choice)
        {
        case 1:
            session.PrintCurrent();
            break;

        case 2:
            session.Next();
            break;

        case 3:
            session.Previous();
            break;

        case 4:
        {
            dNode* book = ReadBook(session);
            if (book)
            {
                session.InsertRight(book);
                cout << "Book added at the end of the session.\n";
            }
            break;
        }

        case 5:
        {
            dNode* book = ReadBook(session);
            if (book)
            {
                session.InsertAfterCurrent(book);
                cout << "Book inserted after the current book.\n";
            }
            break;
        }

        case 6:
        {
            dNode* removed = session.RemoveCurrent();
            if (removed)
            {
                cout << "Removed book: " << removed->title << endl;
                delete removed;
                session.PrintCurrent();
            }
            else
                cout << "The borrowing session is empty.\n";
            break;
        }

        case 7:
            session.PrintForward();
            break;

        case 8:
            session.PrintBackward();
            break;

        case 9:
            cout << "Exiting borrowing session manager. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 9.\n";
        }

    } while (choice != 9);

    return 0;
}
