{
  stdenv,
  lib,
  cmake,
  ninja,
  qtbase,
  libsForQt5,
}:
stdenv.mkDerivation {
  pname = "qtengine-qt5";
  version = "0.1.0";
  src = ../.;

  nativeBuildInputs = [
    cmake
    ninja
  ];

  buildInputs = [
    qtbase
    libsForQt5.kconfig
    libsForQt5.kconfigwidgets
    libsForQt5.kiconthemes
  ];

  cmakeFlags = [
    (lib.cmakeFeature "QTENGINE_QT_MAJOR" "5")
    (lib.cmakeFeature "PLUGINDIR" "${placeholder "out"}/${qtbase.qtPluginPrefix}")
  ];

  dontWrapQtApps = true;
}
