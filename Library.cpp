// Christopher Romano

#include "Library.h"

#include <utility>


// I/O operators -------------------------------------------------------------------------------------------------------

// Library output operator.
std::ostream &operator<<(std::ostream &out, const Library &l) {
    if (!l.catalogue.empty()) {
        for (const auto &b: l.catalogue) out << *b;
    }
    if (!l.members.empty()) {
        for (const auto &h: l.members) out << *h;
    }
    return out;
}

// Library input operator.
std::istream &operator>>(std::istream &in, Library &l) {
    while (!in.eof()) {
        std::string line;
        getline(in, line);
        if (line.empty()) break;
        if (isspace(line.back())) line.pop_back();
        if (line == "book") {
            // Read book object.
            auto temp_book = std::make_shared<Book>();
            in >> *temp_book;
            l.catalogue.push_back(std::move(temp_book));
        } else if (line == "holder") {
            // Read holder object.
            auto temp_holder = std::make_shared<Holder>();
            in >> *temp_holder;
            getline(in, line);
            if (isspace(line.back())) line.pop_back();
            // If null member has no books borrowed.
            if (line != "null") {
                std::stringstream ss(line);
                std::string temp_string;
                char delimiter = ',';
                std::vector<int> temp_vector;

                // Parse borrowed book IDs.
                while (getline(ss, temp_string, delimiter)) {
                    temp_vector.push_back(atoi(temp_string.c_str()));
                }

                // Find the borrowed books in the catalogue, assign them to the member, and assign the member to the books.
                std::for_each(temp_vector.begin(), temp_vector.end(), [&l, &temp_holder](int &n) {
                    auto it = std::find_if(l.catalogue.begin(), l.catalogue.end(),
                                           [&n](const std::shared_ptr<Book> &b) {
                                               return b->get_id() == n;
                                           });
                    temp_holder->borrow_book(*it);
                    (*it)->set_holder(temp_holder);
                });

                // Add the member to the member list.
                l.members.push_back(std::move(temp_holder));
            }
        } else {
            // Handle errors.
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    return in;
}


// Constructors and destructors ----------------------------------------------------------------------------------------

Library::Library() = default;

Library::~Library() = default;


// Private methods -----------------------------------------------------------------------------------------------------

// Find book by ID.
auto Library::find_book(int id_) {
    return std::find_if(catalogue.begin(), catalogue.end(),
                        [&id_](const std::shared_ptr<Book> &book) {
                            return book->get_id() == id_;
                        });
}

// Find member by name.
auto Library::find_member(std::string name_) {
    return std::find_if(members.begin(), members.end(),
                        [&name_](const std::shared_ptr<Holder> &holder) {
                            return holder->get_name() == name_;
                        });
}

// Generate an ID for a book (first available starting from 1).
int Library::generate_id() {
    int number = 0;
    do {
        number++;
    } while (find_if(catalogue.begin(), catalogue.end(), [&number](std::shared_ptr<Book> &book) {
        return book->get_id() == number;
    }) != catalogue.end());
    return number;
}


// Misc methods --------------------------------------------------------------------------------------------------------

// Clear library records.
void Library::initialise() {
    catalogue.clear();
    members.clear();
    std::cout << std::endl << "Library records cleared. Press enter to continue.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Print formatted library report.
void Library::report() {
    // Title strings.
    std::string book_id_string("ID");
    std::string book_name_string("Book");
    std::string holder_name_string("Holder");
    std::string return_date_string("Return Date");

    // Initial widths.
    int longest_book_name = static_cast<int>(book_name_string.size());
    int longest_book_id = static_cast<int>(book_id_string.size());
    int longest_holder_name = static_cast<int>(holder_name_string.size());
    int longest_return_date = static_cast<int>(return_date_string.size());

    // Sort the catalogue by book ID before printing.
    std::sort(catalogue.begin(), catalogue.end(),
              [](const std::shared_ptr<Book> &book_1, const std::shared_ptr<Book> &book_2) {
                  return book_1->get_id() < book_2->get_id();
              });

    // Find how much printing width is required.
    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_return_date, &longest_book_id](
                          const std::shared_ptr<Book> &book) {

                      // Find number of ID digits.
                      int temp_book_id = book->get_id();
                      int digits = 0;
                      do {
                          temp_book_id /= 10;
                          digits++;
                      } while (temp_book_id != 0);
                      if (digits > longest_book_id) longest_book_id = digits;

                      // Find the longest book name.
                      if (book->get_name().size() > longest_book_name)
                          longest_book_name = static_cast<int>(book->get_name().size());

                      // If available find the longest holder name and return date.
                      if (!book->availability()) {
                          if (book->get_holder().lock()->get_name().size() > longest_holder_name)
                              longest_holder_name = static_cast<int>(book->get_holder().lock()->get_name().size());
                          if (book->get_return_date().size() > longest_return_date)
                              longest_return_date = static_cast<int>(book->get_return_date().size());
                      }
                  });

    // Print title row.
    std::cout << std::endl;
    std::cout << std::setw(longest_book_id) << std::left << book_id_string << " | ";
    std::cout << std::setw(longest_book_name) << std::left << book_name_string << " | ";
    std::cout << std::setw(longest_holder_name) << std::left << holder_name_string << " | ";
    std::cout << std::setw(longest_return_date) << std::left << return_date_string << std::endl;

    // Print the unavailable books.
    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_return_date, &longest_book_id](
                          const std::shared_ptr<Book> &book) {
                      if (!book->availability()) {
                          std::cout << std::setw(longest_book_id) << std::right << book->get_id() << " | ";
                          std::cout << std::setw(longest_book_name) << std::right << book->get_name() << " | ";
                          std::cout << std::setw(longest_holder_name) << std::right
                                    << book->get_holder().lock()->get_name() << " | ";
                          std::cout << std::setw(longest_return_date) << std::right << book->get_return_date()
                                    << std::endl;
                      }
                  });

    // Print the available books.
    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_book_id, &longest_return_date](
                          const std::shared_ptr<Book> &book) {
                      if (book->availability()) {
                          std::cout << std::setw(longest_book_id) << std::right << book->get_id() << " | ";
                          std::cout << std::setw(longest_book_name) << std::right << book->get_name() << " | ";
                          std::cout << std::setw(longest_holder_name) << std::right << "N/A" << " | ";
                          std::cout << std::setw(longest_return_date) << std::right << "N/A" << std::endl;
                      }
                  });

    std::cout << std::endl << "Press enter to continue.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Add a book to the library.
