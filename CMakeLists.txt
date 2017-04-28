cmake_minimum_required (VERSION 2.8)
project (httpserver)
find_package(Boost 1.63.0)

file(GLOB SOURCES "src/*.cpp")

add_executable(httpserver ${SOURCES})