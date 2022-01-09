#ifndef C__PROJECT_HOLDER_H
#define C__PROJECT_HOLDER_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Book.h"

class Book;

class Holder {
    friend std::ostream &operator<<(std::ostream &out, const Holder &h);

    friend std::istream &operator>>(std::istream &in, Holder &h);

private:
    std::string name;
    std::vector<std::weak_ptr<Book>> borrowed;
public:
    Holder();

    std::string get_name();

    void add_book(const std::shared_ptr<Book> &book) {
        borrowed.push_back(book);
    }

    std::vector<std::weak_ptr<Book>> get_borrowed();
};


#endif
