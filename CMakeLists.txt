cmake_minimum_required(VERSION 3.16)

project(qt6engine_plugin LANGUAGES CXX)

set(QT_MIN_VERSION 6.9)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if(NOT DEFINED PLUGINDIR OR PLUGINDIR STREQUAL "")
    set(PLUGINDIR "lib/qt-6")
endif()

# nix workaround
if (CMAKE_EXPORT_COMPILE_COMMANDS)
	set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()


find_package(Qt6 ${QT_MIN_VERSION} COMPONENTS Core Gui Widgets REQUIRED)

# Optional KDE Frameworks integration (colorscheme parsing, icon themes).
# Keep these QUIET so building without KF6 installed doesn't emit warnings.
find_package(KF6Config CONFIG QUIET)
find_package(KF6ColorScheme CONFIG QUIET)
find_package(KF6IconThemes CONFIG QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

# In Qt 6.10, private dependencies are required to be explicit,
# but they could not be explicitly depended on prior to 6.9.
if (Qt6_VERSION VERSION_GREATER_EQUAL "6.9.0")
	set(QT_NO_PRIVATE_MODULE_WARNING ON)
    find_package(Qt6 ${QT_MIN_VERSION} COMPONENTS GuiPrivate REQUIRED)
endif()


add_subdirectory(src)
