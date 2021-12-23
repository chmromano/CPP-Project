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
    std::vector<Holder> members;
    std::vector<Book> catalogue;
public:
    void lend_book();
};


#endif //C__PROJECT_LIBRARY_H
