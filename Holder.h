#ifndef C__PROJECT_HOLDER_H
#define C__PROJECT_HOLDER_H


#include <iostream>
#include <string>
#include <vector>

#include "Book.h"

class Book;

class Holder {
    friend std::ostream &operator<<(std::ostream &out, const Holder &h);
    friend std::istream &operator>>(std::istream &in, Holder &h);
private:
    std::string name;
    std::vector<std::weak_ptr<Book>> borrowed;
public:
    std::string get_name();
};


#endif
