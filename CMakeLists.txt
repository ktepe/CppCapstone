cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_BUILD_TYPE Debug)

project(HelloWorld)

#cpp rest sdk related lines
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

#json package
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
#target_link_libraries(myprogram ${JSONCPP_LIBRARIES})


# end of cpp rest sdk

add_executable(HelloWorld src/main.cpp)

add_executable(Client src/nclient.cpp)

add_executable(Wserv  src/webserver.cpp src/handler.cpp )

#add_executable(restserver
#  main.cpp
#  src/handler.cpp
#  )


#add_executable(Server src/server.cpp)

#linking rest sdk to this 
#target_link_libraries(HelloWorld PRIVATE cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
target_link_libraries(HelloWorld PRIVATE cpprestsdk::cpprest)
target_link_libraries(Client PRIVATE cpprestsdk::cpprest)
target_link_libraries(Wserv PRIVATE cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY} ${JSONCPP_LIBRARIES})
#
# rest sdk cmake lines
#
#cmake_minimum_required(VERSION 3.7)
#project(main)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
#find_package(cpprestsdk CONFIG REQUIRED)
#find_package(Boost COMPONENTS system REQUIRED)
#add_executable(main main.cpp)
#target_link_libraries(main PRIVATE cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
