#ifndef DATA_FETCHER_H
#define DATA_FETCHER_H

#include <string>

class DataFetcher {
public:
    // Method to fetch data from the API
    std::string fetchData(const std::string& url);

    // Method to parse fetched data and extract air quality details
    std::string parseData(const std::string& data);

    // Method to fetch forecast data from the API
    std::string fetchForecastData(const std::string& url);
};

#endif // DATA_FETCHER_H
