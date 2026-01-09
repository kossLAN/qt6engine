set(QT6ENGINE_COMMON_SOURCES
  common.cpp
  config/configmanager.cpp
)

add_library(qt6engine_common SHARED ${QT6ENGINE_COMMON_SOURCES})
add_library(qt6engine::common ALIAS qt6engine_common)

target_include_directories(qt6engine_common
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(qt6engine_common
  PUBLIC
    Qt6::Core
    Qt6::Gui
)

if (TARGET KF6::ConfigCore)
  target_link_libraries(qt6engine_common PRIVATE KF6::ConfigCore)
  target_compile_definitions(qt6engine_common PRIVATE KF_CONFIGCORE_LIB)
endif()

if (TARGET KF6::ColorScheme)
  target_link_libraries(qt6engine_common PRIVATE KF6::ColorScheme)
  target_compile_definitions(qt6engine_common PRIVATE KF_COLORSCHEME_LIB)
endif()

install(TARGETS qt6engine_common DESTINATION ${CMAKE_INSTALL_LIBDIR})
