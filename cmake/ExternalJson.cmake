# Download json.hpp
ExternalProject_Add(
        JSON
        URL https://github.com/nlohmann/json/archive/v1.1.0.tar.gz
        LOG_DOWNLOAD ON
        INSTALL_COMMAND ""
        BUILD_COMMAND ""
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/Deps/JSON"
)

ExternalProject_Get_Property(JSON source_dir)

set(JSON_INCLUDE_DIR "${source_dir}/src" CACHE STRING "JSON include")


