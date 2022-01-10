#include "main.h"

void print_modes();

void print_functions();

int main() {
    int mode = 0;
    while (mode != 3) {

        std::ifstream input_file;
        std::ofstream output_file;
        std::string file_name;
        std::unique_ptr<Library> library = std::make_unique<Library>();

        print_modes();
        std::cin >> mode;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (mode == 1) {
            std::cout << "Enter file to read from:" << std::endl;
            std::getline(std::cin, file_name);
            if (file_name.empty()) {
                std::cout << "Error: string is empty." << std::endl;
            } else {
                if (isspace(file_name.back())) file_name.pop_back();
                input_file.open(file_name, std::ifstream::in);
                if (input_file.is_open()) {
                    input_file >> *library;
                } else {
                    std::cout << "File does not exist." << std::endl;
                    mode = 0;
                }
                input_file.close();
            }
        } else if (mode == 2) {
            std::cout << "Enter file to write to:" << std::endl;
            getline(std::cin, file_name);
            if (file_name.empty()) {
                std::cout << "Error: string is empty." << std::endl;
            } else {
                if (isspace(file_name.back())) file_name.pop_back();
            }
        } else if (mode != 3 || !std::cin.good()) {
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Error: invalid choice. Try again." << std::endl;
        }


        while (mode == 1 || mode == 2) {
            print_functions();
            int function = 0;
            std::cin >> function;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (function) {
                case 1:
                    library->report();
                    break;
                case 2:
                    library->lend_book();
                    break;
                case 3:
                    library->return_book();
                    break;
                case 4:
                    library->add_book();
                    break;
                case 5:
                    library->remove_book();
                    break;
                case 6:
                    library->remove_member();
                    break;
                case 7:
                    library->initialise();
                    break;
                case 8:
                    output_file.open(file_name, std::ofstream::out | std::ofstream::trunc);
                    output_file << *library;
                    output_file.close();
                    break;
                case 9:
                    std::cout << "Exiting..." << std::endl;
                    mode = 0;
                    break;
                default:
                    if (!std::cin.good()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << "Error: invalid choice. Try again." << std::endl;
                    break;
            }
        }
    }

    std::cout << "Ending program..." << std::endl;
    return 0;
}

void print_modes() {
    std::cout << "Choose a mode:" << std::endl;
    std::cout << "1. Open existing library" << std::endl;
    std::cout << "2. Create new library" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

void print_functions() {
    std::cout << "Choose a function:" << std::endl;
    std::cout << "1. Print report" << std::endl;
    std::cout << "2. Borrow a book" << std::endl;
    std::cout << "3. Return a book" << std::endl;
    std::cout << "4. Add a new book to library" << std::endl;
    std::cout << "5. Remove book from library" << std::endl;
    std::cout << "6. Remove member from library" << std::endl;
    std::cout << "7. Initialise library (clear all records)" << std::endl;
    std::cout << "8. Save library to file" << std::endl;
    std::cout << "9. Exit" << std::endl;
}