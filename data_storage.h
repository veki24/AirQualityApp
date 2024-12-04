#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>
#include <pqxx/pqxx> // PostgreSQL library

class DataStorage {
private:
    pqxx::connection connection; // Jedna trajna veza s bazom

public:
    DataStorage(const std::string& connection_str);
    ~DataStorage();

    // Save data to the database
    void saveData(const std::string& city, int aqi, double pm25, double pm10, double temperature, const std::string& timestamp);

    // View stored data from the database
    void viewStoredData();
};

#endif // DATA_STORAGE_H
