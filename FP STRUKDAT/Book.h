#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string genre;
    bool isAvailable;
    std::vector<std::string> borrowHistory;

public:
    Book(const std::string& isbn, const std::string& title, 
         const std::string& author, const std::string& genre);
    
    // Getters
    std::string getISBN() const { return isbn; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getGenre() const { return genre; }
    bool getAvailability() const { return isAvailable; }
    
    // Methods
    bool borrow(const std::string& userId);
    bool returnBook();
    std::string toString() const;
};

#endif 