{ nixpkgs ? import <nixpkgs> {} }:

with nixpkgs;
with pkgs;

stdenv.mkDerivation {
  name = "clipsnoop";
  src = ./.;
  buildInputs = [ pkgconfig gnome3.gtkmm ];
  makeFlags = "PREFIX=$(out)";
}
