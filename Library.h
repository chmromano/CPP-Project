#ifndef C__PROJECT_LIBRARY_H
#define C__PROJECT_LIBRARY_H


#include <string>
#include <vector>
#include <iostream>

#include "Holder.h"
#include "Book.h"

class Library {
private:
    std::string name;
    std::vector<Book> catalogue;
    std::vector<std::string> members;
public:
    Library(std::string name_);

    void add_book();

    void lend_book();
};


#endif
