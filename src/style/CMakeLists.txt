find_package(${QT_NAMESPACE} ${QT_MIN_VERSION} COMPONENTS Widgets REQUIRED)

set(QTENGINE_STYLE_SOURCES
	plugin.cpp
	proxystyle.cpp
)

add_library(${QTENGINE_NAME}_style MODULE ${QTENGINE_STYLE_SOURCES})
add_library(${QTENGINE_NAME}::style ALIAS ${QTENGINE_NAME}_style)

target_include_directories(${QTENGINE_NAME}_style PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${QTENGINE_NAME}_style PRIVATE QT_PLUGIN QT_SHARED)

target_link_libraries(${QTENGINE_NAME}_style
	PRIVATE
		${QT_NAMESPACE}::Core
		${QT_NAMESPACE}::Gui
		${QT_NAMESPACE}::Widgets
		${QTENGINE_NAME}::common
)

set(QTENGINE_STYLE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

if (EXISTS "${QTENGINE_STYLE_METADATA}")
	target_sources(${QTENGINE_NAME}_style PRIVATE "${QTENGINE_STYLE_METADATA}")
	set_source_files_properties("${QTENGINE_STYLE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
endif()

install(TARGETS ${QTENGINE_NAME}_style DESTINATION "${PLUGINDIR}/styles")
