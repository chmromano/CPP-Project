#include "Holder.h"

std::ostream &operator<<(std::ostream &out, const Holder &h) {
    std::cout << "HOLDER:" << h.name << ";";
    for (auto it = h.borrowed.begin(); it != h.borrowed.end(); ++it) {
        std::cout << it->get_id();
        if (it + 1 != h.borrowed.end()) {
            std::cout << ",";
        } else {
            std::cout << "\n";
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
