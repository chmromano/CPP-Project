#ifndef C__PROJECT_LIBRARY_H
#define C__PROJECT_LIBRARY_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

#include "Holder.h"
#include "Book.h"

class Holder;
class Book;

class Library {
    friend std::ostream &operator<<(std::ostream &out, const Library &l);

    friend std::istream &operator>>(std::istream &in, Library &l);

private:
    std::string name;
    std::vector<std::shared_ptr<Book>> catalogue;
    std::vector<std::shared_ptr<Holder>> members;
public:
    Library();

    void set_name(std::string n);

    std::string get_name();

    void add_book();

    void lend_book();

    void print_all();
};


#endif
