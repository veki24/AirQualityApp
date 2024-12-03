#include <iostream>
#include "data_fetcher.h"
#include "data_storage.h"

int main() {
    // URLs for all three Zagreb locations
    const std::string urlZagreb1 = "https://api.waqi.info/feed/zagreb/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279";
    const std::string urlZagreb2 = "https://api.waqi.info/feed/@5161/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279";
    const std::string urlZagreb3 = "https://api.waqi.info/feed/@5152/?token=8591b3ce57a87b12b2f6989e64f4e2158db48279"; // New URL for Zagreb-3

    DataFetcher fetcher;
    DataStorage storage;

    // Fetch and display air quality data for Zagreb-1
    std::cout << "Fetching data for Zagreb-1:" << std::endl;
    std::string dataZagreb1 = fetcher.fetchData(urlZagreb1);
    std::string parsedDataZagreb1 = fetcher.parseData(dataZagreb1);
    std::cout << parsedDataZagreb1 << std::endl;

    // Fetch and display air quality data for Zagreb-2
    std::cout << "Fetching data for Zagreb-2:" << std::endl;
    std::string dataZagreb2 = fetcher.fetchData(urlZagreb2);
    std::string parsedDataZagreb2 = fetcher.parseData(dataZagreb2);
    std::cout << parsedDataZagreb2 << std::endl;

    // Fetch and display air quality data for Zagreb-3
    std::cout << "Fetching data for Zagreb-3:" << std::endl;
    std::string dataZagreb3 = fetcher.fetchData(urlZagreb3);
    std::string parsedDataZagreb3 = fetcher.parseData(dataZagreb3);
    std::cout << parsedDataZagreb3 << std::endl;

    // Save both data to file (optional)
    storage.saveData(parsedDataZagreb1);
    storage.saveData(parsedDataZagreb2);
    storage.saveData(parsedDataZagreb3);

    // Prompt to view stored data
    std::cout << "Do you want to view the stored data? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        storage.viewStoredData();
    }

    return 0;
}
