#ifndef C__PROJECT_BOOK_H
#define C__PROJECT_BOOK_H


#include <iostream>
#include <string>
#include <memory>

#include "Holder.h"

class Holder;

class Book {
    friend std::ostream &operator<<(std::ostream &out, const Book &b);

    friend std::istream &operator>>(std::istream &in, Book &b);

private:
    std::string name;
    unsigned int id;
    std::weak_ptr<Holder> holder;
    std::string return_date;
public:
    Book();

    std::string get_name();

    unsigned int get_id() const;

    void set_holder(std::shared_ptr<Holder> h);

    std::string get_return_date();

    void set_return_date();

    bool availability();
};


#endif
