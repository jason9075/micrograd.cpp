{
  description = "Development environment for micrograd.cpp";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.05";
    nixpkgs-unstable.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ ... }:
    let
      system = "x86_64-linux";
      pkgs = import inputs.nixpkgs {
        inherit system;
        config = { allowUnfree = true; };
      };
      pkgs-unstable = import inputs.nixpkgs-unstable {
        inherit system;
        config = { allowUnfree = true; };
      };
    in {
      devShells.x86_64-linux.default = pkgs.mkShell {
        name = "llm-env";
        nativeBuildInputs = with pkgs; [
          gcc
          gdb
          cmake
          clang-tools
          valgrind
          entr
        ];

        shellHook = ''
          export LD_LIBRARY_PATH=${
            pkgs.lib.makeLibraryPath [ pkgs.stdenv.cc.cc pkgs.zlib ]
          }
          echo "Welcome to micro.grad.cpp project environment!"
        '';
      };
    };
}
