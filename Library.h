#ifndef C__PROJECT_LIBRARY_H
#define C__PROJECT_LIBRARY_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Holder.h"
#include "Book.h"

class Library {
    friend std::ostream &operator<<(std::ostream &out, const Library &l);
    friend std::istream &operator>>(std::istream &in, Library &l);
private:
    std::string name;
    std::vector<std::shared_ptr<Book>> catalogue;
    std::vector<std::shared_ptr<std::string>> members;
public:
    Library(std::string name_);

    void add_book();

    void lend_book();
};


#endif
