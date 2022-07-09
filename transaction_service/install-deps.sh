#!/usr/bin/sh

echo "[json parser] configruing"
deps/json-parser/configure
echo "[json parser] cconfigured"

echo "[json parser] installing"
make --directory=deps/json-parser install
echo "[json parser] installed"
rm -rf deps
echo "[cmake] build project"
cmake -S . -B build
echo "[cmake] builed successful"

echo "[make] build binary"
make --directory=build
echo "[make] build binary successful"