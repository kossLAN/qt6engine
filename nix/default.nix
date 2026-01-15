{
  lib,
  pkgs,
  symlinkJoin,
  withQt5 ? true,
}: let
  # We use symlinkJoin because we have conflicting buildInputs that will cause the build
  # to explode otherwise :)
  qt6engine = pkgs.callPackage ./qt6engine.nix {};
  qt5engine = pkgs.libsForQt5.callPackage ./qt5engine.nix {};
in
  symlinkJoin {
    name = "qtengine";
    paths =
      [qt6engine]
      ++ lib.optionals withQt5 [qt5engine];
  }
