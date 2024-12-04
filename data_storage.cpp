#include "data_storage.h"
#include <iostream>

// Konstruktor za inicijalizaciju trajne veze
DataStorage::DataStorage(const std::string& connection_str) 
    : connection(connection_str) {
    if (connection.is_open()) {
        std::cout << "Connected to database: " << connection.dbname() << std::endl;

        // Pripremi SQL naredbe
        pqxx::work W(connection);
        W.exec("PREPARE insert_city AS INSERT INTO cities(city_name) VALUES($1) ON CONFLICT (city_name) DO NOTHING RETURNING id;");
        W.exec("PREPARE select_city AS SELECT id FROM cities WHERE city_name = $1;");
        W.exec("PREPARE insert_air_quality AS INSERT INTO air_quality(city_id, aqi, pm25, pm10, temperature, timestamp) VALUES($1, $2, $3, $4, $5, $6);");
        W.commit();
    } else {
        throw std::runtime_error("Failed to connect to the database!");
    }
}

// Destruktor za zatvaranje veze
DataStorage::~DataStorage() {
    // Destructor doesn't need to call connection.disconnect()
    // pqxx::connection will handle disconnection automatically
}

// Save data to the database (isti kod kao prije, ali koristi trajnu vezu)
void DataStorage::saveData(const std::string& city, int aqi, double pm25, double pm10, double temperature, const std::string& timestamp) {
    try {
        pqxx::work W(connection);

        // Umetni grad ako ne postoji
        pqxx::result res = W.exec_prepared("insert_city", city);
        int city_id = res.empty() ? -1 : res[0][0].as<int>();

        // Ako grad nije pronađen, dohvatiti njegov ID
        if (city_id == -1) {
            res = W.exec_prepared("select_city", city);
            city_id = res[0][0].as<int>();
        }

        // Umetni podatke o kvaliteti zraka
        W.exec_prepared("insert_air_quality", city_id, aqi, pm25, pm10, temperature, timestamp);

        W.commit();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
