cmake_minimum_required(VERSION 3.5)

project(Yahtzee VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    Main.cpp
    YahtzeeUI.cpp
    YahtzeeUI.h
    Dice.h
    Dice.cpp
    YahtzeeGame.cpp
    YahtzeeGame.h
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/Yahtzee.icns
    PROPERTIES MACOSX_PACKAGE_LOCATION Resources
)

qt_add_executable(Yahtzee
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

target_link_libraries(Yahtzee PRIVATE Qt6::Widgets)

set_target_properties(Yahtzee PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Yahtzee
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Set application icon (macOS-specific)
if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE Yahtzee.icns)
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/Yahtzee.icns
        PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )
endif()

qt_finalize_executable(Yahtzee)

add_custom_command(TARGET Yahtzee POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "$<TARGET_FILE_DIR:Yahtzee>/resources")


install(TARGETS Yahtzee
    BUNDLE DESTINATION .
)

set(CPACK_GENERATOR DragNDrop)
set(CPACK_PACKAGE_FILE_NAME Yahtzee-${CMAKE_PROJECT_VERSION}-macos-arm64)
set(CPACK_PACKAGE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/Yahtzee.icns)
include(CPack)   