#ifndef C__PROJECT_LIBRARY_H
#define C__PROJECT_LIBRARY_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <iomanip>

#include "Holder.h"
#include "Book.h"


class Holder;

class Book;

class Library {
    friend std::ostream &operator<<(std::ostream &out, const Library &l);

    friend std::istream &operator>>(std::istream &in, Library &l);

private:
    std::vector<std::shared_ptr<Book>> catalogue;
    std::vector<std::shared_ptr<Holder>> members;


public:
    Library();

    ~Library();

    void initialise();

    int generate_id();

    void add();

    void return_book();

    void lend_book();

    void report();


};


#endif
