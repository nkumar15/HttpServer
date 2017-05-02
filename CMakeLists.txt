cmake_minimum_required (VERSION 2.8)
project (httpserver)

find_package(Boost 1.63.0 COMPONENTS system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(httpserver ${Boost_LIBRARIES})
endif()

file(GLOB SOURCES "src/*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(httpserver ${SOURCES})