#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <map>
#include "Library.h"
#include "Book.h"

void displayGenreMenu() {
    std::cout << "\n=== Available Genres ===\n";
    std::cout << "1. Programming\n";
    std::cout << "2. Fiction\n";
    std::cout << "3. Horror\n";
    std::cout << "4. Comedy\n";
    std::cout << "5. Science\n";
    std::cout << "6. History\n";
    std::cout << "7. All Books\n";
    std::cout << "Enter your choice: ";
}

void displayMenu() {
    std::cout << "\n=== Library Management System ===\n";
    std::cout << "1. Add a new book\n";
    std::cout << "2. Borrow a book\n";
    std::cout << "3. Return a book\n";
    std::cout << "4. Search book by ISBN\n";
    std::cout << "5. Search book by title\n";
    std::cout << "6. Browse books by genre\n";
    std::cout << "7. Get book recommendations\n";
    std::cout << "8. Undo last action\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void addNewBook(Library& library) {
    std::string isbn, title, author, genre;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    
    displayGenreMenu();
    int genreChoice;
    std::cin >> genreChoice;
    
    switch (genreChoice) {
        case 1:
            genre = "Programming";
            break;
        case 2:
            genre = "Fiction";
            break;
        case 3:
            genre = "Horror";
            break;
        case 4:
            genre = "Comedy";
            break;
        case 5:
            genre = "Science";
            break;
        case 6:
            genre = "History";
            break;
        default:
            std::cout << "Invalid genre choice. Book not added.\n";
            return;
    }
    
    Book* newBook = library.addBook(isbn, title, author, genre);
    if (newBook) {
        std::cout << "Book added successfully!\n";
    } else {
        std::cout << "Error: A book with ISBN " << isbn << " already exists. Book not added.\n";
    }
}

void borrowBook(Library& library) {
    std::string userId, isbn;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter your user ID: ";
    std::getline(std::cin, userId);
    std::cout << "Enter book ISBN: ";
    std::getline(std::cin, isbn);
    
    if (library.requestBorrow(userId, isbn)) {
        std::cout << "Borrow request added to queue\n";
        Book* borrowedBook = library.processBorrowQueue();
        if (borrowedBook) {
            std::cout << "Successfully borrowed: " << borrowedBook->toString() << "\n";
        }
    } else {
        std::cout << "Failed to borrow the book. It might be already borrowed.\n";
    }
}

void returnBook(Library& library) {
    std::string userId, isbn;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter your user ID: ";
    std::getline(std::cin, userId);
    std::cout << "Enter book ISBN: ";
    std::getline(std::cin, isbn);
    
    if (library.requestReturn(userId, isbn)) {
        std::cout << "Return request added to queue\n";
        Book* returnedBook = library.processReturnQueue();
        if (returnedBook) {
            std::cout << "Successfully returned: " << returnedBook->toString() << "\n";
        }
    } else {
        std::cout << "Failed to return the book.\n";
    }
}

void searchByISBN(Library& library) {
    std::string isbn;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);
    
    Book* book = library.searchByISBN(isbn);
    if (book) {
        std::cout << "Found: " << book->toString() << "\n";
        std::cout << "Availability: " << (book->getAvailability() ? "Available" : "Borrowed") << "\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

void searchByTitle(Library& library) {
    std::string title;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    
    Book* book = library.searchByTitle(title);
    if (book) {
        std::cout << "Found: " << book->toString() << "\n";
        std::cout << "Availability: " << (book->getAvailability() ? "Available" : "Borrowed") << "\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

void listByGenre(Library& library) {
    displayGenreMenu();
    int genreChoice;
    std::cin >> genreChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
    
    std::string genre;
    std::vector<std::string> genres = {"Programming", "Fiction", "Horror", "Comedy", "Science", "History"};
    
    switch (genreChoice) {
        case 1:
            genre = "Programming";
            break;
        case 2:
            genre = "Fiction";
            break;
        case 3:
            genre = "Horror";
            break;
        case 4:
            genre = "Comedy";
            break;
        case 5:
            genre = "Science";
            break;
        case 6:
            genre = "History";
            break;
        case 7:
            // Show all books by listing each genre
            std::cout << "\n=== All Books in Library ===\n";
            for (const auto& g : genres) {
                auto books = library.getBooksByGenre(g);
                if (!books.empty()) {
                    std::cout << "\nBooks in " << g << " genre:\n";
                    for (const auto& book : books) {
                        std::cout << "- " << book->toString() << "\n";
                        std::cout << "  Availability: " << (book->getAvailability() ? "Available" : "Borrowed") << "\n";
                    }
                }
            }
            return;
        default:
            std::cout << "Invalid genre choice.\n";
            return;
    }
    
    auto books = library.getBooksByGenre(genre);
    if (books.empty()) {
        std::cout << "No books found in " << genre << " genre.\n";
    } else {
        std::cout << "\nBooks in " << genre << " genre:\n";
        for (const auto& book : books) {
            std::cout << "- " << book->toString() << "\n";
            std::cout << "  Availability: " << (book->getAvailability() ? "Available" : "Borrowed") << "\n";
        }
    }
}

void getRecommendations(Library& library) {
    std::string isbn;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter book ISBN for recommendations: ";
    std::getline(std::cin, isbn);
    
    auto recommendations = library.getRecommendations(isbn);
    if (recommendations.empty()) {
        std::cout << "No recommendations found.\n";
    } else {
        std::cout << "\nRecommended books:\n";
        for (const auto& book : recommendations) {
            std::cout << "- " << book->toString() << "\n";
        }
    }
}

void undoLastAction(Library& library) {
    auto result = library.undoLastAction();
    if (std::get<2>(result)) {
        std::cout << "Undid " << std::get<0>(result) << " of " 
                  << std::get<2>(result)->toString() 
                  << " by " << std::get<1>(result) << "\n";
    } else {
        std::cout << "No actions to undo.\n";
    }
}

int main() {
    Library library;
    
    // Add some sample books with simpler ISBNs
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> books = {
        {"001", "Clean Code", "Robert C. Martin", "Programming"},
        {"002", "Clean Architecture", "Robert C. Martin", "Programming"},
        {"003", "Design Patterns", "Erich Gamma", "Programming"},
        {"004", "To Kill a Mockingbird", "Harper Lee", "Fiction"},
        {"005", "1984", "George Orwell", "Fiction"},
        {"006", "The Alchemist", "Paulo Coelho", "Fiction"},
        {"007", "The Shining", "Stephen King", "Horror"},
        {"008", "The Hitchhiker's Guide", "Douglas Adams", "Comedy"},
        {"009", "Astrophysics for People", "Neil deGrasse Tyson", "Science"},
        {"010", "Sapiens", "Yuval Noah Harari", "History"}
    };
    
    for (const auto& book : books) {
        library.addBook(std::get<0>(book), std::get<1>(book), 
                       std::get<2>(book), std::get<3>(book));
    }

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addNewBook(library);
                break;
            case 2:
                borrowBook(library);
                break;
            case 3:
                returnBook(library);
                break;
            case 4:
                searchByISBN(library);
                break;
            case 5:
                searchByTitle(library);
                break;
            case 6:
                listByGenre(library);
                break;
            case 7:
                getRecommendations(library);
                break;
            case 8:
                undoLastAction(library);
                break;
            case 0:
                std::cout << "Thank you for using the Library Management System!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
} 