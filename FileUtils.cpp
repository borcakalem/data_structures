#include "../include/FileUtils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

Entry* FileUtils::read_file(const std::string& file_path, const int len) {
    std::ifstream file(file_path);
    if (!file.is_open()) return nullptr;
    std::string line;
    Entry* entries = new Entry[len];
    int idx = 0;
    std::getline(file, line); // skip header
    while (std::getline(file, line) && idx < len) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> fields;
        while (std::getline(ss, token, ';')) fields.push_back(token);
        if (fields.size() == 6) {
            entries[idx].name = fields[0];
            entries[idx].address = fields[1];
            entries[idx].city = fields[2];
            entries[idx].postcode = fields[3];
            entries[idx].country = fields[4];
            entries[idx].phone = fields[5];
            idx++;
        }
    }
    file.close();
    return entries;
}

void FileUtils::write_to_file(const Entry* entries, const std::string& file_path, const int len) {
    std::ofstream file(file_path);
    file << "name;address;city;postcode;country;phone\n";
    for (int i = 0; i < len; ++i) {
        file << entries[i].name << ";" << entries[i].address << ";" << entries[i].city << ";" << entries[i].postcode << ";" << entries[i].country << ";" << entries[i].phone << "\n";
    }
    file.close();
}
