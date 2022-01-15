cmake_minimum_required(VERSION 3.9)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_BUILD_TYPE Debug)

#project(HelloWorld)
project(Rest_API)

#cpp rest sdk related lines
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk CONFIG REQUIRED)
#find_package(Boost COMPONENTS system REQUIRED)
# end of cpp rest sdk

#json package
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
#target_link_libraries(myprogram ${JSONCPP_LIBRARIES})


#add_executable(HelloWorld src/main.cpp)

add_executable(Client src/client.cpp)

add_executable(Server  src/server.cpp src/handler.cpp src/json_parser.cpp 
src/dbase.cpp src/utils.cpp)

#linking rest sdk to this 
#target_link_libraries(HelloWorld PRIVATE cpprestsdk::cpprest)
target_link_libraries(Client PRIVATE cpprestsdk::cpprest)
target_link_libraries(Server PRIVATE cpprestsdk::cpprest)
#
# rest sdk cmake lines
#
