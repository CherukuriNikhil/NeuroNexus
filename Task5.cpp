#include <bits/stdc++.h>
using namespace std;

// Book class to store book information
class Book {
public:
    string title;
    string author;
    string ISBN;
    bool available;

    Book(const string& title, const string& author, const string& ISBN)
        : title(title), author(author), ISBN(ISBN), available(true) {}
};

// Borrower class to store borrower information
class Borrower {
public:
    string name;
    string id;

    Borrower(const string& name, const string& id) : name(name), id(id) {}
};

// Transaction class to store checkout and return transactions
class Transaction {
public:
    Book* book;
    Borrower* borrower;
    time_t timestamp;
    bool isCheckout;

    Transaction(Book* book, Borrower* borrower, bool isCheckout)
        : book(book), borrower(borrower), isCheckout(isCheckout) {
        timestamp = time(nullptr);
    }
};

// Library class to manage books, borrowers, and transactions
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    // Function to add a book to the library
    void addBook(const string& title, const string& author, const string& ISBN) {
        books.emplace_back(title, author, ISBN);
        cout << "Book added: " << title << endl;
    }

    // Function to add a borrower to the library
    void addBorrower(const string& name, const string& id) {
        borrowers.emplace_back(name, id);
        cout << "Borrower added: " << name << endl;
    }

    // Function to search for books based on title, author, or ISBN
    void searchBooks(const string& keyword) {
        cout << "Search Results:" << endl;
        for (const Book& book : books) {
            if (book.title.find(keyword) != string::npos ||
                book.author.find(keyword) != string::npos ||
                book.ISBN.find(keyword) != string::npos) {
                cout << "Title: " << book.title << ", Author: " << book.author
                          << ", ISBN: " << book.ISBN << ", Available: "
                          << (book.available ? "Yes" : "No") << endl;
            }
        }
    }

    // Function to perform book checkout
    void checkoutBook(const string& ISBN, const string& borrowerId) {
        Book* book = findBookByISBN(ISBN);
        Borrower* borrower = findBorrowerById(borrowerId);

        if (book && borrower && book->available) {
            transactions.emplace_back(book, borrower, true);
            book->available = false;
            cout << "Book checked out successfully." << endl;
        } else {
            cout << "Book not available or borrower not found." << endl;
        }
    }

    // Function to perform book return
    void returnBook(const string& ISBN) {
        Book* book = findBookByISBN(ISBN);

        if (book && !book->available) {
            // Find the last transaction related to this book
            auto it = find_if(transactions.rbegin(), transactions.rend(),
                                   [book](const Transaction& t) { return t.book == book; });

            if (it != transactions.rend()) {
                it->book->available = true;
                transactions.emplace_back(book, it->borrower, false);
                cout << "Book returned successfully." << endl;
            } else {
                cout << "No checkout transaction found for this book." << endl;
            }
        } else {
            cout << "Book not found or already available." << endl;
        }
    }

    // Function to calculate fine for overdue books
    void calculateFine(const string& ISBN) {
        Book* book = findBookByISBN(ISBN);

        if (book && !book->available) {
            // Find the last transaction related to this book
            auto it = find_if(transactions.rbegin(), transactions.rend(),
                                   [book](const Transaction& t) { return t.book == book; });

            if (it != transactions.rend()) {
                time_t currentTime = time(nullptr);
                double daysLate = difftime(currentTime, it->timestamp) / (60 * 60 * 24);

                if (daysLate > 7) {
                    double fine = (daysLate - 7) * 0.5; // Assume a fine of 0.5 per day
                    cout << "Fine for overdue book: $" << fine << endl;
                } else {
                    cout << "Book is not overdue." << endl;
                }
            } else {
                cout << "No checkout transaction found for this book." << endl;
            }
        } else {
            cout << "Book not found or already available." << endl;
        }
    }

private:
    // Helper function to find a book by ISBN
    Book* findBookByISBN(const string& ISBN) {
        auto it = find_if(books.begin(), books.end(),
                               [ISBN](const Book& b) { return b.ISBN == ISBN; });

        return (it != books.end()) ? &(*it) : nullptr;
    }

    // Helper function to find a borrower by ID
    Borrower* findBorrowerById(const string& id) {
        auto it = find_if(borrowers.begin(), borrowers.end(),
                               [id](const Borrower& b) { return b.id == id; });

        return (it != borrowers.end()) ? &(*it) : nullptr;
    }
};

int main() {
    Library library;

    // Add some books and borrowers for testing
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "0061120081");
    library.addBorrower("John Doe", "B001");
    library.addBorrower("Jane Smith", "B002");

    int choice;

    do {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Search Books\n";
        cout << "2. Checkout Book\n";
        cout << "3. Return Book\n";
        cout << "4. Calculate Fine\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string keyword;
                cout << "Enter search keyword: ";
                cin.ignore(); // Clear input buffer
                getline(cin, keyword);
                library.searchBooks(keyword);
                break;
            }
            case 2: {
                string ISBN, borrowerId;
                cout << "Enter ISBN of the book to checkout: ";
                cin >> ISBN;
                cout << "Enter borrower ID: ";
                cin >> borrowerId;
                library.checkoutBook(ISBN, borrowerId);
                break;
            }
            case 3: {
                string ISBN;
                cout << "Enter ISBN of the book to return: ";
                cin >> ISBN;
                library.returnBook(ISBN);
                break;
            }
            case 4: {
                string ISBN;
                cout << "Enter ISBN of the book to calculate fine: ";
                cin >> ISBN;
                library.calculateFine(ISBN);
                break;
            }
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