void Library::add_book() {
    std::string book_name;
    std::cout << std::endl << "Enter the name of the book to add:" << std::endl;
    getline(std::cin, book_name);
    if (book_name.empty()) {
        std::cout << std::endl << "Error: string is empty. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        if (isspace(book_name.back())) book_name.pop_back();
        // Generate and ID and add the book to the catalogue.
        int id = generate_id();
        catalogue.push_back(std::move(std::make_shared<Book>(book_name, id)));
        std::cout << "Book successfully added. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Remove a book from the library.
void Library::remove_book() {
    int temp_book_id;
    std::cout << std::endl << "Enter book ID to remove:" << std::endl;
    std::cin >> temp_book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl << "Error: invalid ID. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        // Find the book with the ID and remove it from the catalogue.
        auto book_it = find_book(temp_book_id);
        if (book_it == catalogue.end()) {
            std::cout << "No book found. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if ((*book_it)->get_holder().lock() != nullptr) (*book_it)->get_holder().lock()->return_book(*book_it);
            catalogue.erase(book_it);
            std::cout << "Book successfully removed. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Lend a book.
void Library::lend_book() {
    int temp_book_id;
    std::cout << std::endl << "Enter book ID:";
    std::cin >> temp_book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl << "Error: invalid ID. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        std::string temp_holder_name;
        std::cout << "Enter member name:" << std::endl;
        getline(std::cin, temp_holder_name);
        if (temp_holder_name.empty()) {
            std::cout << std::endl << "Error: string is empty. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (isspace(temp_holder_name.back())) temp_holder_name.pop_back();

            // Find the book from the catalogue.
            auto book_it = find_book(temp_book_id);

            // Find the member from the member list.
            auto holder_it = find_member(temp_holder_name);

            if (book_it == catalogue.end() && holder_it == members.end()) {
                std::cout << "No book or member found. Press enter to continue.";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (book_it == catalogue.end()) {
                std::cout << "No book found. Press enter to continue.";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                // If a member is not found add the member to the member list.
                if (holder_it == members.end()) {
                    members.push_back(std::make_shared<Holder>(temp_holder_name));
                    holder_it = std::prev(members.end());
                    std::cout << temp_holder_name << " added to members." << std::endl;
                }

                // If the book is available lend it out.
                if ((*book_it)->availability()) {
                    (*book_it)->set_holder(*holder_it);
                    (*book_it)->set_return_date();
                    (*holder_it)->borrow_book(*book_it);
                    std::cout << "Book successfully lent out to: " << (*holder_it)->get_name()
                              << ". Press enter to continue.";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    std::cout << "The book is not available. Currently lent out to "
                              << (*book_it)->get_holder().lock()->get_name()
                              << ". Press enter to continue.";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    }
}

// Return a book to the library.
void Library::return_book() {
    int temp_book_id = 0;
    std::cout << std::endl << "Enter ID:" << std::endl;
    std::cin >> temp_book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: invalid input. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        auto book_it = find_book(temp_book_id);
        if (book_it == catalogue.end()) {
            std::cout << "Book not found. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((*book_it)->availability()) {
            std::cout << "This book had already been returned. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            (*book_it)->get_holder().lock()->return_book(*book_it);
            (*book_it)->return_book();
            std::cout << "Book successfully returned. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Remove a member from the library (returns all borrowed books).
void Library::remove_member() {
    if (members.empty()) {
        std::cout << std::endl << "Member list empty. Press enter to continue.";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        std::cout << std::endl << "Members:" << std::endl;
        for (const auto &m: members) {
            std::cout << m->get_name() << std::endl;
        }
        std::cout << std::endl;

        std::string member_name;
        std::cout << "Enter name of the member to remove:" << std::endl;
        getline(std::cin, member_name);
        if (member_name.empty()) {
            std::cout << "Error: string is empty. Press enter to continue.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (isspace(member_name.back())) member_name.pop_back();

            auto holder_it = find_member(member_name);

            if (holder_it == members.end()) {
                std::cout << "No member found. Press enter to continue.";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                auto temp = (*holder_it)->get_borrowed();
                if (!temp.empty()) {
                    for (const auto &b: temp) {
                        b.lock()->return_book();
                    }
                }
                members.erase(holder_it);
                std::cout << "Member successfully removed. Press enter to continue.";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}
