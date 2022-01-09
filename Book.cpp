#include "Book.h"


// I/O -----------------------------------------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Book &b) {
    out << "book\n";
    out << b.name << "\n";
    out << b.id << "\n";
    if (b.holder.expired()) {
        out << "nullptr\n";
    } else {
        out << b.holder.lock()->get_name() << "\n";
        out << b.return_date << "\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Book &b) {
    std::string line;
    getline(in, b.name);
    getline(in, line);
    b.id = std::move(std::atoll(line.c_str()));
    getline(in, line);
    if (line == "nullptr") {
        b.return_date = "nullptr";
    } else {
        getline(in, line);
        b.return_date = line;
    }
    return in;
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

void Book::set_return_date() {
    return_date = "TEST";
}

void Book::set_holder(std::shared_ptr<Holder> h) {
    holder = h;
}

Book::Book() {

}
