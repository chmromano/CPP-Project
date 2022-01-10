#include "Holder.h"

#include <utility>


// I/O operators -------------------------------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Holder &h) {
    out << "holder\n";
    out << h.name << "\n";
    if (h.borrowed.empty()) {
        out << "null\n";
    } else {
        for (auto it = h.borrowed.begin(); it != h.borrowed.end(); ++it) {
            out << it->lock()->get_id();
            if (it + 1 != h.borrowed.end()) {
                out << ",";
            } else {
                out << "\n";
            }
        }
    }
    return out;
}

std::istream &operator>>(std::istream &in, Holder &h) {
    std::string line;
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    h.name = line;
    return in;
}


// Constructors and destructors ----------------------------------------------------------------------------------------

Holder::Holder() = default;

Holder::Holder(std::string name_) : name(std::move(name_)) {}

Holder::~Holder() = default;


// Other methods -------------------------------------------------------------------------------------------------------

std::string Holder::get_name() {
    return name;
}

std::vector<std::weak_ptr<Book>> Holder::get_borrowed() {
    return borrowed;
}

void Holder::borrow_book(std::shared_ptr<Book> &book) {
    borrowed.push_back(book);
}

void Holder::return_book(const std::shared_ptr<Book> &book) {
    borrowed.erase(std::remove_if(borrowed.begin(), borrowed.end(),
                                  [&book](std::weak_ptr<Book> &b) { return book->get_id() == b.lock()->get_id(); }),
                   borrowed.end());
}
