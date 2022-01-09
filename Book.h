#ifndef C__PROJECT_BOOK_H
#define C__PROJECT_BOOK_H


#include <iostream>
#include <string>

#include "Holder.h"

class Book {
    friend std::ostream &operator<<(std::ostream &out, const Book &b);
    friend std::istream &operator>>(std::istream &in, Book &b);
private:
    std::string name;
    unsigned int id;
    std::weak_ptr<Holder> holder;
    std::unique_ptr<std::string> return_date;

    static unsigned int id_list;
public:
    Book(std::string name_);

    std::string get_name();

    unsigned int get_id() const;

    std::string get_return_date();

    void set_return_date();

    bool availability();
};


#endif
