#include "Library.h"



/*void Library::lend_book() {
    unsigned int temp_book_id;
    std::cout << "Enter book ID:";
    std::cin >> temp_book_id;

    unsigned int temp_holder_id;
    std::cout << "Enter member ID:";
    std::cin >> temp_holder_id;

    auto book_it = std::find_if(catalogue.begin(), catalogue.end(),
                                [&temp_book_id](Book b) { return b.get_id() == temp_book_id; });

    auto holder_it = std::find_if(members.begin(), members.end(),
                                  [&temp_holder_id](Holder h) { return h.get_id() == temp_holder_id; });

    *//*if (book_it == catalogue.end() && holder_it == members.end()) {
        std::cout << "No book or member found." << std::endl;
    } else if (book_it == catalogue.end()) {
        std::cout << "No book found." << std::endl;
    } else if (holder_it == members.end()) {
        std::cout << "No member found." << std::endl;
    } else {
        if ((*book_it).availability()) {
            (*book_it).set_holder(*holder_it);
        } else {
            std::cout << "The book is not available. Currently lent out to " << (*book_it).get_holder_name() << "." << std::endl;
        }
    }
}*/

void Library::add_book() {
    std::string book_name;
    std::cout << "Enter name of book to add:" << std::endl;
    std::cin >> book_name;

}

void Library::print_all() {
    std::cout << name << std::endl;
    for (auto b: catalogue) {
        std::cout << b;
    }
    for (auto h: members) {
        std::cout << h;
    }
}

std::ostream &operator<<(std::ostream &out, const Library &l) {
    out << "library\n";
    out << l.name << "\n";
    if (!l.catalogue.empty()) {
        for (auto b: l.catalogue) out << b;
    }
    if (!l.members.empty()) {
        for (auto h: l.members) out << h;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Library &l) {
    std::string line;

    getline(in, line);
    if (line == "library") {
        getline(in, l.name);
    } else {
        in.setstate(std::ios::failbit);
        return in;
    }

    while (!in.eof()) {
        getline(in, line);
        if (line == "book") {
            auto temp_book = std::make_shared<Book>();
            in >> *temp_book;
            l.catalogue.push_back(std::move(temp_book));
        } else if (line == "holder") {
            auto temp_holder = std::make_shared<Holder>();
            in >> *temp_holder;

            getline(in, line);
            if (line != "nullptr") {
                std::stringstream ss(line);
                std::string temp_string;
                char delimiter = ',';
                std::vector<unsigned int> temp_vector;
                while (getline(ss, temp_string, delimiter)) {
                    temp_vector.push_back(std::move(atoll(temp_string.c_str())));
                }

                std::for_each(temp_vector.begin(), temp_vector.end(), [&l, &temp_holder](unsigned int &n) {
                    auto it = std::find_if(l.catalogue.begin(), l.catalogue.end(), [&n](Book b){
                        return b.get_id() == n;
                    });
                    temp_holder->add_book(*it);
                    (*it)->set_holder(temp_holder);
                });
            }
            l.members.push_back(std::move(temp_holder));
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    return in;
}

void Library::set_name(std::string n) {
name = n;
}

std::string Library::get_name() {
    return name;
}

Library::Library() {
    name = "";
}
