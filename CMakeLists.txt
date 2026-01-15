cmake_minimum_required(VERSION 3.16)

project(qtengine_plugin LANGUAGES CXX)

set(QT6_MIN_VERSION 6.9)
set(QT5_MIN_VERSION 5.15)

function(qtengine_use_qt qt_major)
	if(NOT qt_major)
		set(qt_major 6)
	endif()

	if(NOT qt_major EQUAL 5 AND NOT qt_major EQUAL 6)
		message(FATAL_ERROR "qtengine_use_qt() expects 5 or 6, got '${qt_major}'.")
	endif()

	if(qt_major EQUAL 6)
		set(qt_min_version "${QT6_MIN_VERSION}")
			set(qtengine_name "qt6engine")
	else()
		set(qt_min_version "${QT5_MIN_VERSION}")
			set(qtengine_name "qt5engine")
	endif()

	set(QT_MAJOR "${qt_major}" CACHE STRING "Qt major version to build against (5 or 6)" FORCE)
	set(QT_MIN_VERSION "${qt_min_version}" CACHE STRING "Qt minimum version" FORCE)
	set(QT_NAMESPACE "Qt${qt_major}" CACHE STRING "Qt CMake target namespace" FORCE)
	set(QTENGINE_NAME "${qtengine_name}" CACHE STRING "Engine name based on Qt major" FORCE)
endfunction()

if(NOT DEFINED QTENGINE_QT_MAJOR OR QTENGINE_QT_MAJOR STREQUAL "")
	set(QTENGINE_QT_MAJOR 6)
endif()

qtengine_use_qt("${QTENGINE_QT_MAJOR}")

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
	set(PLUGINDIR "lib/qt-${QT_MAJOR}/plugins")
endif()

# nix workaround
if (CMAKE_EXPORT_COMPILE_COMMANDS)
	set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

if(QT_MAJOR EQUAL 5)
	find_package(Qt5 ${QT5_MIN_VERSION} COMPONENTS Core Gui Widgets REQUIRED)
	find_package(Qt5Gui ${QT5_MIN_VERSION} CONFIG REQUIRED Private)
	find_package(Qt5ThemeSupport ${QT5_MIN_VERSION} CONFIG REQUIRED Private)

	add_library(Qt::Core ALIAS Qt5::Core)
	add_library(Qt::Gui ALIAS Qt5::Gui)

	find_package(KF5Config CONFIG REQUIRED)
	find_package(KF5ConfigWidgets CONFIG REQUIRED)
	find_package(KF5IconThemes CONFIG REQUIRED)
else()
	find_package(Qt6 ${QT6_MIN_VERSION} COMPONENTS Core Gui Widgets REQUIRED)

	find_package(KF6Config CONFIG REQUIRED)
	find_package(KF6ColorScheme CONFIG REQUIRED)
	find_package(KF6IconThemes CONFIG REQUIRED)

    # In Qt 6.10, private dependencies are required to be explicit,
    # but they could not be explicitly depended on prior to 6.9.
    if(QT_MAJOR EQUAL 6 AND Qt6_VERSION VERSION_GREATER_EQUAL "6.9.0")
        set(QT_NO_PRIVATE_MODULE_WARNING ON)
        find_package(Qt6 ${QT6_MIN_VERSION} COMPONENTS GuiPrivate REQUIRED)
    endif()
endif()

add_subdirectory(src)
