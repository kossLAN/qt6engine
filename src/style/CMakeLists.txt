find_package(Qt6 ${QT_MIN_VERSION} COMPONENTS Widgets REQUIRED)

set(QT6ENGINE_STYLE_SOURCES
	plugin.cpp
	proxystyle.cpp
)

add_library(qt6engine_style MODULE ${QT6ENGINE_STYLE_SOURCES})
add_library(qt6engine::style ALIAS qt6engine_style)

target_include_directories(qt6engine_style PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(qt6engine_style PRIVATE QT_PLUGIN QT_SHARED)

target_link_libraries(qt6engine_style
	PRIVATE
		Qt6::Core
		Qt6::Gui
		Qt6::Widgets
		qt6engine::common
)

set(QT6ENGINE_STYLE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

if (EXISTS "${QT6ENGINE_STYLE_METADATA}")
	target_sources(qt6engine_style PRIVATE "${QT6ENGINE_STYLE_METADATA}")
	set_source_files_properties("${QT6ENGINE_STYLE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
endif()

install(TARGETS qt6engine_style DESTINATION "${PLUGINDIR}/styles")
