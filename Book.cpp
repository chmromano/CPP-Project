#include "Book.h"

#include <utility>


// I/O operators -------------------------------------------------------------------------------------------------------

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
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    b.name = line;
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    b.id = std::atoi(line.c_str());
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    if (line == "nullptr") {
        b.return_date = "";
    } else {
        b.return_date = line;
    }
    return in;
}

// GET functions -------------------------------------------------------------------------------------------------------

std::string Book::get_name() {
    return name;
}

int Book::get_id() const {
    return id;
}

std::string Book::get_return_date() {
    return return_date;
}

bool Book::availability() {
    return return_date.empty();
}

std::weak_ptr<Holder> Book::get_holder() {
    return holder;
}

void Book::set_holder(const std::shared_ptr<Holder>& holder_) {
    holder = holder_;
}

Book::Book() = default;

Book::Book(std::string name_, int id_, std::string return_date_) :
        name(std::move(name_)), id(id_), return_date(std::move(return_date_)) {
    holder.reset();
}

void Book::return_book() {
    holder.reset();
    return_date.clear();
}
