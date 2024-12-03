#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>

class DataStorage {
public:
    // Save data to a file
    void saveData(const std::string& data);

    // View stored data from the file
    void viewStoredData();
};

#endif // DATA_STORAGE_H
