#!/bin/bash
set -e

echo "Building project..."

cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static"

cd build

cmake --build .

chmod +x dnsplay

docker build -t dnsplay ..

echo "Done! Docker image 'dnsplay' created successfully."

