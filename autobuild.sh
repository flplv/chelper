autoreconf --install || exit 1
mkdir build -p
cd build; ../configure; make
