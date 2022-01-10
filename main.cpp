// Christopher Romano

#include "main.h"

void print_modes();

void print_functions();

int main() {
    int mode = 0;
    // Mode 3: quit program.
    while (mode != 3) {
        // Declaring needed objects.
        std::ifstream input_file;
        std::ofstream output_file;
        std::string file_name;
        std::unique_ptr<Library> library = std::make_unique<Library>();

        // Display modes and let user choose.
        print_modes();
        std::cin >> mode;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (mode == 1) {
            // Mode 1: open existing file and read library object.
            std::cout << std::endl << "Enter file to read from:" << std::endl;
            std::getline(std::cin, file_name);
            if (file_name.empty()) {
                std::cout << std::endl << "Error: string is empty. Press enter to continue.";
                getchar();
                mode = 0;
            } else {
                if (isspace(file_name.back())) file_name.pop_back();
                input_file.open(file_name, std::ifstream::in);
                if (input_file.is_open()) {
                    input_file >> *library;
                } else {
                    std::cout << std::endl << "Error: file does not exist. Press enter to continue.";
                    getchar();
                    mode = 0;
                }
                input_file.close();
            }
        } else if (mode == 2) {
            // Mode 2: get file name and use an empty library.
            std::cout << std::endl << "Enter file to write to:" << std::endl;
            getline(std::cin, file_name);
            if (file_name.empty()) {
                std::cout << std::endl << "Error: string is empty. Press enter to continue.";
                getchar();
                mode = 0;
            } else {
                if (isspace(file_name.back())) file_name.pop_back();
            }
        } else if (mode != 3 || !std::cin.good()) {
            // Handle input errors.
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << std::endl << "Error: invalid choice. Press enter to continue.";
            getchar();
        }

        // Enter library functions.
        while (mode == 1 || mode == 2) {
            // Display functions and let user choose.
            print_functions();
            int function = 0;
            std::cin >> function;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (function) {
                case 1:
                    // Print report.
                    library->report();
                    break;
                case 2:
                    // Lend a book.
                    library->lend_book();
                    break;
                case 3:
                    // Return a book.
                    library->return_book();
                    break;
                case 4:
                    // Add a new book to the library.
                    library->add_book();
                    break;
                case 5:
                    // Remove a book from the library.
                    library->remove_book();
                    break;
                case 6:
                    // Remove a member from the library.
                    library->remove_member();
                    break;
                case 7:
                    // Clear all library records.
                    library->initialise();
                    break;
                case 8:
                    // Save library to file.
                    output_file.open(file_name, std::ofstream::out | std::ofstream::trunc);
                    output_file << *library;
                    output_file.close();
                    break;
                case 9:
                    // Exit function mode and return to main menu.
                    std::cout << std::endl << "Exiting..." << std::endl;
                    mode = 0;
                    break;
                default:
                    // Handle input errors.
                    if (!std::cin.good()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << std::endl << "Error: invalid choice. Press enter to continue.";
                    getchar();
                    break;
            }
        }
    }

    std::cout << std::endl << "Ending program..." << std::endl;
    return 0;
}

// Print user modes.
void print_modes() {
    std::cout << std::endl;
    std::cout << "Choose a mode:" << std::endl;
    std::cout << "1. Open existing library" << std::endl;
    std::cout << "2. Create new library" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

// Print library functions.
void print_functions() {
    std::cout << std::endl;
    std::cout << "Choose a function:" << std::endl;
    std::cout << "1. Print library report" << std::endl;
    std::cout << "2. Lend a book" << std::endl;
    std::cout << "3. Return a book" << std::endl;
    std::cout << "4. Add a new book to library" << std::endl;
    std::cout << "5. Remove a book from library" << std::endl;
    std::cout << "6. Remove a member from library" << std::endl;
    std::cout << "7. Clear library records" << std::endl;
    std::cout << "8. Save library to file" << std::endl;
    std::cout << "9. Exit" << std::endl;
}
