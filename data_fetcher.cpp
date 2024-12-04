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
std::tuple<std::string, int, double, double, double, std::string> DataFetcher::parseData(const std::string& data) {
    try {
        json jsonData = json::parse(data);
        if (jsonData["status"] == "ok") {
            std::string city = jsonData["data"]["city"]["name"];
            int aqi = jsonData["data"]["aqi"];
            double pm25 = jsonData["data"]["iaqi"]["pm25"]["v"];
            double pm10 = jsonData["data"]["iaqi"]["pm10"]["v"];
            double temperature = jsonData["data"]["iaqi"]["t"]["v"];
            std::string timestamp = jsonData["data"]["time"]["s"]; // Timestamp of the data

            return std::make_tuple(city, aqi, pm25, pm10, temperature, timestamp); // Return as a tuple
        } else {
            throw std::runtime_error("Error fetching data: " + jsonData["data"].get<std::string>());
        }
    } catch (const json::exception& e) {
        throw std::runtime_error("Error parsing data: " + std::string(e.what()));
    }
}

