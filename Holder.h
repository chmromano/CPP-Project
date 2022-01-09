#ifndef C__PROJECT_HOLDER_H
#define C__PROJECT_HOLDER_H


#include <string>
#include <vector>

class Book;

class Holder {
private:
    std::string name;
    unsigned int id;
    std::vector<Book> borrowed;
public:
    std::string get_name();

    unsigned int get_id();
};


#endif //C__PROJECT_HOLDER_H
