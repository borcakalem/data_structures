//
// Created by aldin on 28/05/2025.
//

#include "../include/Entry.h"
#include "../include/FileUtils.h"
#include "../include/Operations.h"
#include <iostream>
#include <string>

#define NUM_ENTRIES 1000000
#define UNSORTED_FILE "phonebook_unsorted.csv"
#define SORTED_FILE "phonebook_sorted.csv"

int main() {
    // Read the unsorted phonebook file
    Entry* entries = FileUtils::read_file(UNSORTED_FILE, NUM_ENTRIES);
    if (!entries) {
        std::cout << "Failed to read input file!\n";
        return 1;
    }

    // Sort the entries by name
    Operations::sort(entries, NUM_ENTRIES);

    // Write the sorted entries to a new file
    FileUtils::write_to_file(entries, SORTED_FILE, NUM_ENTRIES);
    std::cout << "Phonebook loaded and sorted.\n";

    // User search loop
    std::string input;
    while (true) {
        std::cout << "Enter name (Surname, Name) to search or -1 to exit: ";
        std::getline(std::cin, input);
        if (input == "-1") {
            break;
        }
        int* result = Operations::search(entries, NUM_ENTRIES, input);
        if (!result) {
            std::cout << "No entries found for '" << input << "'.\n";
        } else {
            int start = result[0];
            int end = result[1];
            int count = end - start + 1;
            std::cout << count << (count == 1 ? " entry" : " entries") << " found:\n";
            for (int i = start; i <= end; ++i) {
                std::cout << "Name: " << entries[i].name << '\n';
                std::cout << "  Address: " << entries[i].address << '\n';
                std::cout << "  City: " << entries[i].city << '\n';
                std::cout << "  Postcode: " << entries[i].postcode << '\n';
                std::cout << "  Country: " << entries[i].country << '\n';
                std::cout << "  Phone: " << entries[i].phone << '\n';
                std::cout << "---\n";
            }
            delete[] result;
        }
    }
    delete[] entries;
    std::cout << "Goodbye!\n";
    return 0;
}
