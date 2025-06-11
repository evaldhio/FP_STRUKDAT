#ifndef GENRE_TREE_H
#define GENRE_TREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Book.h"

class GenreTree {
private:
    std::unordered_map<std::string, std::vector<Book*>> genreBooks;
    std::unordered_map<std::string, Book*> isbnToBook;
    std::unordered_map<std::string, Book*> titleToBook;
    std::unordered_map<std::string, std::unordered_set<std::string>> coBorrowed;

public:
    void addBook(Book* book);
    std::vector<Book*> getBooksByGenre(const std::string& genre) const;
    Book* findBookByISBN(const std::string& isbn) const;
    Book* findBookByTitle(const std::string& title) const;
    void updateCoBorrowed(const std::string& book1ISBN, const std::string& book2ISBN);
    std::vector<Book*> getRecommendations(const std::string& bookISBN, int maxRecommendations = 5) const;
};

#endif 