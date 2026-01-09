{
  pkgs ? import <nixpkgs> {},
  stdenv ? pkgs.clangStdenv,
  qt6engine ? pkgs.callPackage ./nix/default.nix {inherit stdenv;},
  ...
}: let
  tidyfox = import (pkgs.fetchFromGitea {
    domain = "git.outfoxxed.me";
    owner = "outfoxxed";
    repo = "tidyfox";
    rev = "9d85d7e7dea2602aa74ec3168955fee69967e92f";
    hash = "sha256-77ERiweF6lumonp2c/124rAoVG6/o9J+Aajhttwtu0w=";
  }) {inherit pkgs;};
in
  pkgs.mkShell.override {stdenv = qt6engine.stdenv;} {
    inputsFrom = [qt6engine];

    buildInputs = with pkgs; [
      kdePackages.kconfig
      kdePackages.kcolorscheme
      kdePackages.kiconthemes
    ];

    nativeBuildInputs = with pkgs; [
      just
      clang-tools
      parallel
      makeWrapper
    ];

    TIDYFOX = "${tidyfox}/lib/libtidyfox.so";
    QT_QPA_PLATFORMTHEME = "qt6engine";
    # QT_DEBUG_PLUGINS = "1";

    shellHook = ''
      export CMAKE_BUILD_PARALLEL_LEVEL=$(nproc)
      export QT_PLUGIN_PATH=$QT_PLUGIN_PATH:$(echo $PWD)/result/lib/qt-6/plugins

      # Add Qt-related environment variables.
      # https://discourse.nixos.org/t/qt-development-environment-on-a-flake-system/23707/5
      setQtEnvironment=$(mktemp)
      random=$(openssl rand -base64 20 | sed "s/[^a-zA-Z0-9]//g")
      makeShellWrapper "$(type -p sh)" "$setQtEnvironment" "''${qtWrapperArgs[@]}" --argv0 "$random"
      sed "/$random/d" -i "$setQtEnvironment"
      source "$setQtEnvironment"

      # qmlls does not account for the import path and bases its search off qtbase's path.
      # The actual imports come from qtdeclarative. This directs qmlls to the correct imports.
      export QMLLS_BUILD_DIRS=$(pwd)/build:$QML2_IMPORT_PATH
    '';
  }
