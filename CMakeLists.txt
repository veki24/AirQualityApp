cmake_minimum_required(VERSION 3.10)

project(AirQualityApp)

set(CMAKE_CXX_STANDARD 20)


# Set vcpkg root directory and use the vcpkg toolchain file
set(VCPKG_ROOT "C:/Users/Vedran/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Add sources
add_executable(AirQualityApp main.cpp data_fetcher.cpp data_storage.cpp)

# Link curl library
find_package(CURL REQUIRED)
target_include_directories(AirQualityApp PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(AirQualityApp PRIVATE ${CURL_LIBRARIES})

# Include nlohmann/json library
find_package(nlohmann_json REQUIRED)
target_link_libraries(AirQualityApp PRIVATE nlohmann_json::nlohmann_json)

# Find and link libpqxx library using vcpkg
find_package(libpqxx CONFIG REQUIRED)
target_link_libraries(AirQualityApp PRIVATE libpqxx::pqxx)
