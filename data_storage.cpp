#include "data_storage.h"
#include <fstream>
#include <iostream>

// Save data to a file
void DataStorage::saveData(const std::string& data) {
    std::ofstream file("air_quality_data.json", std::ios::app);
    if (file.is_open()) {
        file << data << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for saving data." << std::endl;
    }
}

// View data stored in the file
void DataStorage::viewStoredData() {
    std::ifstream file("air_quality_data.json");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "No stored data found." << std::endl;
    }
}
