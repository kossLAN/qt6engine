{
  lib,
  stdenv,
  qt6Packages,
  kdePackages,
  cmake,
  ninja,
}:
stdenv.mkDerivation {
  pname = "qt6engine";
  version = "0.1.0";
  src = ../.;

  nativeBuildInputs = [
    cmake
    ninja
  ];

  buildInputs = [
    qt6Packages.qtbase

    kdePackages.kconfig
    kdePackages.kcolorscheme
    kdePackages.kiconthemes
  ];

  cmakeFlags = [
    (lib.cmakeFeature "PLUGINDIR" "${placeholder "out"}/lib/qt-6/plugins")
  ];

  dontWrapQtApps = true;
}
