# qt6engine 

This is primarily a fork of [hyprqt6engine](https://github.com/hyprwm/hyprqt6engine), and by extension [qt6ct](https://www.opencode.net/trialuser/qt6ct). This aims to seperate itself from unnecessary dependencies, and to provide a good interface for nix.

## Nix Flake Installation

First add the input to your flake.

```nix
qt6engine = {
  url = "github:kossLAN/qt6engine";
  inputs.nixpkgs.follows = "nixpkgs";
};
```

Then use the provided NixOS module.

```nix
imports = [inputs.qt6engine.nixosModules.default];

# Add your desired theme to your system packages
environment.systemPackages = with pkgs.kdePackages; [
  breeze
  breeze-icons
];

programs.qt6engine = {
  enable = true;
  
  config = {
    theme = {
      colorScheme = "${pkgs.kdePackages.breeze}/share/color-schemes/BreezeDark.colors";
      iconTheme = "breeze-dark";
      style = "breeze";
      fontFixed = "<font name>";
      fontFixedSize = 10;
      font = "<font name>";
      fontSize = 10;
    };

    misc = {
      singleClickActivate = false;
      menusHaveIcons = true;
      shortcutsForContextMenus = true;
    };
  };
};
```

> [!NOTE]
>
> A restart of your DE/WM may be required for changes to take effect.

## Credits 

Thank you [hyprqt6engine](https://github.com/hyprwm/hyprqt6engine) & [qt6ct](https://www.opencode.net/trialuser/qt6ct) for being the foundation of this project. Also a thanks to [outfoxxed](https://github.com/outfoxxed) because I "borrowed" a lot of his C++ build tools that made working in C++ a lot less painful, especially on NixOS.
