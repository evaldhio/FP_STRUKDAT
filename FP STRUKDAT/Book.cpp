#include "Book.h"
#include <sstream>

Book::Book(const std::string& isbn, const std::string& title, 
           const std::string& author, const std::string& genre)
    : isbn(isbn), title(title), author(author), genre(genre), isAvailable(true) {}

bool Book::borrow(const std::string& userId) {
    if (isAvailable) {
        isAvailable = false;
        borrowHistory.push_back(userId);
        return true;
    }
    return false;
}

bool Book::returnBook() {
    if (!isAvailable) {
        isAvailable = true;
        return true;
    }
    return false;
}

std::string Book::toString() const {
    std::stringstream ss;
    ss << title << " by " << author << " (ISBN: " << isbn << ")";
    return ss.str();
} 