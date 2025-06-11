#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
#include "Book.h"
#include "GenreTree.h"

class Library {
private:
    GenreTree genreTree;
    std::queue<std::pair<std::string, Book*>> borrowQueue;
    std::queue<std::pair<std::string, Book*>> returnQueue;
    std::stack<std::tuple<std::string, std::string, Book*>> actionHistory;
    std::vector<Book*> books;  // Track all books for cleanup

public:
    Library() = default;
    ~Library();  // Destructor to clean up memory
    
    Book* addBook(const std::string& isbn, const std::string& title, 
                 const std::string& author, const std::string& genre);
    bool requestBorrow(const std::string& userId, const std::string& bookISBN);
    bool requestReturn(const std::string& userId, const std::string& bookISBN);
    Book* processBorrowQueue();
    Book* processReturnQueue();
    std::tuple<std::string, std::string, Book*> undoLastAction();
    Book* searchByISBN(const std::string& isbn) const;
    Book* searchByTitle(const std::string& title) const;
    std::vector<Book*> getRecommendations(const std::string& bookISBN, int maxRecommendations = 5) const;
    std::vector<Book*> getBooksByGenre(const std::string& genre) const;
};

#endif 