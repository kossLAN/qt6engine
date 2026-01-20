set(QTENGINE_COMMON_SOURCES
  common.cpp
  config/configmanager.cpp
)

add_library(${QTENGINE_NAME}_common SHARED ${QTENGINE_COMMON_SOURCES})
add_library(${QTENGINE_NAME}::common ALIAS ${QTENGINE_NAME}_common)

target_include_directories(${QTENGINE_NAME}_common
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${QTENGINE_NAME}_common PUBLIC ${QT_NAMESPACE}::Core)

if (QT_MAJOR EQUAL 5) 
    target_link_libraries(${QTENGINE_NAME}_common PRIVATE 
      ${KF_NAMESPACE}::ConfigCore
      ${KF_NAMESPACE}::ConfigWidgets
    )
else()
  target_link_libraries(${QTENGINE_NAME}_common PRIVATE 
      ${KF_NAMESPACE}::ConfigCore
      ${KF_NAMESPACE}::ColorScheme
  )
endif()

install(TARGETS ${QTENGINE_NAME}_common DESTINATION ${CMAKE_INSTALL_LIBDIR})
