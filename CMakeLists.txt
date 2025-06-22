cmake_minimum_required(VERSION 3.16)
project(NekrachiJadActivityTracker)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")


find_package(Qt6 REQUIRED COMPONENTS Widgets)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(test)
set(SOURCE_FILES Date.cpp Date.h)
add_executable(NekrachiJadActivityTracker main.cpp Date.h Date.cpp Activity.h Activity.cpp ActivityList.h ActivityList.cpp Ora.h Ora.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(NekrachiJadActivityTracker PRIVATE Qt6::Widgets)



add_custom_command(TARGET NekrachiJadActivityTracker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Qt6_DIR}/../../../bin/Qt6Core.dll"
        "${Qt6_DIR}/../../../bin/Qt6Gui.dll"
        "${Qt6_DIR}/../../../bin/Qt6Widgets.dll"
        $<TARGET_FILE_DIR:NekrachiJadActivityTracker>
)

add_custom_command(TARGET NekrachiJadActivityTracker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:NekrachiJadActivityTracker>/platforms"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Qt6_DIR}/../../../plugins/platforms/qwindows.dll"
        "$<TARGET_FILE_DIR:NekrachiJadActivityTracker>/platforms"
)

