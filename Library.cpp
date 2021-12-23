#include "Library.h"

void Library::lend_book() {
    unsigned int temp_book_id;
    std::cout << "Enter book ID:";
    std::cin >> temp_book_id;
    auto book_it = std::find_if(catalogue.begin(), catalogue.end(),
                                [&temp_book_id](Book b) { return b.get_id() == temp_book_id; });

    unsigned int temp_holder_id;
    std::cout << "Enter member ID:";
    std::cin >> temp_holder_id;
    auto holder_it = std::find_if(members.begin(), members.end(),
                                  [&temp_holder_id](Holder h) { return h.get_id() == temp_holder_id; });
}