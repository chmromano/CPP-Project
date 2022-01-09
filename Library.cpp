#include "Library.h"

Library::Library(std::string name_) : name(name_) {}

void Library::lend_book() {
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

    /*if (book_it == catalogue.end() && holder_it == members.end()) {
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
    }*/
}

void Library::add_book() {
    std::string book_name;
    std::cout << "Enter name of book to add:" << std::endl;
    std::cin >> book_name;

}
