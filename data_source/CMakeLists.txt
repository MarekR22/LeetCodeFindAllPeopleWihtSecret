find_package(nlohmann_json 3.11.3 REQUIRED)

add_library(data_source)
target_sources(data_source
    PRIVATE
        data.cpp
        directories.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/directories.hpp
    PUBLIC data.hpp)

target_link_libraries(data_source PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(data_source
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/directories.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/directories.hpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/large.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
