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
    Holder holder;
    std::string return_date;
public:
    std::string get_name();

    unsigned int get_id();

    Holder get_Holder();

    std::string get_return_date();

    void set_holder(Holder holder_);

    void set_return_date();

    bool availability();

    bool borrow(Holder holder_);
};


#endif //C__PROJECT_BOOK_H
