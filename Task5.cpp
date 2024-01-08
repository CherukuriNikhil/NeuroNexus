#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> 

// Book class to store book information
class Book {
public:
    std::string title;
    std::string author;
    std::string ISBN;
    bool available;

    Book(const std::string& title, const std::string& author, const std::string& ISBN)
        : title(title), author(author), ISBN(ISBN), available(true) {}
};

// Borrower class to store borrower information
class Borrower {
public:
    std::string name;
    std::string id;

    Borrower(const std::string& name, const std::string& id) : name(name), id(id) {}
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
    std::vector<Book> books;
    std::vector<Borrower> borrowers;
    std::vector<Transaction> transactions;

public:
    // Function to add a book to the library
    void addBook(const std::string& title, const std::string& author, const std::string& ISBN) {
        books.emplace_back(title, author, ISBN);
        std::cout << "Book added: " << title << std::endl;
    }

    // Function to add a borrower to the library
    void addBorrower(const std::string& name, const std::string& id) {
        borrowers.emplace_back(name, id);
        std::cout << "Borrower added: " << name << std::endl;
    }

    // Function to search for books based on title, author, or ISBN
    void searchBooks(const std::string& keyword) {
        std::cout << "Search Results:" << std::endl;
        for (const Book& book : books) {
            if (book.title.find(keyword) != std::string::npos ||
                book.author.find(keyword) != std::string::npos ||
                book.ISBN.find(keyword) != std::string::npos) {
                std::cout << "Title: " << book.title << ", Author: " << book.author
                          << ", ISBN: " << book.ISBN << ", Available: "
                          << (book.available ? "Yes" : "No") << std::endl;
            }
        }
    }

    // Function to perform book checkout
    void checkoutBook(const std::string& ISBN, const std::string& borrowerId) {
        Book* book = findBookByISBN(ISBN);
        Borrower* borrower = findBorrowerById(borrowerId);

        if (book && borrower && book->available) {
            transactions.emplace_back(book, borrower, true);
            book->available = false;
            std::cout << "Book checked out successfully." << std::endl;
        } else {
            std::cout << "Book not available or borrower not found." << std::endl;
        }
    }

    // Function to perform book return
    void returnBook(const std::string& ISBN) {
        Book* book = findBookByISBN(ISBN);

        if (book && !book->available) {
            // Find the last transaction related to this book
            auto it = std::find_if(transactions.rbegin(), transactions.rend(),
                                   [book](const Transaction& t) { return t.book == book; });

            if (it != transactions.rend()) {
                it->book->available = true;
                transactions.emplace_back(book, it->borrower, false);
                std::cout << "Book returned successfully." << std::endl;
            } else {
                std::cout << "No checkout transaction found for this book." << std::endl;
            }
        } else {
            std::cout << "Book not found or already available." << std::endl;
        }
    }

    // Function to calculate fine for overdue books
    void calculateFine(const std::string& ISBN) {
        Book* book = findBookByISBN(ISBN);

        if (book && !book->available) {
            // Find the last transaction related to this book
            auto it = std::find_if(transactions.rbegin(), transactions.rend(),
                                   [book](const Transaction& t) { return t.book == book; });

            if (it != transactions.rend()) {
                time_t currentTime = time(nullptr);
                double daysLate = difftime(currentTime, it->timestamp) / (60 * 60 * 24);

                if (daysLate > 7) {
                    double fine = (daysLate - 7) * 0.5; // Assume a fine of 0.5 per day
                    std::cout << "Fine for overdue book: $" << fine << std::endl;
                } else {
                    std::cout << "Book is not overdue." << std::endl;
                }
            } else {
                std::cout << "No checkout transaction found for this book." << std::endl;
            }
        } else {
            std::cout << "Book not found or already available." << std::endl;
        }
    }

private:
    // Helper function to find a book by ISBN
    Book* findBookByISBN(const std::string& ISBN) {
        auto it = std::find_if(books.begin(), books.end(),
                               [ISBN](const Book& b) { return b.ISBN == ISBN; });

        return (it != books.end()) ? &(*it) : nullptr;
    }

    // Helper function to find a borrower by ID
    Borrower* findBorrowerById(const std::string& id) {
        auto it = std::find_if(borrowers.begin(), borrowers.end(),
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
        std::cout << "\nLibrary Management System Menu:\n";
        std::cout << "1. Search Books\n";
        std::cout << "2. Checkout Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Calculate Fine\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string keyword;
                std::cout << "Enter search keyword: ";
                std::cin.ignore(); // Clear input buffer
                std::getline(std::cin, keyword);
                library.searchBooks(keyword);
                break;
            }
            case 2: {
                std::string ISBN, borrowerId;
                std::cout << "Enter ISBN of the book to checkout: ";
                std::cin >> ISBN;
                std::cout << "Enter borrower ID: ";
                std::cin >> borrowerId;
                library.checkoutBook(ISBN, borrowerId);
                break;
            }
            case 3: {
                std::string ISBN;
                std::cout << "Enter ISBN of the book to return: ";
                std::cin >> ISBN;
                library.returnBook(ISBN);
                break;
            }
            case 4: {
                std::string ISBN;
                std::cout << "Enter ISBN of the book to calculate fine: ";
                std::cin >> ISBN;
                library.calculateFine(ISBN);
                break;
            }
            case 5:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
