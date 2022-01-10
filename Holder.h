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

    Holder(std::string name_);

    ~Holder();

    std::string get_name();

    std::vector<std::weak_ptr<Book>> get_borrowed();

    void borrow_book(std::shared_ptr<Book> &book);

    void return_book(const std::shared_ptr<Book> &book);
};


#endif
