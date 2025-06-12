cmake_minimum_required(VERSION 3.30)
project(NekrachiJadActivityTracker)

set(CMAKE_CXX_STANDARD 20)

# Adatta questo percorso al tuo Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.3/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(NekrachiJadActivityTracker main.cpp)

target_link_libraries(NekrachiJadActivityTracker PRIVATE Qt6::Widgets)

