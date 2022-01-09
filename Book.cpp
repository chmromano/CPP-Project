#include "Book.h"

static unsigned int id_list = 1;


// Constructor ---------------------------------------------------------------------------------------------------------

Book::Book(std::string name_) : name(name_), holder_name(""), return_date("") {
    id = id_list;
    id_list++;
}

// I/O -----------------------------------------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Book &b) {
    std::cout << "BOOK:" << b.name << ";" << b.id << ";" << b.holder_name << ";" << b.return_date << "\n";
    return out;
}

// GET functions -------------------------------------------------------------------------------------------------------

std::string Book::get_name() {
    return name;
}

unsigned int Book::get_id() const {
    return id;
}

std::string Book::get_return_date() {
    return return_date;
}

bool Book::availability() {
    return return_date.empty();
}

void Book::set_holder(std::string holder_) {
    holder_name = holder_;
}

void Book::set_return_date() {
    return_date = "TEST";
}
