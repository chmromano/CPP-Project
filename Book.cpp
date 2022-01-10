#include "Book.h"

#include <utility>


// I/O operators -------------------------------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Book &b) {
    out << "book\n";
    out << b.name << "\n";
    out << b.id << "\n";
    if (b.holder.expired()) {
        out << "null\n";
    } else {
        out << b.return_date << "\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Book &b) {
    std::string line;
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    b.name = std::move(line);
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    b.id = std::atoi(line.c_str());
    getline(in, line);
    if (isspace(line.back())) line.pop_back();
    if (line == "null") {
        b.return_date = "";
    } else {
        b.return_date = line;
    }
    return in;
}


// Constructors and destructors ----------------------------------------------------------------------------------------

Book::Book() = default;

Book::Book(std::string name_, int id_, std::string return_date_) :
        name(std::move(name_)), id(id_), return_date(std::move(return_date_)) {
    holder.reset();
}

Book::~Book() = default;


// Other methods -------------------------------------------------------------------------------------------------------

int Book::get_id() const {
    return id;
}

std::string Book::get_name() {
    return name;
}

std::weak_ptr<Holder> Book::get_holder() {
    return holder;
}

std::string Book::get_return_date() {
    return return_date;
}

void Book::set_holder(const std::shared_ptr<Holder> &holder_) {
    holder = holder_;
}

// Automatically set return date two weeks from now.
void Book::set_return_date() {
    // Duration of two weeks.
    std::chrono::duration<int, std::ratio<60 * 60 * 24 * 14>> two_weeks(1);

    std::chrono::system_clock::time_point return_tt = std::chrono::system_clock::now() + two_weeks;
    time_t tt = std::chrono::system_clock::to_time_t(return_tt);
    std::string temp = ctime(&tt);
    if (isspace(temp.back())) temp.pop_back();

    return_date = std::move(temp);
}

void Book::return_book() {
    holder.reset();
    return_date.clear();
}

bool Book::availability() {
    return return_date.empty();
}
