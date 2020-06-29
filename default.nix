{ stdenv, lib, pkgconfig, gnome3 }:

stdenv.mkDerivation {
  name = "clipsnoop";
  src = lib.cleanSource ./.;
  buildInputs = [ pkgconfig gnome3.gtkmm ];
  makeFlags = "PREFIX=$(out)";
}
