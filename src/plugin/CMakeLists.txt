set(QT6ENGINE_PLUGIN_SOURCES
	main.cpp
	platformtheme.cpp
)

add_library(qt6engine_plugin MODULE ${QT6ENGINE_PLUGIN_SOURCES})

target_include_directories(qt6engine_plugin PRIVATE "${QT6ENGINE_CPP_DIR}")
target_compile_definitions(qt6engine_plugin PRIVATE QT_PLUGIN QT_SHARED)

target_link_libraries(qt6engine_plugin
	PUBLIC Qt6::Core Qt6::Gui
	PRIVATE Qt6::GuiPrivate qt6engine::common
)

set(QT6ENGINE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

if(EXISTS "${QT6ENGINE_METADATA}")
	target_sources(qt6engine_plugin PRIVATE "${QT6ENGINE_METADATA}")
	set_source_files_properties("${QT6ENGINE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
endif()

install(TARGETS qt6engine_plugin DESTINATION "${PLUGINDIR}/platformthemes")
