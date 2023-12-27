cmake_minimum_required(VERSION 3.5)

project(threads_1_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(threads_1_1 main.cpp)

include(GNUInstallDirs)
install(TARGETS threads_1_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
