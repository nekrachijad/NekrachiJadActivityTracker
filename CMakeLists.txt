cmake_minimum_required(VERSION 3.16)
project(NekrachiJadActivityTracker)

set(CMAKE_CXX_STANDARD 20)

# Dov'è Qt installato? (Adatta se diverso)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")

# Trova Qt6 e i moduli
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Attiva automoc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Aggiungi l'eseguibile
add_executable(NekrachiJadActivityTracker main.cpp)

# Linka Qt
target_link_libraries(NekrachiJadActivityTracker PRIVATE Qt6::Widgets)

# Copia le DLL Qt nella build directory (Qt6Core.dll, Qt6Gui.dll, Qt6Widgets.dll)
add_custom_command(TARGET NekrachiJadActivityTracker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Qt6_DIR}/../../../bin/Qt6Core.dll"
        "${Qt6_DIR}/../../../bin/Qt6Gui.dll"
        "${Qt6_DIR}/../../../bin/Qt6Widgets.dll"
        $<TARGET_FILE_DIR:NekrachiJadActivityTracker>
)

# Copia qwindows.dll nella sotto-cartella "platforms"
add_custom_command(TARGET NekrachiJadActivityTracker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:NekrachiJadActivityTracker>/platforms"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Qt6_DIR}/../../../plugins/platforms/qwindows.dll"
        "$<TARGET_FILE_DIR:NekrachiJadActivityTracker>/platforms"
)
