#!/usr/bin/sh

git clone https://github.com/json-parser/json-parser.git
echo "[json parser] configruing"
cd json-parser
./configure
echo "[json parser] cconfigured"

echo "[json parser] installing"
make install
echo "[json parser] installed"
cd -
rm -rf deps
echo "[cmake] build project"
cmake -S . -B build
echo "[cmake] builed successful"

echo "[make] build binary"
cd build
make
echo "[make] build binary successful"
export LD_LIBRARY_PATH=/usr/local/lib:/usr/local/lib64:/usr/local/lib/json-parser