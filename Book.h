#ifndef C__PROJECT_BOOK_H
#define C__PROJECT_BOOK_H


#include <iostream>
#include <string>

#include "Holder.h"

class Book {
    friend std::istream &operator>>(std::istream &in, Book &book);

private:
    std::string name;
    unsigned int id;
    std::string holder_name;
    std::string return_date;

    static unsigned int id_list;
public:
    Book(std::string name_);

    std::string get_name();

    unsigned int get_id();

    std::string get_return_date();

    void set_holder(std::string holder_);

    void set_return_date();

    bool availability();
};


#endif //C__PROJECT_BOOK_H
