#include "Holder.h"

std::ostream &operator<<(std::ostream &out, const Holder &h) {
    out << "holder\n";
    out << h.name << "\n";
    if (h.borrowed.empty()) {
        out << "nullptr\n";
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
    line.pop_back();
    h.name = line;
    return in;
}

std::string Holder::get_name() {
    return name;
}

std::vector<std::weak_ptr<Book>> Holder::get_borrowed() {
    return borrowed;
}

void Holder::add_book(const std::shared_ptr<Book> &book) {
    borrowed.push_back(book);
}

Holder::Holder() = default;
