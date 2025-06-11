#include "GenreTree.h"
#include <algorithm>

void GenreTree::addBook(Book* book) {
    genreBooks[book->getGenre()].push_back(book);
    isbnToBook[book->getISBN()] = book;
    titleToBook[book->getTitle()] = book;
}

std::vector<Book*> GenreTree::getBooksByGenre(const std::string& genre) const {
    auto it = genreBooks.find(genre);
    if (it != genreBooks.end()) {
        return it->second;
    }
    return std::vector<Book*>();
}

Book* GenreTree::findBookByISBN(const std::string& isbn) const {
    auto it = isbnToBook.find(isbn);
    return (it != isbnToBook.end()) ? it->second : nullptr;
}

Book* GenreTree::findBookByTitle(const std::string& title) const {
    auto it = titleToBook.find(title);
    return (it != titleToBook.end()) ? it->second : nullptr;
}

void GenreTree::updateCoBorrowed(const std::string& book1ISBN, const std::string& book2ISBN) {
    coBorrowed[book1ISBN].insert(book2ISBN);
    coBorrowed[book2ISBN].insert(book1ISBN);
}

std::vector<Book*> GenreTree::getRecommendations(const std::string& bookISBN, int maxRecommendations) const {
    auto book = findBookByISBN(bookISBN);
    if (!book) {
        return std::vector<Book*>();
    }

    std::vector<Book*> recommendations;
    std::unordered_set<Book*> uniqueRecommendations;

    // Get recommendations based on genre
    auto genreBooks = getBooksByGenre(book->getGenre());
    for (auto* genreBook : genreBooks) {
        if (genreBook->getISBN() != bookISBN && genreBook->getAvailability()) {
            uniqueRecommendations.insert(genreBook);
        }
    }

    // Get recommendations based on co-borrowed books
    auto coBorrowedIt = coBorrowed.find(bookISBN);
    if (coBorrowedIt != coBorrowed.end()) {
        for (const auto& coISBN : coBorrowedIt->second) {
            auto* coBook = findBookByISBN(coISBN);
            if (coBook && coBook->getAvailability()) {
                uniqueRecommendations.insert(coBook);
            }
        }
    }

    // Convert set to vector and limit size
    recommendations.assign(uniqueRecommendations.begin(), uniqueRecommendations.end());
    if (recommendations.size() > maxRecommendations) {
        recommendations.resize(maxRecommendations);
    }

    return recommendations;
} 