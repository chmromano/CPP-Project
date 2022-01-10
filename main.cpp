#include "main.h"

void print_modes();

void print_functions();

int main() {
    srand(time(nullptr));

    int mode = 0;
    while (mode != 3) {
        print_modes();
        std::ifstream input_file;
        std::ofstream output_file;
        std::cin >> mode;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string file_name;
        std::unique_ptr<Library> library = std::make_unique<Library>();
        if (mode == 1) {
            std::cout << "Enter file to read from:" << std::endl;
            std::getline(std::cin, file_name);
            if (isspace(file_name.back())) file_name.pop_back();
            input_file.open(file_name, std::ifstream::in);
            if (input_file.is_open()) {
                input_file >> *library;
            } else {
                std::cout << "File does not exist." << std::endl;
                mode = 0;
            }
            input_file.close();
        } else if (mode == 2) {
            std::cout << "Enter file to write to:" << std::endl;
            getline(std::cin, file_name);
            if (isspace(file_name.back())) file_name.pop_back();
        } else if (mode != 3 || !std::cin.good()) {
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Invalid choice, try again." << std::endl;
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
                case 3:
                    library->return_book();
                    break;
                case 4:
                    library->add();
                    break;
                case 5:
                    std::cout << "Clearing library records..." << std::endl;
                    library->initialise();
                    break;
                case 6:
                    output_file.open(file_name, std::ofstream::out | std::ofstream::trunc);
                    output_file << *library;
                    output_file.close();
                    break;
                case 7:
                    std::cout << "Exiting library..." << std::endl;
                    break;
                default:
                    if (!std::cin.good()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << "Invalid choice, try again." << std::endl;
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
    std::cout << "5. Initialise library (clear all records)" << std::endl;
    std::cout << "6. Save library to file" << std::endl;
    std::cout << "7. Exit" << std::endl;
}