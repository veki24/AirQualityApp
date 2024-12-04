#include <iostream>
#include "data_fetcher.h"
#include "data_storage.h"

int main() {
    // URLs for all three Zagreb locations
    const std::string urlZagreb1 = "https://api.waqi.info/feed/zagreb/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279";
    const std::string urlZagreb2 = "https://api.waqi.info/feed/@5161/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279";
    const std::string urlZagreb3 = "https://api.waqi.info/feed/@5152/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279";

    const std::string connection_str = "dbname=air_quality_database user=postgres password=bazepodataka host=localhost port=5432";

    DataFetcher fetcher;
    DataStorage storage(connection_str); // Jedna trajna veza

    // Fetch and store air quality data for Zagreb-1
    std::cout << "Fetching data for Zagreb-1:" << std::endl;
    std::string dataZagreb1 = fetcher.fetchData(urlZagreb1);
    auto [city1, aqi1, pm251, pm101, temperature1, timestamp1] = fetcher.parseData(dataZagreb1);
    storage.saveData(city1, aqi1, pm251, pm101, temperature1, timestamp1);

    // Fetch and store air quality data for Zagreb-2
    std::cout << "Fetching data for Zagreb-2:" << std::endl;
    std::string dataZagreb2 = fetcher.fetchData(urlZagreb2);
    auto [city2, aqi2, pm252, pm102, temperature2, timestamp2] = fetcher.parseData(dataZagreb2);
    storage.saveData(city2, aqi2, pm252, pm102, temperature2, timestamp2);

    // Fetch and store air quality data for Zagreb-3
    std::cout << "Fetching data for Zagreb-3:" << std::endl;
    std::string dataZagreb3 = fetcher.fetchData(urlZagreb3);
    auto [city3, aqi3, pm253, pm103, temperature3, timestamp3] = fetcher.parseData(dataZagreb3);
    storage.saveData(city3, aqi3, pm253, pm103, temperature3, timestamp3);

    return 0;
}
