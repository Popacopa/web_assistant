cmake_minimum_required(VERSION 4.0.3)


project(server)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.88.0")
find_package(Boost REQUIRED)


if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost libraries not found") 
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
    add_library(comport ./modules/ComPort.cpp)
    add_library(portlst ./modules/PortLst.cpp)


    target_link_libraries(comport ${Boost_LIBRARIES})
    target_link_libraries(portlst ${Boost_LIBRARIES})

endif()


add_executable(server server.cpp)


target_link_libraries(server comport)
target_link_libraries(server portlst)