set(QT_MAJOR 5)
set(QT_NAMESPACE "Qt5")
set(KF_NAMESPACE "KF5")
set(QTENGINE_NAME "qt5engine")

if(DEFINED QT5_PLUGINDIR AND NOT QT5_PLUGINDIR STREQUAL "")
    set(PLUGINDIR "${QT5_PLUGINDIR}")
else()
    set(PLUGINDIR "lib/qt5/plugins")
endif()

find_package(Qt5 ${QT5_MIN_VERSION} COMPONENTS Core Gui Widgets DBus REQUIRED)
find_package(Qt5QuickControls2 ${QT5_MIN_VERSION})
find_package(Qt5ThemeSupport ${QT5_MIN_VERSION} CONFIG REQUIRED Private)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    Config ConfigWidgets IconThemes
)

add_subdirectory(common)
add_subdirectory(style)
add_subdirectory(plugin)
