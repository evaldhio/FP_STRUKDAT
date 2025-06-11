#include "Library.h"
#include <tuple>

Library::~Library() {
    // Clean up all allocated Book objects
    for (auto book : books) {
        delete book;
    }
}

Book* Library::addBook(const std::string& isbn, const std::string& title, 
                      const std::string& author, const std::string& genre) {
    // Check if a book with the same ISBN already exists
    if (genreTree.findBookByISBN(isbn)) {
        return nullptr;  // Book already exists, do not add
    }
    
    Book* book = new Book(isbn, title, author, genre);
    books.push_back(book);  // Track the book for cleanup
    genreTree.addBook(book);
    return book;
}

bool Library::requestBorrow(const std::string& userId, const std::string& bookISBN) {
    Book* book = genreTree.findBookByISBN(bookISBN);
    if (book && book->getAvailability()) {
        borrowQueue.push({userId, book});
        return true;
    }
    return false;
}

bool Library::requestReturn(const std::string& userId, const std::string& bookISBN) {
    Book* book = genreTree.findBookByISBN(bookISBN);
    if (book && !book->getAvailability()) {
        returnQueue.push({userId, book});
        return true;
    }
    return false;
}

Book* Library::processBorrowQueue() {
    if (borrowQueue.empty()) {
        return nullptr;
    }

    auto request = borrowQueue.front();
    borrowQueue.pop();
    std::string userId = std::get<0>(request);
    Book* book = std::get<1>(request);

    if (book->borrow(userId)) {
        actionHistory.push({"borrow", userId, book});
        return book;
    }
    return nullptr;
}

Book* Library::processReturnQueue() {
    if (returnQueue.empty()) {
        return nullptr;
    }

    auto request = returnQueue.front();
    returnQueue.pop();
    std::string userId = std::get<0>(request);
    Book* book = std::get<1>(request);

    if (book->returnBook()) {
        actionHistory.push({"return", userId, book});
        return book;
    }
    return nullptr;
}

std::tuple<std::string, std::string, Book*> Library::undoLastAction() {
    if (actionHistory.empty()) {
        return {"", "", nullptr};
    }

    auto action = actionHistory.top();
    actionHistory.pop();
    std::string actionType = std::get<0>(action);
    std::string userId = std::get<1>(action);
    Book* book = std::get<2>(action);

    if (actionType == "borrow") {
        book->returnBook();
        return {"return", userId, book};
    } else {  // actionType == "return"
        book->borrow(userId);
        return {"borrow", userId, book};
    }
}

Book* Library::searchByISBN(const std::string& isbn) const {
    return genreTree.findBookByISBN(isbn);
}

Book* Library::searchByTitle(const std::string& title) const {
    return genreTree.findBookByTitle(title);
}

std::vector<Book*> Library::getRecommendations(const std::string& bookISBN, int maxRecommendations) const {
    return genreTree.getRecommendations(bookISBN, maxRecommendations);
}

std::vector<Book*> Library::getBooksByGenre(const std::string& genre) const {
    return genreTree.getBooksByGenre(genre);
} 