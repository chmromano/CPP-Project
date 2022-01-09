#include "main.h"

int main() {

    std::ifstream input_file("library.txt", std::ios::in);

    auto library = std::make_unique<Library>();

    input_file >> *library;

    std::cout << *library;

    input_file.close();

    return 0;
}
