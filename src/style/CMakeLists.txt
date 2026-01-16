set(QTENGINE_STYLE_SOURCES
	plugin.cpp
	proxystyle.cpp
)

add_library(${QTENGINE_NAME}_style MODULE ${QTENGINE_STYLE_SOURCES})
add_library(${QTENGINE_NAME}::style ALIAS ${QTENGINE_NAME}_style)

set_target_properties(${QTENGINE_NAME}_style PROPERTIES
	INSTALL_RPATH "$ORIGIN/../../../../${CMAKE_INSTALL_LIBDIR}"
)

target_link_libraries(${QTENGINE_NAME}_style
	PRIVATE
		${QT_NAMESPACE}::Widgets
		${QTENGINE_NAME}::common
)

# set(QTENGINE_STYLE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

# if (EXISTS "${QTENGINE_STYLE_METADATA}")
# 	target_sources(${QTENGINE_NAME}_style PRIVATE "${QTENGINE_STYLE_METADATA}")
# 	set_source_files_properties("${QTENGINE_STYLE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
# endif()

install(TARGETS ${QTENGINE_NAME}_style DESTINATION "${PLUGINDIR}/styles")
