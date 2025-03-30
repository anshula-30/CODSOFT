#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> // Required for remove()

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable = true;
    time_t dueDate = 0;  // Store due date for fine calculation
};

struct Borrower {
    string name;
    string borrowedISBN;
    time_t borrowDate;
};

vector<Book> books;
vector<Borrower> borrowers;

void addBook() {
    Book newBook;
    cin.ignore(); // Ignore previous input
    cout << "Enter book title: ";
    getline(cin, newBook.title);
    cout << "Enter author: ";
    getline(cin, newBook.author);
    cout << "Enter ISBN: ";
    getline(cin, newBook.ISBN);
    books.push_back(newBook);
    cout << "Book added successfully!\n";
}

void searchBook() {
    string query;
    cin.ignore();
    cout << "Enter title, author, or ISBN to search: ";
    getline(cin, query);
    
    bool found = false;
    for (const auto& book : books) {
        if (book.title == query || book.author == query || book.ISBN == query) {
            cout << "Book Found: " << book.title << " by " << book.author;
            cout << " [ISBN: " << book.ISBN << "] " 
                 << (book.isAvailable ? "[Available]\n" : "[Checked Out]\n");
            found = true;
        }
    }
    if (!found) cout << "Book not found!\n";
}

void checkoutBook() {
    string borrowerName, bookISBN;
    cin.ignore();
    cout << "Enter borrower's name: ";
    getline(cin, borrowerName);
    cout << "Enter book ISBN: ";
    getline(cin, bookISBN);

    for (auto& book : books) {
        if (book.ISBN == bookISBN && book.isAvailable) {
            book.isAvailable = false;
            time_t now = time(0);
            book.dueDate = now + (7 * 24 * 60 * 60); // Due in 7 days
            borrowers.push_back({borrowerName, bookISBN, now});
            cout << "Book checked out successfully!\n";
            return;
        }
    }
    cout << "Book not available or incorrect ISBN!\n";
}

void returnBook() {
    string bookISBN;
    cin.ignore();
    cout << "Enter ISBN of the book to return: ";
    getline(cin, bookISBN);

    for (auto& book : books) {
        if (book.ISBN == bookISBN && !book.isAvailable) {
            book.isAvailable = true;
            time_t now = time(0);

            double fine = 0;
            auto it = borrowers.begin();
            while (it != borrowers.end()) {
                if (it->borrowedISBN == bookISBN) {
                    if (now > book.dueDate) {
                        fine = (now - book.dueDate) / (24 * 60 * 60) * 5; // Rs. 5 per day
                    }
                    it = borrowers.erase(it); // Safely remove borrower
                    break;
                } else {
                    ++it;
                }
            }

            cout << "Book returned successfully!\n";
            if (fine > 0) cout << "Late return! Fine to be paid: Rs. " << fine << "\n";
            return;
        }
    }
    cout << "Invalid ISBN or book was not checked out!\n";
}

void displayBooks() {
    cout << "Library Books:\n";
    for (const auto& book : books) {
        cout << book.title << " by " << book.author 
             << " [ISBN: " << book.ISBN << "] " 
             << (book.isAvailable ? "[Available]\n" : "[Checked Out]\n");
    }
}

int main() {
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: displayBooks(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
