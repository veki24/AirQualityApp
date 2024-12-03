#include "data_fetcher.h"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp> // JSON parser library
#include <sstream>
#include <iomanip>

// Alias for JSON parser
using json = nlohmann::json;

// Callback for curl to write data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Fetch data from the API
std::string DataFetcher::fetchData(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}

// Parse JSON response and extract relevant data
std::string DataFetcher::parseData(const std::string& data) {
    try {
        json jsonData = json::parse(data);
        if (jsonData["status"] == "ok") {
            std::string city = jsonData["data"]["city"]["name"];
            int aqi = jsonData["data"]["aqi"];
            double pm25 = jsonData["data"]["iaqi"]["pm25"]["v"];
            double temperature = jsonData["data"]["iaqi"]["t"]["v"];
            std::string date = jsonData["data"]["time"]["s"]; // Date of the data

            // Forecast Data
            std::string forecastData;
            for (const auto& daily : jsonData["data"]["forecast"]["daily"]["pm25"]) {
                forecastData += "Date: " + daily["day"].get<std::string>() + " - PM2.5: " + std::to_string(daily["avg"].get<int>()) + "\n";
            }

            std::ostringstream result;
            result << "City: " << city << "\n"
                   << "AQI: " << aqi << "\n"
                   << "PM2.5: " << pm25 << "\n"
                   << "Temperature: " << temperature << "°C\n"
                   << "Date: " << date << "\n\n"
                   << "Forecast:\n" << forecastData;
            return result.str();
        } else {
            return "Error: " + jsonData["data"].get<std::string>();
        }
    } catch (const json::exception& e) {
        return "Error parsing data: " + std::string(e.what());
    }
}


// Fetch and parse forecast data
std::string DataFetcher::fetchForecastData(const std::string& url) {
    try {
        std::string data = fetchData(url);
        json jsonData = json::parse(data);
        if (jsonData["status"] == "ok") {
            std::ostringstream forecastResult;
            forecastResult << "\nForecast for the next few days:\n";

            for (const auto& day : jsonData["data"]["forecast"]["daily"]["pm25"]) {
                forecastResult << "Date: " << day["day"] << "\n"
                               << "Average PM2.5: " << day["avg"] << " µg/m³\n"
                               << "Max PM2.5: " << day["max"] << " µg/m³\n"
                               << "Min PM2.5: " << day["min"] << " µg/m³\n\n";
            }
            return forecastResult.str();
        } else {
            return "Error: " + jsonData["data"].get<std::string>();
        }
    } catch (const json::exception& e) {
        return "Error fetching forecast data: " + std::string(e.what());
    }
}
