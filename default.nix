{ stdenv, lib, pkg-config, boost, gtkmm3 }:

stdenv.mkDerivation {
  name = "clipsnoop";
  src = lib.cleanSource ./.;
  nativeBuildInputs = [ pkg-config ];
  buildInputs = [ gtkmm3 boost ];
  makeFlags = "PREFIX=$(out)";
}
