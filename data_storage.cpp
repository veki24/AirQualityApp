#include "data_storage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // For std::replace

// Constructor: Initialize persistent database connection
DataStorage::DataStorage(const std::string& connection_str) 
    : connection(connection_str) {
    if (connection.is_open()) {
        std::cout << "Connected to database: " << connection.dbname() << std::endl;

        // Prepare SQL statements
        pqxx::work W(connection);
        W.exec("PREPARE insert_city AS INSERT INTO cities(city_name) VALUES($1) ON CONFLICT (city_name) DO NOTHING RETURNING id;");
        W.exec("PREPARE select_city AS SELECT id FROM cities WHERE city_name = $1;");
        W.exec("PREPARE insert_air_quality AS INSERT INTO air_quality(city_id, aqi, pm25, pm10, temperature, timestamp) VALUES($1, $2, $3, $4, $5, $6);");
        W.commit();
    } else {
        throw std::runtime_error("Failed to connect to the database!");
    }
}

// Destructor: Connection cleanup
DataStorage::~DataStorage() {
    // pqxx::connection handles disconnection automatically
}

// Save air quality data to the database
void DataStorage::saveData(const std::string& city, int aqi, double pm25, double pm10, double temperature, const std::string& timestamp) {
    try {
        pqxx::work W(connection);

        // Insert city if it doesn't exist
        pqxx::result res = W.exec_prepared("insert_city", city);
        int city_id = res.empty() ? -1 : res[0][0].as<int>();

        // Retrieve city ID if it wasn't inserted
        if (city_id == -1) {
            res = W.exec_prepared("select_city", city);
            city_id = res[0][0].as<int>();
        }

        // Insert air quality data
        W.exec_prepared("insert_air_quality", city_id, aqi, pm25, pm10, temperature, timestamp);

        W.commit();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DataStorage::importCSV(const std::string& filePath) {
    // Hardcoded city name for this dataset
    std::string city = "Zagreb-3, Croatia";
    std::cout << "Processing data for city: " << city << std::endl;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        if (isHeader) {
            isHeader = false; // Skip the header row
            continue;
        }

        std::cout << "Processing line: " << line << std::endl;

        std::istringstream iss(line);
        std::vector<std::string> row;
        std::string value;

        while (std::getline(iss, value, ',')) {
            row.push_back(value);
        }

        // Ensure the row has at least the date column
        if (row.size() < 1 || row[0].empty()) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        try {
            // Process data
            std::string timestamp = row[0];

            double pm25 = (row.size() > 1 && !row[1].empty()) ? std::stod(row[1]) : NAN;
            double pm10 = (row.size() > 2 && !row[2].empty()) ? std::stod(row[2]) : NAN;
            double temperature = (row.size() > 3 && !row[3].empty()) ? std::stod(row[3]) : NAN;

            // Calculate AQI based on pm25 or pm10
            int aqi = NAN;
            if (!std::isnan(pm25) && !std::isnan(pm10)) {
                aqi = static_cast<int>(std::max(pm25, pm10));
            } else if (!std::isnan(pm25)) {
                aqi = static_cast<int>(pm25);
            } else if (!std::isnan(pm10)) {
                aqi = static_cast<int>(pm10);
            }

            // Save the processed data
            saveData(city, aqi, pm25, pm10, temperature, timestamp);
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << std::endl;
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    file.close();
}



