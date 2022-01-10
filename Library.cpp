#include "Library.h"

#include <utility>


// I/O operators -------------------------------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Library &l) {
    if (!l.catalogue.empty()) {
        for (const auto &b: l.catalogue) out << *b;
    }
    if (!l.members.empty()) {
        for (const auto &h: l.members) out << *h;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Library &l) {
    while (!in.eof()) {
        std::string line;
        getline(in, line);
        if (line.empty()) break;
        if (isspace(line.back())) line.pop_back();
        if (line == "book") {
            auto temp_book = std::make_shared<Book>();
            in >> *temp_book;
            l.catalogue.push_back(std::move(temp_book));
        } else if (line == "holder") {
            auto temp_holder = std::make_shared<Holder>();
            in >> *temp_holder;

            getline(in, line);
            if (isspace(line.back())) line.pop_back();
            if (line != "nullptr") {
                std::stringstream ss(line);
                std::string temp_string;
                char delimiter = ',';
                std::vector<int> temp_vector;
                while (getline(ss, temp_string, delimiter)) {
                    temp_vector.push_back(atoi(temp_string.c_str()));
                }
                std::for_each(temp_vector.begin(), temp_vector.end(), [&l, &temp_holder](int &n) {
                    auto it = std::find_if(l.catalogue.begin(), l.catalogue.end(),
                                           [&n](const std::shared_ptr<Book> &b) {
                                               return b->get_id() == n;
                                           });
                    temp_holder->add_book(*it);
                    (*it)->set_holder(temp_holder);
                });
                l.members.push_back(std::move(temp_holder));
            }
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    return in;
}


// Constructors and destructors ----------------------------------------------------------------------------------------
Library::Library() = default;

Library::~Library() = default;


void Library::lend_book() {
    int temp_book_id;
    std::cout << "Enter book ID:";
    std::cin >> temp_book_id;

    std::string temp_holder_name;
    std::cout << "Enter member name:";
    std::cin >> temp_holder_name;

    auto book_it = std::find_if(catalogue.begin(), catalogue.end(),
                                [&temp_book_id](const std::shared_ptr<Book> &book) {
                                    return book->get_id() == temp_book_id;
                                });

    auto holder_it = std::find_if(members.begin(), members.end(),
                                  [&temp_holder_name](const std::shared_ptr<Holder> &holder) {
                                      return holder->get_name() == temp_holder_name;
                                  });

    if (book_it == catalogue.end() && holder_it == members.end()) {
        std::cout << "No book or member found." << std::endl;
    } else if (book_it == catalogue.end()) {
        std::cout << "No book found." <<
                  std::endl;
    } else {
        if (holder_it == members.end()) {
            members.push_back(std::make_shared<Holder>(temp_holder_name));
            holder_it = std::prev(members.end());
        }

        if ((*book_it)->availability()) {
            (*book_it)->set_holder(*holder_it);
        } else {
            std::cout << "The book is not available. Currently lent out to " << (*book_it)->get_holder().lock()->get_name() << "."
                      << std::endl;
        }
    }
}


void Library::add() {
    std::string book_name;
    std::cout << "Enter name of book to add:" << std::endl;
    getline(std::cin, book_name);
    int id = generate_id();
    catalogue.push_back(std::move(std::make_shared<Book>(book_name, id)));
}

int Library::generate_id() {
    int number;
    do {
        number = rand() % 1000000 + 1;
    } while (find_if(catalogue.begin(), catalogue.end(), [&number](std::shared_ptr<Book> &book) {
        return book->get_id() == number;
    }) != catalogue.end());
    return number;
}

void Library::initialise() {
    catalogue.clear();
    members.clear();
}

void Library::report() {
    int longest_book_name = 0;
    int longest_book_id = 0;
    int longest_holder_name = 0;
    int longest_return_date = 0;

    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_return_date, &longest_book_id](
                          const std::shared_ptr<Book> &book) {
                      if (book->get_name().size() > longest_book_name) longest_book_name = book->get_name().size();
                      int temp = book->get_id();
                      int digits = 0;
                      do {
                          temp /= 10;
                          digits++;
                      } while (temp != 0);
                      if (digits > longest_book_id) longest_book_id = digits;
                      if (!book->availability()) {
                          if (book->get_holder().lock()->get_name().size() > longest_holder_name)
                              longest_holder_name = book->get_holder().lock()->get_name().size();
                          if (book->get_return_date().size() > longest_return_date)
                              longest_return_date = book->get_return_date().size();
                      }
                  });

    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_return_date, &longest_book_id](
                          const std::shared_ptr<Book> &book) {
                      if (!book->availability()) {
                          std::cout << std::setw(longest_book_id) << book->get_id() << " | ";
                          std::cout << std::setw(longest_book_name) << book->get_name() << " | ";
                          std::cout << std::setw(longest_holder_name) << book->get_holder().lock()->get_name() << " | ";
                          std::cout << std::setw(longest_return_date) << book->get_return_date() << std::endl;
                      }
                  });

    std::for_each(catalogue.begin(), catalogue.end(),
                  [&longest_book_name, &longest_holder_name, &longest_book_id, &longest_return_date](
                          const std::shared_ptr<Book> &book) {
                      if (book->availability()) {
                          std::cout << std::setw(longest_book_id) << book->get_id() << " | ";
                          std::cout << std::setw(longest_book_name) << book->get_name() << " | ";
                          std::cout << std::setw(longest_holder_name) << "N/A" << " | ";
                          std::cout << std::setw(longest_return_date) << "Available" << std::endl;
                      }
                  });
}

void Library::return_book() {
    int temp_book_id = 0;
    std::cout << "Enter ID:" << std::endl;
    std::cin >> temp_book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
    } else {
        auto book_it = std::find_if(catalogue.begin(), catalogue.end(),
                                    [&temp_book_id](const std::shared_ptr<Book> &book) {
                                        return book->get_id() == temp_book_id;
                                    });
        if (book_it == catalogue.end()){
            std::cout << "Book not found." << std::endl;
        } else if ((*book_it)->availability()){
            std::cout << "This book is already available." << std::endl;
        } else {(*book_it)->get_holder().lock()->return_book(*book_it);
            (*book_it)->return_book();

        }
    }
}
