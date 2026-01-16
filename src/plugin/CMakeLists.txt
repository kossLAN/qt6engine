set(QTENGINE_PLUGIN_SOURCES
	main.cpp
	platformtheme.cpp
)

add_library(${QTENGINE_NAME}_plugin MODULE ${QTENGINE_PLUGIN_SOURCES})

set_target_properties(${QTENGINE_NAME}_plugin PROPERTIES
	INSTALL_RPATH "$ORIGIN/../../../../${CMAKE_INSTALL_LIBDIR}"
)

target_link_libraries(${QTENGINE_NAME}_plugin
	PUBLIC 
        ${QT_NAMESPACE}::Core 
        ${QT_NAMESPACE}::Gui
	PRIVATE 
        ${QT_NAMESPACE}::GuiPrivate
        $<TARGET_NAME_IF_EXISTS:${QT_NAMESPACE}::WidgetsPrivate>
        $<TARGET_NAME_IF_EXISTS:${QT_NAMESPACE}::QuickControls2>
        ${KF_NAMESPACE}::IconThemes
        ${QTENGINE_NAME}::common
)

if (QT_MAJOR EQUAL 5)
    target_link_libraries(${QTENGINE_NAME}_plugin PRIVATE 
        ${QT_NAMESPACE}::ThemeSupport 
        ${QT_NAMESPACE}::ThemeSupportPrivate)
endif()

# set(QTENGINE_METADATA "${CMAKE_CURRENT_SOURCE_DIR}/engine.json")

# if(EXISTS "${QTENGINE_METADATA}")
# 	target_sources(${QTENGINE_NAME}_plugin PRIVATE "${QTENGINE_METADATA}")
# 	set_source_files_properties("${QTENGINE_METADATA}" PROPERTIES HEADER_FILE_ONLY ON)
# endif()

install(TARGETS ${QTENGINE_NAME}_plugin DESTINATION "${PLUGINDIR}/platformthemes")
