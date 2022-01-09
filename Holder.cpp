#include "Holder.h"

std::ostream &operator<<(std::ostream &out, const Holder &h) {
    out << "HOLDER:" << h.name << ";";
    for (auto it = h.borrowed.begin(); it != h.borrowed.end(); ++it) {
        out << it->lock()->get_id();
        if (it + 1 != h.borrowed.end()) {
            out << ",";
        } else {
            out << "\n";
        }
    }
    return out;
}

std::istream &operator>>(std::istream &in, Holder &h) {
    return in;
}

std::string Holder::get_name() {
    return name;
}
