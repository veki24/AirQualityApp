cmake_minimum_required(VERSION 3.10)

project(AirQualityApp)

set(CMAKE_CXX_STANDARD 17)

# Add sources
add_executable(AirQualityApp main.cpp data_fetcher.cpp data_storage.cpp)

# Link curl library
find_package(CURL REQUIRED)
target_include_directories(AirQualityApp PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(AirQualityApp PRIVATE ${CURL_LIBRARIES})

# Include nlohmann/json library (ensure it's installed)
find_package(nlohmann_json REQUIRED)
target_link_libraries(AirQualityApp PRIVATE nlohmann_json::nlohmann_json)
