#include "Book.h"

// GET functions -------------------------------------------------------------------------------------------------------

std::string Book::get_name() {
    return name;
}

unsigned int Book::get_id() {
    return id;
}

Holder Book::get_Holder() {
    return holder;
}

std::string Book::get_return_date() {
    return return_date;
}

bool Book::availability() {
    return return_date.empty();
}

void Book::set_holder(Holder holder_) {
    holder = holder_;
}

void Book::set_return_date() {
    return_date = "TEST";
}