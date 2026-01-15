set(QTENGINE_PLUGIN_SOURCES
	main.cpp
	platformtheme.cpp
)

add_library(${QTENGINE_NAME}_plugin MODULE ${QTENGINE_PLUGIN_SOURCES})

target_include_directories(${QTENGINE_NAME}_plugin PRIVATE "${QT6ENGINE_CPP_DIR}")
target_compile_definitions(${QTENGINE_NAME}_plugin PRIVATE QT_PLUGIN QT_SHARED)

target_link_libraries(${QTENGINE_NAME}_plugin
	PUBLIC ${QT_NAMESPACE}::Core ${QT_NAMESPACE}::Gui
	PRIVATE ${QTENGINE_NAME}::common
)

if (TARGET ${QT_NAMESPACE}::GuiPrivate)
	target_link_libraries(${QTENGINE_NAME}_plugin PRIVATE ${QT_NAMESPACE}::GuiPrivate)
endif()

if (QT_MAJOR EQUAL 5)
	if (TARGET ${QT_NAMESPACE}::ThemeSupport)
		target_link_libraries(${QTENGINE_NAME}_plugin PRIVATE ${QT_NAMESPACE}::ThemeSupport)
	endif()
	if (TARGET ${QT_NAMESPACE}::ThemeSupportPrivate)
		target_link_libraries(${QTENGINE_NAME}_plugin PRIVATE ${QT_NAMESPACE}::ThemeSupportPrivate)
	endif()
endif()

set(QTENGINE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

if(EXISTS "${QTENGINE_METADATA}")
	target_sources(${QTENGINE_NAME}_plugin PRIVATE "${QTENGINE_METADATA}")
	set_source_files_properties("${QTENGINE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
endif()

install(TARGETS ${QTENGINE_NAME}_plugin DESTINATION "${PLUGINDIR}/platformthemes")
