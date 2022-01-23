{ stdenv, lib, pkgconfig, boost, gtkmm3 }:

stdenv.mkDerivation {
  name = "clipsnoop";
  src = lib.cleanSource ./.;
  nativeBuildInputs = [ pkgconfig ];
  buildInputs = [ gtkmm3 boost ];
  makeFlags = "PREFIX=$(out)";
}
