#ifndef C__PROJECT_BOOK_H
#define C__PROJECT_BOOK_H


#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <ctime>

#include "Holder.h"

class Holder;

class Book {
    friend std::ostream &operator<<(std::ostream &out, const Book &b);

    friend std::istream &operator>>(std::istream &in, Book &b);

private:
    std::string name;
    int id;
    std::weak_ptr<Holder> holder;
    std::string return_date;
public:
    Book();

    Book(std::string name_, int id_, std::string return_date_ = "");

    ~Book();

    int get_id() const;

    std::string get_name();

    std::weak_ptr<Holder> get_holder();

    std::string get_return_date();

    void set_holder(const std::shared_ptr<Holder> &h);

    void set_return_date();

    void return_book();

    bool availability();
};


#endif
